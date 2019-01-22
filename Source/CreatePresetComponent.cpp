/*
  ==============================================================================

    CreatePresetComponent.cpp
    Created: 21 Jan 2019 3:32:17pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "CreatePresetComponent.h"

CreatePresetComponent::CreatePresetComponent()
	: theName("name_label", "Create Preset"), cancelButton("cancel", ""), saveButton("save", ""), text("text")
{
	initialiseUI();
}

CreatePresetComponent::~CreatePresetComponent()
{
}

void CreatePresetComponent::initialiseUI()
{
	// Name
	theName.setFont(Font(16.0f, Font::plain));
	theName.setColour(Label::textColourId, Colours::black);
	theName.setJustificationType(Justification::centred);
	addAndMakeVisible(theName);

	// Text Input
	text.setMultiLine(false);
	text.setFont(Font(16.0f, Font::plain));
	text.setColour(Label::textColourId, Colours::black);
	addAndMakeVisible(text);

	// Load button
	cancelButton.setButtonText("Cancel");
	cancelButton.changeWidthToFitText();
	cancelButton.addListener(this);
	addAndMakeVisible(cancelButton);

	// Save button
	saveButton.setButtonText("Save");
	saveButton.changeWidthToFitText();
	saveButton.addListener(this);
	addAndMakeVisible(saveButton);

	setSize(150, 100);
}

void CreatePresetComponent::paint(Graphics&)
{

}

void CreatePresetComponent::resized()
{
	theName.setBounds(0.0f, 0.0f, getWidth(), 25.0f);

	text.setBounds(10.0f, 25.0f, getWidth() - 20.0f, 25.0f);

	cancelButton.setBounds(10.0f, 65.0f, 55.0f, 25.0f);

	saveButton.setBounds(85.0f, 65.0f, 55.0f, 25.0f);
}

void CreatePresetComponent::buttonClicked(Button* button)
{
	if (button->getName() == "save")
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