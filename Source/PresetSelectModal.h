/*
  ==============================================================================

    PresetSelectModal.h
    Created: 14 Jan 2019 7:53:46pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class PresetSelectModal : public Component, private Button::Listener
{
public:
	PresetSelectModal();
	~PresetSelectModal();

	void initialiseUI();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

	void buttonClicked(Button* button) override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.

	// UI Elements
	TextButton selectButton;
	TextButton cancelButton;

	// Practical Elements
	ListBox presetList;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetSelectModal)
};
