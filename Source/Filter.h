/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <vector>
using std::vector;

#include <utility>
using std::pair;

#include <string>
using std::string;

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
			en = 1;
			isActive = false;
			for (int i = 0; i < filter.size(); i++)
				filter[i]->makeInactive();
			button->setButtonText("Enable");
		}
		else 
		{
			en = 0;
			isActive = true;
			updateFilter();
			button->setButtonText("Disable");
		}
	}

	vector<pair<string, float>> serialize()
	{
		vector<pair<string, float>> params;

		params.push_back(pair<string, float>("cutoff", f));
		params.push_back(pair<string, float>("slope", g));
		params.push_back(pair<string, float>("res", q));
		params.push_back(pair<string, float>("filter", ft));
		params.push_back(pair<string, float>("enable", en));

		return params;
	}

	void deserialize(vector<pair<string, float>> params)
	{
		for (pair<string, float> param : params)
		{
			if (param.first == "cutoff")
			{
				f = param.second;
			}
			else if (param.first == "slope")
			{
				g = param.second;
			}
			else if (param.first == "res")
			{
				q = param.second;
			}
			else if (param.first == "filter")
			{
				ft = param.second;
			}
			else if (param.first == "enable")
			{
				en = param.second;
			}
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
	int ft;
	int en;

	vector<FilterType*> filters;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Filter)
};
