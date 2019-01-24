////////////////////////////////////////////////////////////////////////////////
///
/// General FIR digital filter routines with MMX optimization. 
///
/// Notes : MMX optimized functions reside in a separate, platform-specific file, 
/// e.g. 'mmx_win.cpp' or 'mmx_gcc.cpp'
///
/// This source file contains OpenMP optimizations that allow speeding up the
/// corss-correlation algorithm by executing it in several threads / CPU cores 
/// in parallel. See the following article link for more detailed discussion 
/// about SoundTouch OpenMP optimizations:
/// http://www.softwarecoven.com/parallel-computing-in-embedded-mobile-devices
///
/// Author        : Copyright (c) Olli Parviainen
/// Author e-mail : oparviai 'at' iki.fi
/// SoundTouch WWW: http://www.surina.net/soundtouch
///
////////////////////////////////////////////////////////////////////////////////
//
// License :
//
//  SoundTouch audio processing library
//  Copyright (c) Olli Parviainen
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
////////////////////////////////////////////////////////////////////////////////

#include <memory.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "FIRFilter.h"
#include "cpu_detect.h"

#define SOUNDTOUCH_FLOAT_SAMPLES

using namespace soundtouch;

/*****************************************************************************
 *
 * Implementation of the class 'FIRFilter'
 *
 *****************************************************************************/

FIRFilter::FIRFilter()
{
	resultDivFactor = 0;
	resultDivider = 0;
	length = 0;
	lengthDiv8 = 0;
	filterCoeffs = NULL;
}


FIRFilter::~FIRFilter()
{
	delete[] filterCoeffs;
}


// Usual C-version of the filter routine for stereo sound
unsigned int FIRFilter::evaluateFilterStereo(float *dest, const float *src, unsigned int numSamples) const
{
	int j, end;
#ifdef SOUNDTOUCH_FLOAT_SAMPLES
	// when using floating point samples, use a scaler instead of a divider
	// because division is much slower operation than multiplying.
	double dScaler = 1.0 / (double)resultDivider;
#endif

	assert(length != 0);
	assert(src != NULL);
	assert(dest != NULL);
	assert(filterCoeffs != NULL);

	end = 2 * (numSamples - length);

#pragma omp parallel for
	for (j = 0; j < end; j += 2)
	{
		const float *ptr;
		double suml, sumr;
		unsigned int i;

		suml = sumr = 0;
		ptr = src + j;

		for (i = 0; i < length; i += 4)
		{
			// loop is unrolled by factor of 4 here for efficiency
			suml += ptr[2 * i + 0] * filterCoeffs[i + 0] +
				ptr[2 * i + 2] * filterCoeffs[i + 1] +
				ptr[2 * i + 4] * filterCoeffs[i + 2] +
				ptr[2 * i + 6] * filterCoeffs[i + 3];
			sumr += ptr[2 * i + 1] * filterCoeffs[i + 0] +
				ptr[2 * i + 3] * filterCoeffs[i + 1] +
				ptr[2 * i + 5] * filterCoeffs[i + 2] +
				ptr[2 * i + 7] * filterCoeffs[i + 3];
		}

#ifdef SOUNDTOUCH_INTEGER_SAMPLES
		suml >>= resultDivFactor;
		sumr >>= resultDivFactor;
		// saturate to 16 bit integer limits
		suml = (suml < -32768) ? -32768 : (suml > 32767) ? 32767 : suml;
		// saturate to 16 bit integer limits
		sumr = (sumr < -32768) ? -32768 : (sumr > 32767) ? 32767 : sumr;
#else
		suml *= dScaler;
		sumr *= dScaler;
#endif // SOUNDTOUCH_INTEGER_SAMPLES
		dest[j] = (float)suml;
		dest[j + 1] = (float)sumr;
	}
	return numSamples - length;
}


// Usual C-version of the filter routine for mono sound
unsigned int FIRFilter::evaluateFilterMono(float *dest, const float *src, unsigned int numSamples) const
{
	int j, end;
#ifdef SOUNDTOUCH_FLOAT_SAMPLES
	// when using floating point samples, use a scaler instead of a divider
	// because division is much slower operation than multiplying.
	double dScaler = 1.0 / (double)resultDivider;
#endif

	assert(length != 0);

	end = numSamples - length;
#pragma omp parallel for
	for (j = 0; j < end; j++)
	{
		const float *pSrc = src + j;
		double sum;
		unsigned int i;

		sum = 0;
		for (i = 0; i < length; i += 4)
		{
			// loop is unrolled by factor of 4 here for efficiency
			sum += pSrc[i + 0] * filterCoeffs[i + 0] +
				pSrc[i + 1] * filterCoeffs[i + 1] +
				pSrc[i + 2] * filterCoeffs[i + 2] +
				pSrc[i + 3] * filterCoeffs[i + 3];
		}
#ifdef SOUNDTOUCH_INTEGER_SAMPLES
		sum >>= resultDivFactor;
		// saturate to 16 bit integer limits
		sum = (sum < -32768) ? -32768 : (sum > 32767) ? 32767 : sum;
#else
		sum *= dScaler;
#endif // SOUNDTOUCH_INTEGER_SAMPLES
		dest[j] = (float)sum;
	}
	return end;
}


unsigned int FIRFilter::evaluateFilterMulti(float *dest, const float *src, unsigned int numSamples, unsigned int numChannels)
{
	int j, end;

#ifdef SOUNDTOUCH_FLOAT_SAMPLES
	// when using floating point samples, use a scaler instead of a divider
	// because division is much slower operation than multiplying.
	double dScaler = 1.0 / (double)resultDivider;
#endif

	assert(length != 0);
	assert(src != NULL);
	assert(dest != NULL);
	assert(filterCoeffs != NULL);
	assert(numChannels < 16);

	end = numChannels * (numSamples - length);

#pragma omp parallel for
	for (j = 0; j < end; j += numChannels)
	{
		const float *ptr;
		double sums[16];
		unsigned int c, i;

		for (c = 0; c < numChannels; c++)
		{
			sums[c] = 0;
		}

		ptr = src + j;

		for (i = 0; i < length; i++)
		{
			float coef = filterCoeffs[i];
			for (c = 0; c < numChannels; c++)
			{
				sums[c] += ptr[0] * coef;
				ptr++;
			}
		}

		for (c = 0; c < numChannels; c++)
		{
#ifdef SOUNDTOUCH_INTEGER_SAMPLES
			sums[c] >>= resultDivFactor;
#else
			sums[c] *= dScaler;
#endif // SOUNDTOUCH_INTEGER_SAMPLES
			dest[j + c] = (float)sums[c];
		}
	}
	return numSamples - length;
}


// Set filter coeffiecients and length.
//
// Throws an exception if filter length isn't divisible by 8
void FIRFilter::setCoefficients(const float *coeffs, unsigned int newLength, unsigned int uResultDivFactor)
{
	assert(newLength > 0);

	lengthDiv8 = newLength / 8;
	length = lengthDiv8 * 8;
	assert(length == newLength);

	resultDivFactor = uResultDivFactor;
	resultDivider = (float)::pow(2.0, (int)resultDivFactor);

	delete[] filterCoeffs;
	filterCoeffs = new float[length];
	memcpy(filterCoeffs, coeffs, length * sizeof(float));
}


unsigned int FIRFilter::getLength() const
{
	return length;
}


// Applies the filter to the given sequence of samples. 
//
// Note : The amount of outputted samples is by value of 'filter_length' 
// smaller than the amount of input samples.
unsigned int FIRFilter::evaluate(float *dest, const float *src, unsigned int numSamples, unsigned int numChannels)
{
	assert(length > 0);
	assert(lengthDiv8 * 8 == length);

	if (numSamples < length) return 0;

#ifndef USE_MULTICH_ALWAYS
	if (numChannels == 1)
	{
		return evaluateFilterMono(dest, src, numSamples);
	}
	else if (numChannels == 2)
	{
		return evaluateFilterStereo(dest, src, numSamples);
	}
	else
#endif // USE_MULTICH_ALWAYS
	{
		assert(numChannels > 0);
		return evaluateFilterMulti(dest, src, numSamples, numChannels);
	}
}


// Operator 'new' is overloaded so that it automatically creates a suitable instance 
// depending on if we've a MMX-capable CPU available or not.
void * FIRFilter::operator new(size_t s)
{
	// Notice! don't use "new FIRFilter" directly, use "newInstance" to create a new instance instead!
	return newInstance();
}


FIRFilter * FIRFilter::newInstance()
{
	unsigned int uExtensions;

	uExtensions = detectCPUextensions();

	// Check if MMX/SSE instruction set extensions supported by CPU

#ifdef SOUNDTOUCH_ALLOW_MMX
	// MMX routines available only with integer sample types
	if (uExtensions & SUPPORT_MMX)
	{
		return ::new FIRFilterMMX;
	}
	else
#endif // SOUNDTOUCH_ALLOW_MMX

#ifdef SOUNDTOUCH_ALLOW_SSE
		if (uExtensions & SUPPORT_SSE)
		{
			// SSE support
			return ::new FIRFilterSSE;
		}
		else
#endif // SOUNDTOUCH_ALLOW_SSE

		{
			// ISA optimizations not supported, use plain C version
			return ::new FIRFilter;
		}
}
