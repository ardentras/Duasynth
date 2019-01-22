/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <utility>
using std::pair;

#include <vector>
using std::vector;

#include "../JuceLibraryCode/JuceHeader.h"
#include "DuasynthAudioProcessor.h"
#include "DuasynthAudioProcessorEditor.h"
#include "CreatePresetComponent.h"
#include "LoadPresetComponent.h"
#include "PresetBank.h"

//==============================================================================
/**
*/
class DuasynthAudioProcessorEditor  : public AudioProcessorEditor, private Button::Listener
{
public:
	DuasynthAudioProcessorEditor() : AudioProcessorEditor(nullptr), processor(DuasynthAudioProcessor()) {}
	DuasynthAudioProcessorEditor(DuasynthAudioProcessor& p);
    ~DuasynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	void buttonClicked(Button* button) override;

	DuasynthAudioProcessor& getProcessor() { return processor; }

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	DuasynthAudioProcessor& processor;
	Label oscs;
	Label filters;
	Label lfos;

	PresetBank preset;

	const float ELEM_PADDING = 5.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DuasynthAudioProcessorEditor)
};
