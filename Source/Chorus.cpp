/*
  ==============================================================================

    Chorus.cpp
    Created: 22 Jan 2019 6:33:16pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "Chorus.h"

// cubic interpolation coefficients
static const float _coeffs[] =
{ -0.5f,  1.0f, -0.5f, 0.0f,
   1.5f, -2.5f,  0.0f, 1.0f,
  -1.5f,  2.0f,  0.5f, 0.0f,
   0.5f, -0.5f,  0.0f, 0.0f };

//==============================================================================
Chorus::Chorus() :
	lMix("mix_knob", "Mix"), lPitch("pitch_knob", "Pitch"),
	lWidth("width_knob", "Width"), lSpeed("speed_knob", "Speed"),
	lDepth("depth_knob", "Depth"), theName("name_label", "Chorus"),
	isActive(false), m(0.0), p(1.0), w(0.5), s(9.99 / 2), d(63.0), en(1),
	currentAngle(0.0), angleDelta(0.0)
{
	initialiseUI();

	initialiseChorus();
}

Chorus::~Chorus()
{
	delete[] filterCoeffs;
}

void Chorus::initialiseUI()
{
	// Name
	theName.setFont(Font(24.0f, Font::plain));
	theName.setColour(Label::textColourId, Colours::white);
	theName.setJustificationType(Justification::centred);
	addAndMakeVisible(theName);

	// Mix
	mix.setRange(0.0f, 1.0f, 1.0f / 150.0f);
	mix.setValue(1.0f);
	mix.addListener(this);
	mix.setName("mix_knob");
	addAndMakeVisible(mix);

	lMix.setFont(Font(16.0f, Font::plain));
	lMix.setColour(Label::textColourId, Colours::white);
	lMix.setJustificationType(Justification::centred);
	addAndMakeVisible(lMix);

	// Pitch
	pitch.setRange(0.85f, 1.15f, 1.0f / 150.0f);
	pitch.setValue(1.0f);
	pitch.addListener(this);
	pitch.setName("pitch_knob");
	addAndMakeVisible(pitch);

	lPitch.setFont(Font(16.0f, Font::plain));
	lPitch.setColour(Label::textColourId, Colours::lightgrey);
	lPitch.setJustificationType(Justification::centred);
	addAndMakeVisible(lPitch);

	// Width
	width.setRange(0.0f, 1.0f, 1.0f / 150.0f);
	width.setValue(0.5f);
	width.addListener(this);
	width.setName("width_knob");
	addAndMakeVisible(width);

	lWidth.setFont(Font(16.0f, Font::plain));
	lWidth.setColour(Label::textColourId, Colours::white);
	lWidth.setJustificationType(Justification::centred);
	addAndMakeVisible(lWidth);

	// LFO Speed
	speed.setRange(0.01f, 10.0f, 9.99f / 150.0f);
	speed.setValue(9.99f / 2.0f);
	speed.addListener(this);
	speed.setName("speed_knob");
	addAndMakeVisible(speed);

	lSpeed.setFont(Font(16.0f, Font::plain));
	lSpeed.setColour(Label::textColourId, Colours::white);
	lSpeed.setJustificationType(Justification::centred);
	addAndMakeVisible(lSpeed);

	// LFO Depth
	depth.setRange(0.0f, 127.0f, 1.0f / 127.0f);
	depth.setValue(63.0f);
	depth.addListener(this);
	depth.setName("depth_knob");
	addAndMakeVisible(depth);

	lDepth.setFont(Font(16.0f, Font::plain));
	lDepth.setColour(Label::textColourId, Colours::white);
	lDepth.setJustificationType(Justification::centred);
	addAndMakeVisible(lDepth);

	// Enable button
	enable.setButtonText("Enable");
	enable.addListener(this);
	enable.changeWidthToFitText();
	addAndMakeVisible(enable);

	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(100, 200);
}

void Chorus::initialiseChorus()
{
	level = d * 0.5;

	angleDelta = s / sampleRate * 2.0 * MathConstants<double>::pi;

	fract = 0;

	resultDivider = 16384;

	filterCoeffs = NULL;

	setCoeffs();
}

void Chorus::updateChorus()
{
	sliderValueChanged(&mix);
	sliderValueChanged(&pitch);
	sliderValueChanged(&width);
	sliderValueChanged(&speed);
	sliderValueChanged(&depth);
}

//==============================================================================
void Chorus::paint(Graphics& g)
{
}

void Chorus::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor...
	theName.setBounds(0.0f, 0.0f, getWidth(), 25.0f);

	mix.setBounds(getWidth() / 4.0f, 18.0f, 50.0f, 50.0f);
	lMix.setBounds(getWidth() / 4.0f, 60.5, 50.0f, 15.0f);

	width.setBounds(0.0f, 68.0f, 50.0f, 50.0f);
	lWidth.setBounds(0.0f, 110.5f, 50.0f, 15.0f);

	pitch.setBounds(50.0f, 68.0f, 50.0f, 50.0f);
	lPitch.setBounds(50.0f, 110.5f, 50.0f, 15.0f);

	speed.setBounds(0.0f, 118.0f, 50.0f, 50.0f);
	lSpeed.setBounds(0.0f, 160.5f, 50.0f, 15.0f);

	depth.setBounds(50.0f, 118.0f, 50.0f, 50.0f);
	lDepth.setBounds(50.0f, 160.5f, 50.0f, 15.0f);

	enable.setBounds((getWidth() / 2.0f) - 25.0f, 182.0f, 50.0f, 18.0f);
}

void Chorus::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	this->sampleRate = sampleRate;
	spb = samplesPerBlock;
	fract = 0;
}

void Chorus::processSamples(AudioBuffer<float>& buffer, int numSamples)
{
	if (isActive)
	{
		// Evidently this is the only way to get this block into new memory
		AudioBuffer<float> initial(buffer.getNumChannels(), numSamples);
		initial = buffer;

		// Process waveshaping
		juce::dsp::AudioBlock<float> block = juce::dsp::AudioBlock<float>(buffer).getSubBlock((size_t)0, (size_t)numSamples);
		processLFO(block, initial, numSamples);

		// Mix the two signals
		block.multiply(m);
		block.addWithMultiply(juce::dsp::AudioBlock<float>(initial).getSubBlock((size_t)0, (size_t)numSamples), 1.0f - m);
	}
}

void Chorus::processLFO(juce::dsp::AudioBlock<float>& block, const juce::dsp::AudioBlock<float> initial, int numSamples)
{
	int startSample = 0;
	float orig_sample;
	float voic_sample;

	level = d * 0.5;

	angleDelta = s / sampleRate * 2.0 * MathConstants<double>::pi;

	if (angleDelta != 0.0)
	{
		while (--numSamples >= 0)
		{
			float temp, vol1, fract_float;
			double currentSample;

			currentSample = (double)(0.5 * (level / 127.0f) * sin(currentAngle));
			
			transposeMulti(block, initial, numSamples, initial.getNumChannels());

			for (int i = 0; i < initial.getNumChannels(); i++)
			{
				orig_sample = initial.getSample(i, startSample);

				voic_sample = block.getSample(i, startSample);
				//voic_sample += currentSample;
				block.setSample(i, startSample, voic_sample);
			}

			currentAngle += angleDelta;
			if (currentAngle > (MathConstants<double>::twoPi))
			{
				currentAngle -= MathConstants<double>::twoPi;
			}
		}
	}
}

int Chorus::transposeMulti(juce::dsp::AudioBlock<float>& dest, juce::dsp::AudioBlock<float> src, int &srcSamples, int numChannels)
{
	int i;
	int srcSampleEnd = srcSamples - 4;
	int srcCount = 0;
	int inc = 0;
	double rate = p;

//	if (p >= 1.0f)
//	{
//		int j, k, end;
//		// when using floating point samples, use a scaler instead of a divider
//		// because division is much slower operation than multiplying.
//		double dScaler = 1.0 / (double)resultDivider;
//
//		assert(filterCoeffs != NULL);
//
//		end = 2 * (srcSamples - 64);
//
//#pragma omp parallel for
//		for (j = 0, k = 0; j < end; j += 2, k++)
//		{
//			const float *ptr;
//			double suml, sumr;
//			unsigned int i;
//
//			suml = sumr = 0;
//			ptr = src.getChannelPointer(0) + j;
//			for (i = 0; i < 64; i += 4)
//			{
//				// loop is unrolled by factor of 4 here for efficiency
//				suml += ptr[2 * i + 0] * filterCoeffs[i + 0] +
//					ptr[2 * i + 2] * filterCoeffs[i + 1] +
//					ptr[2 * i + 4] * filterCoeffs[i + 2] +
//					ptr[2 * i + 6] * filterCoeffs[i + 3];
//				sumr += ptr[2 * i + 1] * filterCoeffs[i + 0] +
//					ptr[2 * i + 3] * filterCoeffs[i + 1] +
//					ptr[2 * i + 5] * filterCoeffs[i + 2] +
//					ptr[2 * i + 7] * filterCoeffs[i + 3];
//			}
//
//			suml *= dScaler;
//			sumr *= dScaler;
//
//			dest.setSample(0, k, (float)suml);
//			dest.setSample(1, k, (float)sumr);
//		}
//	}

	i = 0;
	while (srcCount < srcSampleEnd)
	{
		const float x3 = 1.0f;
		const float x2 = (float)fract;    // x
		const float x1 = x2 * x2;           // x^2
		const float x0 = x1 * x2;           // x^3
		float y0, y1, y2, y3;

		y0 = _coeffs[0] * x0 + _coeffs[1] * x1 + _coeffs[2] * x2 + _coeffs[3] * x3;
		y1 = _coeffs[4] * x0 + _coeffs[5] * x1 + _coeffs[6] * x2 + _coeffs[7] * x3;
		y2 = _coeffs[8] * x0 + _coeffs[9] * x1 + _coeffs[10] * x2 + _coeffs[11] * x3;
		y3 = _coeffs[12] * x0 + _coeffs[13] * x1 + _coeffs[14] * x2 + _coeffs[15] * x3;

		for (int c = 0; c < numChannels; c++)
		{
			float out;
			out = (y0 * src.getSample(c, inc)) + (y1 * src.getSample(c, inc + 1)) + (y2 * src.getSample(c, inc + 2)) + (y3 * src.getSample(c, inc + 3));
			//out = y0 * psrc[c] + y1 * psrc[c + numChannels] + y2 * psrc[c + 2 * numChannels] + y3 * psrc[c + 3 * numChannels];
			dest.setSample(c, i, out);
			//pdest[0] = (float)out;
			//pdest++;
		}
		i++;

		// update position fraction
		fract += rate;
		// update whole positions
		int whole = (int)fract;
		fract -= whole;
		inc += whole;
		//psrc += numChannels * whole;
		srcCount += whole;
	}
	srcSamples = srcCount;

//	if (p < 1.0f)
//	{
//		int j, k, end;
//		// when using floating point samples, use a scaler instead of a divider
//		// because division is much slower operation than multiplying.
//		double dScaler = 1.0 / (double)resultDivider;
//
//		assert(filterCoeffs != NULL);
//
//		end = 2 * (srcSamples - 64);
//
//#pragma omp parallel for
//		for (j = 0, k = 0; j < end; j += 2, k++)
//		{
//			const float *ptr;
//			double suml, sumr;
//			unsigned int i;
//
//			suml = sumr = 0;
//			ptr = src.getChannelPointer(0) + j;
//			for (i = 0; i < 64; i += 4)
//			{
//				// loop is unrolled by factor of 4 here for efficiency
//				suml += ptr[2 * i + 0] * filterCoeffs[i + 0] +
//					ptr[2 * i + 2] * filterCoeffs[i + 1] +
//					ptr[2 * i + 4] * filterCoeffs[i + 2] +
//					ptr[2 * i + 6] * filterCoeffs[i + 3];
//				sumr += ptr[2 * i + 1] * filterCoeffs[i + 0] +
//					ptr[2 * i + 3] * filterCoeffs[i + 1] +
//					ptr[2 * i + 5] * filterCoeffs[i + 2] +
//					ptr[2 * i + 7] * filterCoeffs[i + 3];
//			}
//
//			suml *= dScaler;
//			sumr *= dScaler;
//
//			dest.setSample(0, k, (float)suml);
//			dest.setSample(1, k, (float)sumr);
//		}
//	}

	return i;
}


void Chorus::releaseResources()
{
}

void Chorus::sliderValueChanged(Slider* slider)
{
	if (slider->getName() == "mix_knob")
	{
		m = slider->getValue();
	}
	else if (slider->getName() == "pitch_knob")
	{
		p = slider->getValue();

		setCoeffs();
	}
	else if (slider->getName() == "width_knob")
	{
		w = slider->getValue();
	}
	else if (slider->getName() == "speed_knob")
	{
		s = slider->getValue();
	}
	else if (slider->getName() == "depth_knob")
	{
		d = slider->getValue();
	}
}

void Chorus::setCoeffs()
{
	int length = 64;
	double cutoffFreq = p > 1.0 ? 0.5 / p : 0.5 * p;
	unsigned int i;
	double cntTemp, temp, tempCoeff, h, w;
	double wc;
	double scaleCoeff, sum;
	double *work;
	float *coeffs;

	assert(length >= 2);
	assert(length % 4 == 0);
	assert(cutoffFreq >= 0);
	assert(cutoffFreq <= 0.5);

	work = new double[length];
	coeffs = new float[length];

	wc = 2.0 * MathConstants<double>::pi * cutoffFreq;
	tempCoeff = MathConstants<double>::twoPi / (double)length;

	sum = 0;
	for (i = 0; i < length; i++)
	{
		cntTemp = (double)i - (double)(length / 2);

		temp = cntTemp * wc;
		if (temp != 0)
		{
			h = sin(temp) / temp;                     // sinc function
		}
		else
		{
			h = 1.0;
		}
		w = 0.54 + 0.46 * cos(tempCoeff * cntTemp);       // hamming window

		temp = w * h;
		work[i] = temp;

		// calc net sum of coefficients 
		sum += temp;
	}

	// ensure the sum of coefficients is larger than zero
	assert(sum > 0);

	// ensure we've really designed a lowpass filter...
	assert(work[length / 2] > 0);
	assert(work[length / 2 + 1] > -1e-6);
	assert(work[length / 2 - 1] > -1e-6);

	// Calculate a scaling coefficient in such a way that the result can be
	// divided by 16384
	scaleCoeff = 16384.0f / sum;

	for (i = 0; i < length; i++)
	{
		temp = work[i] * scaleCoeff;
		// scale & round to nearest integer
		temp += (temp >= 0) ? 0.5 : -0.5;
		// ensure no overfloods
		assert(temp >= -32768 && temp <= 32767);
		coeffs[i] = (float)(temp / 16384.0f);
	}

	// Set coefficients. Use divide factor 14 => divide result by 2^14 = 16384


	delete[] filterCoeffs;
	filterCoeffs = new float[64];
	memcpy(filterCoeffs, coeffs, 64 * sizeof(float));

	delete[] work;
	delete[] coeffs;
}