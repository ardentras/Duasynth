/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"
#include "Knob.h"
#include "WFView.h"

//==============================================================================
/**
*/
class OscillatorEditor  : public AudioProcessorEditor
{
public:
	OscillatorEditor(Oscillator& p);
    ~OscillatorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	Oscillator& processor;
	Knob coarse;
	Knob fine;
	Slider volume;
	WFView wfView;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorEditor)
};
