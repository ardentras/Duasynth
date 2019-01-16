/*
  ==============================================================================

    PresetBank.cpp
    Created: 14 Jan 2019 7:53:19pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "PresetBank.h"

PresetBank::PresetBank()
	: theName("name_label", "Presets"), loadButton("load", ""), saveButton("save", "")
{
	initialiseUI();

	sqlite3_open("file:presets.db", &db);
}

PresetBank::~PresetBank()
{
	sqlite3_close(db);
}

void PresetBank::initialiseUI()
{
	// Name
	theName.setFont(Font(24.0f, Font::plain));
	theName.setColour(Label::textColourId, Colours::white);
	theName.setJustificationType(Justification::centred);
	addAndMakeVisible(theName);

	// Load button
	loadButton.setButtonText("Load");
	loadButton.changeWidthToFitText();
	addAndMakeVisible(loadButton);

	// Save button
	saveButton.setButtonText("Save");
	saveButton.changeWidthToFitText();
	addAndMakeVisible(saveButton);

	setSize(100, 75);
}

void PresetBank::paint(Graphics&)
{

}

void PresetBank::resized()
{
	theName.setBounds(0.0f, 0.0f, getWidth(), 25.0f);

	loadButton.setBounds(5.0f, 40.0f, 40.0f, 25.0f);
	
	saveButton.setBounds(55.0f, 40.0f, 40.0f, 25.0f);
}

void PresetBank::serialize(vector<Slider> params)
{

}

vector<Slider> PresetBank::deserialize()
{

}