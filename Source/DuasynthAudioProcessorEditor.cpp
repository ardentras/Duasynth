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
	: AudioProcessorEditor(&p), processor(p), oscs("", "Oscillators"),
	filters("", "Filters"), lfos("", "LFOs")
{
	// Oscillators label
	oscs.setFont(Font(24.0f, Font::plain));
	oscs.setColour(Label::textColourId, Colours::white);
	oscs.setJustificationType(Justification::centred);
	addAndMakeVisible(oscs);
	addAndMakeVisible(processor.getAOsc());
	addAndMakeVisible(processor.getBOsc());

	// Filters label
	filters.setFont(Font(24.0f, Font::plain));
	filters.setColour(Label::textColourId, Colours::white);
	filters.setJustificationType(Justification::centred);
	addAndMakeVisible(filters);
	addAndMakeVisible(processor.getAFilter());
	addAndMakeVisible(processor.getBFilter());

	// LFOs label
	lfos.setFont(Font(24.0f, Font::plain));
	lfos.setColour(Label::textColourId, Colours::white);
	lfos.setJustificationType(Justification::centred);
	addAndMakeVisible(lfos);

	addAndMakeVisible(preset);

	addAndMakeVisible(processor.getWaveshaper());

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
	
	// Oscillators
	oscs.setBounds(
		ELEM_PADDING, // x
		ELEM_PADDING, // y
		(processor.getAOsc().getWidth() + ELEM_PADDING) * 2, // width
		25.0f); // height
	processor.getAOsc().setBounds(
		ELEM_PADDING, 
		ELEM_PADDING + oscs.getBounds().getHeight(), 
		processor.getAOsc().getWidth(), 
		processor.getAOsc().getHeight());
	processor.getBOsc().setBounds(
		(ELEM_PADDING * 2) + processor.getAOsc().getWidth(), 
		ELEM_PADDING + oscs.getBounds().getHeight(), 
		processor.getBOsc().getWidth(), 
		processor.getBOsc().getHeight());
	
	// Filters
	filters.setBounds(
		ELEM_PADDING, 
		10.0f + ELEM_PADDING + processor.getAOsc().getHeight() + oscs.getBounds().getHeight(), 
		(processor.getAFilter().getWidth() + ELEM_PADDING) * 2, 
		25.0f);
	processor.getAFilter().setBounds(
		ELEM_PADDING, 
		10.0f + ELEM_PADDING + processor.getAOsc().getHeight() + oscs.getBounds().getHeight() + filters.getBounds().getHeight(), 
		processor.getAFilter().getWidth(), 
		processor.getAFilter().getHeight());
	processor.getBFilter().setBounds(
		(ELEM_PADDING * 2) + processor.getAFilter().getWidth(), 
		10.0f + ELEM_PADDING + processor.getAOsc().getHeight() + oscs.getBounds().getHeight() + filters.getBounds().getHeight(), 
		processor.getBFilter().getWidth(), 
		processor.getBFilter().getHeight());

	// Right Column (Preset, Chorus, WS)
	preset.setBounds(
		(ELEM_PADDING * 3) + (processor.getAFilter().getWidth() * 2) + 40,
		ELEM_PADDING,
		preset.getWidth(),
		preset.getHeight());
	processor.getWaveshaper().setBounds(
		(ELEM_PADDING * 3) + (processor.getAFilter().getWidth() * 2) + 40, 
		ELEM_PADDING + processor.getAFilter().getHeight() + processor.getWaveshaper().getHeight(), 
		processor.getWaveshaper().getWidth(), 
		processor.getWaveshaper().getHeight());
}
