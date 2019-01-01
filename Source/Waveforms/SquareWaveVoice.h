/*
  ==============================================================================

	TriangleWaveVoice.h
	Created: 18 Dec 2018 3:59:55pm
	Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DuasynthWaveVoice.h"

class SquareWaveVoice : public DuasynthWaveVoice
{
public:
	SquareWaveVoice() {}
	~SquareWaveVoice() {}

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
	void setCurrentPlaybackSampleRate(double newRate) override { SynthesiserVoice::setCurrentPlaybackSampleRate(newRate); }
};