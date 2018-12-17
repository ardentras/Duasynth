/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DuasynthAudioProcessor.h"
#include "DuasynthAudioProcessorEditor.h"
#include "Oscillator.h"

//==============================================================================
/**
*/
class DuasynthAudioProcessorEditor  : public AudioProcessorEditor
{
public:
	DuasynthAudioProcessorEditor(DuasynthAudioProcessor& p);
    ~DuasynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	DuasynthAudioProcessor& processor;
	Oscillator a_osc;
	Oscillator b_osc;

	const float ELEM_PADDING = 5.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DuasynthAudioProcessorEditor)
};
