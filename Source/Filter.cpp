/*
  ==============================================================================

    Filter.cpp
    Created: 18 Dec 2018 9:49:48pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"
/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#include "Filter.h"
#include "Waveforms/SawWaveSound.h"
#include "Waveforms/SawWaveVoice.h"
#include "Waveforms/TriangleWaveSound.h"
#include "Waveforms/TriangleWaveVoice.h"

//==============================================================================
Filter::Filter()
	: lCutoff("cutoff_knob", "Cutoff"), lSlope("slope_knob", "Slope"),
	lRes("res_adj", "Res"), isActive(false)
{
	initialiseFilter();

	initialiseUI();
}

Filter::~Filter()
{
}

void Filter::initialiseUI()
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
	slope.setValue(127.0 * 0.5);
	slope.addListener(this);
	slope.setName("slope_knob");
	addAndMakeVisible(slope);

	lSlope.setFont(Font(16.0f, Font::plain));
	lSlope.setColour(Label::textColourId, Colours::white);
	lSlope.setJustificationType(Justification::centred);
	addAndMakeVisible(lSlope);

	// Resonance
	res.setRange(1.0f, 6.0f, 0.05f);
	res.setValue(3.5f);
	res.addListener(this);
	res.setName("res_knob");
	addAndMakeVisible(res);

	lRes.setFont(Font(16.0f, Font::plain));
	lRes.setColour(Label::textColourId, Colours::white);
	lRes.setJustificationType(Justification::centred);
	addAndMakeVisible(lRes);

	// Filter select
	filterSelect.setSliderStyle(Slider::SliderStyle::IncDecButtons);
	filterSelect.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	filterSelect.setMinAndMaxValues(0.0, 1.0);
	filterSelect.setRange(filterSelect.getMinValue(), filterSelect.getMaxValue(), 1.0);
	filterSelect.setTextBoxIsEditable(false);
	filterSelect.addListener(this);
	filterSelect.setName("filter_select");
	addAndMakeVisible(filterSelect);

	// Filter view
	addAndMakeVisible(filterView);

	// Enable button
	enable.setButtonText("Enable");
	enable.addListener(this);
	enable.changeWidthToFitText();
	addAndMakeVisible(enable);

	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(150, 160);
}

void Filter::initialiseFilter()
{
}

void Filter::updateFilter()
{
	//filterView.setFilter(temp->getShape());

	sliderValueChanged(&cutoff);
	sliderValueChanged(&slope);
	sliderValueChanged(&res);
}

//==============================================================================
void Filter::paint(Graphics& g)
{
}

void Filter::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor...
	enable.setBounds(getWidth() - 57.0f, 2.0f, 50.0f, 18.0f);

	filterSelect.setBounds(10.0f, 2.0f, 50.0f, 18.0f);

	filterView.setBounds(10.0f, 22.0f, getWidth() - 17.0f, (getHeight() / 2) - 2.0f);
	filterView.setSize(filterView.getBounds().getWidth(), filterView.getBounds().getHeight());

	cutoff.setBounds(0.0f, getHeight() - 57.5f, 50.0f, 50.0f);
	lCutoff.setBounds(0.0f, getHeight() - 15.0f, 50.0f, 15.0f);

	slope.setBounds(50.0f, getHeight() - 57.5f, 50.0f, 50.0f);
	lSlope.setBounds(50.0f, getHeight() - 15.0f, 50.0f, 15.0f);

	res.setBounds(100.0f, getHeight() - 57.5f, 50.0f, 50.0f);
	lRes.setBounds(100.0f, getHeight() - 15.0f, 50.0f, 15.0f);
}

void Filter::processSamples(AudioBuffer<float>& buffer, int numSamples)
{
	bool added_filters = false;
	while (filter.size() < buffer.getNumChannels())
	{
		IIRFilter* f = new IIRFilter();
		f->makeInactive();
		filter.push_back(f);
		added_filters = true;
	}

	if (added_filters)
	{
		updateFilter();
	}

	for (int channel = 0; channel < buffer.getNumChannels(); channel++)
	{
		filter[channel]->processSamples(buffer.getWritePointer(channel), numSamples);
	}
}

void Filter::releaseResources()
{
	for (int i = 0; i < filter.size(); i++)
	{
		filter[i]->reset();
	}
}

void Filter::sliderValueChanged(Slider* slider)
{
	if (isActive)
	{
		if (slider->getName() == "cutoff_knob")
		{
			f = slider->getValue();
		}
		else if (slider->getName() == "slope_knob")
		{

		}
		else if (slider->getName() == "res_knob")
		{
			q = slider->getValue();
		}

		for (int i = 0; i < filter.size(); i++)
		{
			filter[i]->setCoefficients(IIRCoefficients::makeLowPass(sampleRate, 2.0 * pow(10, f), q));
		}
	}
}

void Filter::sliderDragEnded(Slider* slider)
{
	if (slider->getName() == "filter_select")
	{

	}
}
