/*
  ==============================================================================

    WhiteNoiseVoice.cpp
    Created: 13 Feb 2019 4:26:48pm
    Author:  shaun.rasmusen

  ==============================================================================
*/
#include <cmath>

#include "WhiteNoiseVoice.h"

bool WhiteNoiseVoice::canPlaySound(SynthesiserSound* sound)
{
	return true;
}

void WhiteNoiseVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
	currentAngle = 0.0;
	level = velocity * 0.15;
	tailOff = 0.0;

	double cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber) * std::pow(2.0, ((oct * 1200.0) + (coarse * 100.0) + fine) / 1200.0);
	double cyclesPerSample = cyclesPerSecond / getSampleRate();
	angleDelta = 1.0;
}

void WhiteNoiseVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
	if (angleDelta != 0.0)
	{
		if (tailOff > 0.0)
		{
			while (--numSamples >= 0)
			{
				double currentSample = (((level * (volume / 127.0f)) * angleDelta)) * tailOff * unif(re);

				for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
					outputBuffer.addSample(i, startSample, currentSample);
				++startSample;
				tailOff *= 0.99;
				if (tailOff <= 0.005)
				{
					clearCurrentNote();
					angleDelta = 0.0;
					break;
				}
			}
		}
		else
		{
			while (--numSamples >= 0)
			{
				double currentSample = (((level * (volume / 127.0f)) * angleDelta)) * unif(re);

				for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
					outputBuffer.addSample(i, startSample, currentSample);
				++startSample;
			}
		}
	}
}

void WhiteNoiseVoice::stopNote(float velocity, bool allowTailOff)
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
