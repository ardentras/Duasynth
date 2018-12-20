/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <vector>
using std::vector;

#include <list>
using std::list;

#include "../JuceLibraryCode/JuceHeader.h"

#include "Knob.h"
#include "FilterView.h"
#include "Filters/FilterType.h"

//==============================================================================
/**
*/
class Filter : public Component, private Slider::Listener, private Button::Listener
{
public:
	Filter();
	~Filter();

	void initialiseUI();
	void initialiseFilter();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

	void processSamples(AudioBuffer<float>& buffer, int numSamples);
	void releaseResources();

	void sliderValueChanged(Slider* slider) override;
	void sliderDragEnded(Slider* slider) override;

	void updateFilter();

	void setSampleRate(double rate) { sampleRate = rate; }

	bool isFilterActive() { return isActive; }

	void buttonClicked(Button* button) {
		if (isActive) 
		{
			isActive = false;
			for (int i = 0; i < filter.size(); i++)
				filter[i]->makeInactive();
			button->setButtonText("Enable");
		}
		else 
		{
			isActive = true;
			updateFilter();
			button->setButtonText("Disable");
		}
	}

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.

	bool isActive;

	// UI Elements
	Label lCutoff;
	Knob cutoff;
	Label lSlope;
	Knob slope;
	Label lRes;
	Knob res;
	Slider filterSelect;
	FilterView filterView;
	TextButton enable;

	// Practical Elements
	vector<IIRFilter*> filter;
	double sampleRate;
	double f;
	double g;
	double q;

	list<FilterType*> filters;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Filter)
};
