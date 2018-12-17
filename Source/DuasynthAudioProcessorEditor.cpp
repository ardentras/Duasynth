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
	addAndMakeVisible(b_osc);

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
	
	a_osc.setBounds(ELEM_PADDING, ELEM_PADDING, a_osc.getWidth(), a_osc.getHeight());
	b_osc.setBounds((ELEM_PADDING * 2) + a_osc.getWidth(), ELEM_PADDING, b_osc.getWidth(), b_osc.getHeight());
}
