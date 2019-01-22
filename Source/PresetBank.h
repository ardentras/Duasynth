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

#include <string>
using std::string;

#include <utility>
using std::pair;

#include "../JuceLibraryCode/JuceHeader.h"
#include "sqlite/sqlite3.h"

#include "Preset.h"

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

	ComboBox* getPresets();
	void store(string name, vector<pair<string, vector<pair<string, float>>>> params);
	vector<pair<string, vector<pair<string, float>>>> unstore(string name);

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
	Preset curr_preset;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetBank)
};
