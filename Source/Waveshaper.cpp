/*
  ==============================================================================

    Waveshaper.cpp
    Created: 31 Dec 2018 12:36:40pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "Waveshaper.h"

//==============================================================================
Waveshaper::Waveshaper()
{
	initialiseWaveshaper();

	initialiseUI();
}

Waveshaper::~Waveshaper()
{
}

void Waveshaper::initialiseUI()
{
	// Cutoff
	cutoff.setRange(1.0f, 4.0f, 3.0f / 150);
	cutoff.setValue(2.5f);
	cutoff.addListener(this);
	cutoff.setName("cutoff_knob");
	addAndMakeVisible(cutoff);

	lCutoff.setFont(Font(16.0f, Font::plain));
	lCutoff.setColour(Label::textColourId, Colours::white);
	lCutoff.setJustificationType(Justification::centred);
	addAndMakeVisible(lCutoff);

	// Slope
	slope.setRange(0.0f, 127.0f, 1.0);
	slope.setValue(0.0f);
	slope.addListener(this);
	slope.setName("slope_knob");
	slope.setEnabled(false);
	addAndMakeVisible(slope);

	lSlope.setFont(Font(16.0f, Font::plain));
	lSlope.setColour(Label::textColourId, Colours::lightgrey);
	lSlope.setJustificationType(Justification::centred);
	addAndMakeVisible(lSlope);

	// Resonance
	res.setRange(1.0f, 3.0f, 0.05f);
	res.setValue(1.0f);
	res.addListener(this);
	res.setName("res_knob");
	addAndMakeVisible(res);

	lRes.setFont(Font(16.0f, Font::plain));
	lRes.setColour(Label::textColourId, Colours::white);
	lRes.setJustificationType(Justification::centred);
	addAndMakeVisible(lRes);

	// Enable button
	enable.setButtonText("Enable");
	enable.addListener(this);
	enable.changeWidthToFitText();
	addAndMakeVisible(enable);

	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(150, 160);
}

void Waveshaper::initialiseWaveshaper()
{
}

void Waveshaper::updateWaveshaper()
{
	sliderValueChanged(&cutoff);
	sliderValueChanged(&slope);
	sliderValueChanged(&res);
}

//==============================================================================
void Waveshaper::paint(Graphics& g)
{
}

void Waveshaper::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor...
	enable.setBounds(getWidth() - 57.0f, 2.0f, 50.0f, 18.0f);

	cutoff.setBounds(0.0f, getHeight() - 57.5f, 50.0f, 50.0f);
	lCutoff.setBounds(0.0f, getHeight() - 15.0f, 50.0f, 15.0f);

	slope.setBounds(50.0f, getHeight() - 57.5f, 50.0f, 50.0f);
	lSlope.setBounds(50.0f, getHeight() - 15.0f, 50.0f, 15.0f);

	res.setBounds(100.0f, getHeight() - 57.5f, 50.0f, 50.0f);
	lRes.setBounds(100.0f, getHeight() - 15.0f, 50.0f, 15.0f);
}

void Waveshaper::processSamples(AudioBuffer<float>& buffer, int numSamples)
{
	
}

void Waveshaper::releaseResources()
{

}

void Waveshaper::sliderValueChanged(Slider* slider)
{
	if (isActive)
	{
		
	}
}