/*
  ==============================================================================

    Waveshaper.h
    Created: 31 Dec 2018 12:36:40pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "Knob.h"

//==============================================================================
/**
*/
class Waveshaper : public Component, private Slider::Listener, private Button::Listener
{
public:
	Waveshaper();
	~Waveshaper();

	void initialiseUI();
	void initialiseWaveshaper();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

	void processSamples(AudioBuffer<float>& buffer, int numSamples);
	void releaseResources();

	void updateWaveshaper();

	void sliderValueChanged(Slider* slider) override;

	void setSampleRate(double rate) { sampleRate = rate; }

	bool isWaveshaperActive() { return isActive; }

	void buttonClicked(Button* button) {
		if (isActive)
		{
			isActive = false;
		}
		else
		{
			isActive = true;
		}
	}

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.

	bool isActive;

	// UI Elements
	Label lCutoff;
	Knob cutoff;
	Label lSlope;
	Knob slope;
	Label lRes;
	Knob res;
	TextButton enable;

	// Practical Elements

	double sampleRate;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Waveshaper)
};
