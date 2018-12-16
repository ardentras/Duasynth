/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DuasynthAudioProcessor.h"

//==============================================================================
/**
*/
class DuasynthAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    DuasynthAudioProcessorEditor (DuasynthAudioProcessor&);
    ~DuasynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DuasynthAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DuasynthAudioProcessorEditor)
};
