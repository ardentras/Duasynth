/*
  ==============================================================================

    SawWaveVoice.cpp
    Created: 17 Dec 2018 8:10:14pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "SawWaveVoice.h"

bool SawWaveVoice::canPlaySound(SynthesiserSound* sound)
{
	return true;
}

void SawWaveVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
	currentAngle = 0.0;
	level = velocity * 0.15;
	tailOff = 0.0;

	auto cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	auto cyclesPerSample = cyclesPerSecond / getSampleRate();
	angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
}

void SawWaveVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
	if (angleDelta != 0.0)
	{
		if (tailOff > 0.0) // [7]
		{
			while (--numSamples >= 0)
			{
				auto currentSample = (float)(std::sin(currentAngle) * level * tailOff);
				for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
					outputBuffer.addSample(i, startSample, currentSample);
				currentAngle += angleDelta;
				++startSample;
				tailOff *= 0.99; // [8]
				if (tailOff <= 0.005)
				{
					clearCurrentNote(); // [9]
					angleDelta = 0.0;
					break;
				}
			}
		}
		else
		{
			while (--numSamples >= 0) // [6]
			{
				auto currentSample = (float)(std::sin(currentAngle) * level);
				for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
					outputBuffer.addSample(i, startSample, currentSample);
				currentAngle += angleDelta;
				++startSample;
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
