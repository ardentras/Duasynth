/*
  ==============================================================================

    SawWaveVoice.h
    Created: 17 Dec 2018 8:10:13pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DuasynthWaveVoice.h"

class SawWaveVoice : public DuasynthWaveVoice
{
public:
	SawWaveVoice() : coarse(0.0), fine(0.0), oct(0.0) {}
	~SawWaveVoice() {}

	bool canPlaySound(SynthesiserSound*) override;
	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
	void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
	void stopNote(float velocity, bool allowTailOff) override;

	/** Called to let the voice know that the pitch wheel has been moved.
		This will be called during the rendering callback, so must be fast and thread-safe.
	*/
	void pitchWheelMoved(int newPitchWheelValue) override {}

	/** Called to let the voice know that a midi controller has been moved.
		This will be called during the rendering callback, so must be fast and thread-safe.
	*/
	void controllerMoved(int controllerNumber, int newControllerValue) override {}

	/** Called to let the voice know that the aftertouch has changed.
		This will be called during the rendering callback, so must be fast and thread-safe.
	*/
	void aftertouchChanged(int newAftertouchValue) {}

	/** Called to let the voice know that the channel pressure has changed.
		This will be called during the rendering callback, so must be fast and thread-safe.
	*/
	void channelPressureChanged(int newChannelPressureValue) override {}

	/** Changes the voice's reference sample rate.

		The rate is set so that subclasses know the output rate and can set their pitch
		accordingly.

		This method is called by the synth, and subclasses can access the current rate with
		the currentSampleRate member.
	*/
	void setCurrentPlaybackSampleRate(double newRate) override { SynthesiserVoice::setCurrentPlaybackSampleRate(newRate);  }

	void setOct(double val) { angleDelta *= std::pow(2.0, val - oct); oct = val; }
	void setCoarse(double val) { angleDelta *= std::pow(2.0, ((val - coarse) * 100.0) / 1200.0); coarse = val; }
	void setFine(double val) { angleDelta *= std::pow(2.0, (val - fine) / 1200.0); fine = val; }
	void setVolume(double val) { volume = val; }

private:
	double currentAngle;
	double angleDelta;
	double level;
	double tailOff;

	double coarse;
	double fine;
	double oct;
	double volume;
};