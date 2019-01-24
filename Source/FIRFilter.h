////////////////////////////////////////////////////////////////////////////////
///
/// General FIR digital filter routines with MMX optimization. 
///
/// Note : MMX optimized functions reside in a separate, platform-specific file, 
/// e.g. 'mmx_win.cpp' or 'mmx_gcc.cpp'
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

#ifndef FIRFilter_H
#define FIRFilter_H

#include <stddef.h>

namespace soundtouch
{

	class FIRFilter
	{
	protected:
		// Number of FIR filter taps
		unsigned int length;
		// Number of FIR filter taps divided by 8
		unsigned int lengthDiv8;

		// Result divider factor in 2^k format
		unsigned int resultDivFactor;

		// Result divider value.
		float resultDivider;

		// Memory for filter coefficients
		float *filterCoeffs;

		virtual unsigned int evaluateFilterStereo(float *dest,
			const float *src,
			unsigned int numSamples) const;
		virtual unsigned int evaluateFilterMono(float *dest,
			const float *src,
			unsigned int numSamples) const;
		virtual unsigned int evaluateFilterMulti(float *dest, const float *src, unsigned int numSamples, unsigned int numChannels);

	public:
		FIRFilter();
		virtual ~FIRFilter();

		/// Operator 'new' is overloaded so that it automatically creates a suitable instance 
		/// depending on if we've a MMX-capable CPU available or not.
		static void * operator new(size_t s);

		static FIRFilter *newInstance();

		/// Applies the filter to the given sequence of samples. 
		/// Note : The amount of outputted samples is by value of 'filter_length' 
		/// smaller than the amount of input samples.
		///
		/// \return Number of samples copied to 'dest'.
		unsigned int evaluate(float *dest,
			const float *src,
			unsigned int numSamples,
			unsigned int numChannels);

		unsigned int getLength() const;

		virtual void setCoefficients(const float *coeffs,
			unsigned int newLength,
			unsigned int uResultDivFactor);
	};


	// Optional subclasses that implement CPU-specific optimizations:

#ifdef SOUNDTOUCH_ALLOW_MMX

/// Class that implements MMX optimized functions exclusive for 16bit integer samples type.
	class FIRFilterMMX : public FIRFilter
	{
	protected:
		short *filterCoeffsUnalign;
		short *filterCoeffsAlign;

		virtual unsigned int evaluateFilterStereo(short *dest, const short *src, unsigned int numSamples) const;
	public:
		FIRFilterMMX();
		~FIRFilterMMX();

		virtual void setCoefficients(const short *coeffs, unsigned int newLength, unsigned int uResultDivFactor);
	};

#endif // SOUNDTOUCH_ALLOW_MMX


#ifdef SOUNDTOUCH_ALLOW_SSE
	/// Class that implements SSE optimized functions exclusive for floating point samples type.
	class FIRFilterSSE : public FIRFilter
	{
	protected:
		float *filterCoeffsUnalign;
		float *filterCoeffsAlign;

		virtual unsigned int evaluateFilterStereo(float *dest, const float *src, unsigned int numSamples) const;
	public:
		FIRFilterSSE();
		~FIRFilterSSE();

		virtual void setCoefficients(const float *coeffs, unsigned int newLength, unsigned int uResultDivFactor);
	};

#endif // SOUNDTOUCH_ALLOW_SSE

}

#endif  // FIRFilter_H
