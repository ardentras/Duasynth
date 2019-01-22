/*
  ==============================================================================

    LoadPresetComponent.cpp
    Created: 21 Jan 2019 3:32:26pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "LoadPresetComponent.h"

LoadPresetComponent::LoadPresetComponent()
	: theName("name_label", "Load Preset"), cancelButton("cancel", ""), loadButton("load", ""), text("text")
{
	initialiseUI();
}

LoadPresetComponent::~LoadPresetComponent()
{
}

void LoadPresetComponent::initialiseUI()
{
	// Name
	theName.setFont(Font(16.0f, Font::plain));
	theName.setColour(Label::textColourId, Colours::black);
	theName.setJustificationType(Justification::centred);
	addAndMakeVisible(theName);

	// Text Input
	text.setColour(Label::textColourId, Colours::black);
	addAndMakeVisible(text);

	// Load button
	cancelButton.setButtonText("Cancel");
	cancelButton.changeWidthToFitText();
	cancelButton.addListener(this);
	addAndMakeVisible(cancelButton);

	// Save button
	loadButton.setButtonText("Load");
	loadButton.changeWidthToFitText();
	loadButton.addListener(this);
	addAndMakeVisible(loadButton);

	setSize(150, 100);
}

void LoadPresetComponent::paint(Graphics&)
{

}

void LoadPresetComponent::resized()
{
	theName.setBounds(0.0f, 0.0f, getWidth(), 25.0f);

	text.setBounds(10.0f, 25.0f, getWidth() - 20.0f, 25.0f);

	cancelButton.setBounds(10.0f, 65.0f, 55.0f, 25.0f);

	loadButton.setBounds(85.0f, 65.0f, 55.0f, 25.0f);
}

void LoadPresetComponent::buttonClicked(Button* button)
{
	if (button->getName() == "load")
	{
		DialogWindow* dw = this->findParentComponentOfClass<DialogWindow>();

		dw->exitModalState(2);
	}
	else if (button->getName() == "cancel")
	{
		DialogWindow* dw = this->findParentComponentOfClass<DialogWindow>();
		dw->exitModalState(1);
	}
}