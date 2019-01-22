/*
  ==============================================================================

    LoadPresetComponent.h
    Created: 21 Jan 2019 3:32:26pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class LoadPresetComponent : public Component, private Button::Listener
{
public:
	LoadPresetComponent();
	~LoadPresetComponent();

	void initialiseUI();

	void buttonClicked(Button* button);

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.

	// UI Elements
	TextButton loadButton;
	TextButton cancelButton;
	TextEditor text;
	Label theName;

	// Practical Elements

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LoadPresetComponent)
};