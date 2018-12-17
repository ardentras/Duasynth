/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "Oscillator.h"
#include "Waveforms/TriangleWaveSound.h"

//==============================================================================
Oscillator::Oscillator()
	: lCoarse("coarse_knob", "Coarse"), lFine("fine_knob", "Fine"),
	  lOctave("octave_adj", "Oct")
{
	waveforms.push_back(TriangleWaveSound());

	// Coarse tuning
	coarse.setRange(-24.0f, 24.0f, 1.0);
	coarse.setValue(0.0f);
	addAndMakeVisible(coarse);

	lCoarse.setFont(Font(16.0f, Font::plain));
	lCoarse.setColour(Label::textColourId, Colours::white);
	lCoarse.setJustificationType(Justification::centred);
	addAndMakeVisible(lCoarse);

	// Fine tuning
	fine.setRange(-24.0f, 24.0f, 1.0);
	fine.setValue(0.0f);
	addAndMakeVisible(fine);

	lFine.setFont(Font(16.0f, Font::plain));
	lFine.setColour(Label::textColourId, Colours::white);
	lFine.setJustificationType(Justification::centred);
	addAndMakeVisible(lFine);

	// Octave adj.
	octave.setSliderStyle(Slider::SliderStyle::IncDecButtons);
	octave.setRange(-2.0, 2.0, 1.0);
	octave.setTextBoxIsEditable(false);
	addAndMakeVisible(octave);

	lOctave.setFont(Font(16.0f, Font::plain));
	lOctave.setColour(Label::textColourId, Colours::white);
	lOctave.setJustificationType(Justification::centred);
	addAndMakeVisible(lOctave);

	// Volume adj.
	volume.setSliderStyle(Slider::LinearBarVertical);
	volume.setRange(0.0, 127.0, 1.0);
	volume.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	volume.setValue(1.0);
	addAndMakeVisible(volume);

	// Waveform view
	TriangleWaveSound tws;
	wfView.setWaveform(tws.getShape());
	addAndMakeVisible(wfView);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (150, 120);
}

Oscillator::~Oscillator()
{
}

//==============================================================================
void Oscillator::paint (Graphics& g)
{
}

void Oscillator::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	octave.setBounds(20.0f, getHeight() - 57.5f, 50.0f, 40.0f);
	lOctave.setBounds(20.0f, getHeight() - 15.0f, 50.0f, 15.0f);

	coarse.setBounds(65.0f, getHeight() - 57.5f, 50.0f, 50.0f);
	lCoarse.setBounds(65.0f, getHeight() - 15.0f, 50.0f, 15.0f);
	
	fine.setBounds(105.0f, getHeight() - 57.5f, 50.0f, 50.0f);
	lFine.setBounds(105.0f, getHeight() - 15.0f, 50.0f, 15.0f);

	volume.setBounds(2.0f, 2.0f, 11.0f, getHeight() - 2.0f);

	wfView.setBounds(15.0f, 2.0f, getWidth() - 17.0f, (getHeight() / 2) - 2.0f);
	wfView.setSize(wfView.getBounds().getWidth(), wfView.getBounds().getHeight());
}
