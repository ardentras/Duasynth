/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator ()
    : synth(), coarse(), fine()
{
	addAndMakeVisible(coarse);
	addAndMakeVisible(fine);

	volume.setSliderStyle(Slider::LinearBarVertical);
	volume.setRange(0.0, 127.0, 1.0);
	volume.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	volume.setValue(1.0);
	addAndMakeVisible(volume);

	addAndMakeVisible(wfView);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (150, 100);
}

Oscillator::~Oscillator()
{
}

//==============================================================================
void Oscillator::paint (Graphics& g)
{
	g.setColour(Colour(0.0f, 0.0f, 0.0f, 1.0f));
	g.fillRect(15.0f, 2.0f, getWidth() - 22.0f, getHeight() / 2.0f);
}

void Oscillator::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	auto area = getLocalBounds();

	auto dialArea = area.removeFromTop(area.getHeight() / 2);
	coarse.setBounds(50.0f, getHeight() - 50.0f, 50.0f, 50.0f);
	fine.setBounds(100.0f, getHeight() - 50.0f, 50.0f, 50.0f);

	volume.setBounds(2.0f, 2.0f, 10.0f, getHeight() - 2.0f);

	wfView.setBounds(24.0f, 10.0f, getWidth() - 34.0f, (getWidth() - 34.0f) / 2);
}
