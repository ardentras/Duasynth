/*
  ==============================================================================

    SawWaveVoice.cpp
    Created: 17 Dec 2018 8:10:14pm
    Author:  shaun.rasmusen

  ==============================================================================
*/
#include <cmath>
#include <math.h>

#include "SawWaveVoice.h"

bool SawWaveVoice::canPlaySound(SynthesiserSound* sound)
{
	return true;
}

void SawWaveVoice::startNote(float f, float a)
{
	currentAngle = 0.0;
	level = a * 62;
	tailOff = 0.0;

	angleDelta = f / getSampleRate() * 2.0 * MathConstants<double>::pi;
}

void SawWaveVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
	currentAngle = 0.0;
	level = velocity * 0.15;
	tailOff = 0.0;

	double cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber) * std::pow(2.0, ((oct * 1200.0) + (coarse * 100.0) + fine) / 1200.0);
	double cyclesPerSample = cyclesPerSecond / getSampleRate();
	angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
}

double SawWaveVoice::renderNextSample()
{
	double currentSample;

	if (angleDelta != 0.0)
	{
		currentSample = (double)(level / MathConstants<double>::pi * currentAngle);
		
		currentAngle += angleDelta;

		if (currentAngle > (MathConstants<double>::twoPi))
		{
			currentAngle -= MathConstants<double>::twoPi;
		}
	}

	return currentSample;
}

void SawWaveVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
	if (angleDelta != 0.0)
	{ 
		if (tailOff > 0.0)
		{
			while (--numSamples >= 0)
			{
				double currentSample = (double)(level * (volume / 127.0f) / MathConstants<double>::pi * currentAngle * tailOff);
				for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
					outputBuffer.addSample(i, startSample, currentSample);
				
				currentAngle = fmod(currentAngle + (fm_buff == nullptr ? 1 : 1.0 - (*fm_buff * fm_level)) * angleDelta, MathConstants<double>::twoPi);

				buff = currentAngle * (volume / 127.0f);
				++startSample;
				tailOff *= 0.99;
				if (tailOff <= 0.005)
				{
					clearCurrentNote();
					angleDelta = 0.0;
					break;
				}

				if (currentAngle > (MathConstants<double>::twoPi))
				{
					currentAngle -= MathConstants<double>::twoPi;
				}
			}
		}
		else
		{
			while (--numSamples >= 0)
			{

				double currentSample = (double)(level * (volume / 127.0f) / MathConstants<double>::pi * currentAngle);
				for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
					outputBuffer.addSample(i, startSample, currentSample);
				
				currentAngle = fmod(currentAngle + (fm_buff == nullptr ? 1 : 1.0 - (*fm_buff * fm_level)) * angleDelta, MathConstants<double>::twoPi);

				buff = currentAngle * (volume / 127.0f);
				++startSample;

				if (currentAngle > (MathConstants<double>::twoPi))
				{
					currentAngle -= MathConstants<double>::twoPi;
				}
			}
		}
	}
}

void SawWaveVoice::stopNote(float velocity, bool allowTailOff)
{
	if (allowTailOff)
	{
		if (tailOff == 0.0)
			tailOff = 1.0;
	}
	else
	{
		clearCurrentNote();
		angleDelta = 0.0;
	}
}
