/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "Oscillator.h"
#include "OscillatorEditor.h"

//==============================================================================
OscillatorEditor::OscillatorEditor (Oscillator& p)
    : AudioProcessorEditor (&p), processor (p), coarse(), fine()
{
	addAndMakeVisible(coarse);
	addAndMakeVisible(fine);

	volume.setSliderStyle(Slider::LinearBarVertical);
	volume.setRange(0.0, 127.0, 1.0);
	volume.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	volume.setValue(1.0);
	addAndMakeVisible(&volume);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 500);
}

OscillatorEditor::~OscillatorEditor()
{
}

//==============================================================================
void OscillatorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

}

void OscillatorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	auto area = getLocalBounds();

	auto dialArea = area.removeFromTop(area.getHeight() / 2);
	coarse.setBounds(dialArea.removeFromLeft(dialArea.getWidth() / 2).reduced(4));
	fine.setBounds(dialArea.reduced(4));

	volume.setBounds(300, 30, 20, getHeight() - 60);
}
