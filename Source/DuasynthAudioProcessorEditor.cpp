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
	: AudioProcessorEditor(&p), processor(p)
{
	addAndMakeVisible(processor.getAOsc());
	addAndMakeVisible(processor.getBOsc());

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
	
	processor.getAOsc().setBounds(ELEM_PADDING, ELEM_PADDING, processor.getAOsc().getWidth(), processor.getAOsc().getHeight());
	processor.getBOsc().setBounds((ELEM_PADDING * 2) + processor.getAOsc().getWidth(), ELEM_PADDING, processor.getBOsc().getWidth(), processor.getBOsc().getHeight());
}
