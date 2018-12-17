/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "DuasynthAudioProcessor.h"
#include "DuasynthAudioProcessorEditor.h"

//==============================================================================
DuasynthAudioProcessorEditor::DuasynthAudioProcessorEditor(DuasynthAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p), a_osc()
{
	addAndMakeVisible(a_osc);
	setSize (500, 600);
}

DuasynthAudioProcessorEditor::~DuasynthAudioProcessorEditor()
{
}

//==============================================================================
void DuasynthAudioProcessorEditor::paint (Graphics& g)
{
}

void DuasynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	
	a_osc.setBounds(0.0f, 0.0f, a_osc.getWidth(), a_osc.getHeight());
}
