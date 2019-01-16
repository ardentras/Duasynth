/*
  ==============================================================================

    PresetBank.h
    Created: 14 Jan 2019 7:53:19pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once

#include <vector>
using std::vector;

#include "../JuceLibraryCode/JuceHeader.h"
#include "sqlite/sqlite3.h"

//==============================================================================
/**
*/
class PresetBank : public Component
{
public:
	PresetBank();
	~PresetBank();

	void initialiseUI();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

	void serialize(vector<Slider> params);
	vector<Slider> deserialize();

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.

	// UI Elements
	TextButton saveButton;
	TextButton loadButton;
	Label theName;

	// Practical Elements
	//ModalComponentManager modals;
	sqlite3* db;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetBank)
};
