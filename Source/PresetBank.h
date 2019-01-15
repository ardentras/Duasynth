/*
  ==============================================================================

    PresetBank.h
    Created: 14 Jan 2019 7:53:19pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class PresetBank : public Component, private Button::Listener
{
public:
	PresetBank();
	~PresetBank();

	void initialiseUI();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

	void buttonClicked(Button* button) override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.

	// UI Elements
	TextButton saveButton;
	TextButton loadButton;
	Label theName;

	// Practical Elements
	//ModalComponentManager modals;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetBank)
};
