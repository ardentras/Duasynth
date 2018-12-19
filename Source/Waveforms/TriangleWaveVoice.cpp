/*
  ==============================================================================

    TriangleWaveVoice.cpp
    Created: 18 Dec 2018 3:59:55pm
    Author:  shaun.rasmusen

  ==============================================================================
*/
#include <cmath>

#include "TriangleWaveVoice.h"

bool TriangleWaveVoice::canPlaySound(SynthesiserSound* sound)
{
	return true;
}

void TriangleWaveVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
	currentAngle = 0.0;
	level = velocity * 0.15;
	tailOff = 0.0;

	double cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber) * std::pow(2.0, ((oct * 1200.0) + (coarse * 100.0) + fine) / 1200.0);
	double cyclesPerSample = cyclesPerSecond / getSampleRate();
	angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
}

void TriangleWaveVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
	if (angleDelta != 0.0)
	{
		if (tailOff > 0.0)
		{
			while (--numSamples >= 0)
			{
				double currentSample;

				if (currentAngle < MathConstants<double>::pi)
				{
					currentSample = (double)(((level * (volume / 127.0f) * -1) + ((2 * level * (volume / 127.0f) / MathConstants<double>::pi) * currentAngle)) * tailOff);
				}
				else
				{
					currentSample = (double)(((level * (volume / 127.0f) * 3) - ((2 * level * (volume / 127.0f) / MathConstants<double>::pi) * currentAngle)) * tailOff);
				}

				for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
					outputBuffer.addSample(i, startSample, currentSample);
				currentAngle += angleDelta;
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
				double currentSample;

				if (currentAngle < MathConstants<double>::pi)
				{
					currentSample = (double)((level * (volume / 127.0f) * 3) - ((2 * level * (volume / 127.0f) / MathConstants<double>::pi) * currentAngle));
				}
				else
				{
					currentSample = (double)((level * (volume / 127.0f) * -1) + ((2 * level * (volume / 127.0f) / MathConstants<double>::pi) * currentAngle));
				}

				for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
					outputBuffer.addSample(i, startSample, currentSample);
				currentAngle += angleDelta;
				++startSample;

				if (currentAngle > (MathConstants<double>::twoPi))
				{
					currentAngle -= MathConstants<double>::twoPi;
				}
			}
		}
	}
}

void TriangleWaveVoice::stopNote(float velocity, bool allowTailOff)
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
