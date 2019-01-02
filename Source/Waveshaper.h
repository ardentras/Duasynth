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

	void prepareToPlay(double sampleRate, int samplesPerBlock) { processorChain.prepare({ sampleRate, (uint32)samplesPerBlock, 2 }); }
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
			button->setButtonText("Enable");
		}
		else
		{
			isActive = true;
			button->setButtonText("Disable");
		}
	}

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.

	bool isActive;

	// UI Elements
	Label theName;
	Label lMix;
	Knob mix;
	Label lVolume;
	Knob volume;
	Label lAttack;
	Knob attack;
	Label lKnee;
	Knob knee;
	Label lCurve;
	Knob curve;
	TextButton enable;

	// Practical Elements
	juce::dsp::ProcessorChain<juce::dsp::Gain<float>, juce::dsp::WaveShaper<float>, juce::dsp::Gain<float>> processorChain;

	double sampleRate;
	double m;
	double a;
	double k;
	double c;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Waveshaper)
};
