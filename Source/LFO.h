/*
  ==============================================================================

    LFO.h
    Created: 2 Feb 2019 5:09:28pm
    Author:  shaun.rasmusen

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
#include "Waveforms/DuasynthWaveSound.h"
#include "Waveforms/DuasynthWaveVoice.h"
#include "Knob.h"
#include "WFView.h"

#define SAMPLE_RATE 512

//==============================================================================
/**
*/
class LFO : public Component, public Timer, public Slider::Listener, private Button::Listener
{
public:
	LFO();
	~LFO();

	void initialiseUI();
	void initialiseLFO();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

	void timerCallback() override;

	void sliderValueChanged(Slider* slider) override {}
	void sliderDragEnded(Slider* slider) override;

	void updateLFO();

	string getCurrWF() { return curr_wf; }

	bool isLFOActive() { return isActive; }

	bool canLFOBind() { return canBind; }

	void startLFO();
	void stopLFO();

	void addBind(Knob* knob) 
	{
		knob->setBound(true); binds.push_back(knob); 
		knob->setColour(Slider::ColourIds::rotarySliderFillColourId, Colour::fromRGB(0, 150, 0));
	}

	void removeBind(Knob* knob) 
	{
		Knob k;
		for (int i = 0; i < binds.size(); i++)
		{
			if (binds[i] == knob)
			{
				knob->setColour(Slider::ColourIds::rotarySliderFillColourId, k.findColour(Slider::ColourIds::rotarySliderFillColourId));
				knob->setBound(false);
				binds.erase(binds.begin() + i);
			}
		}
	}

	void buttonClicked(Button* button);

	vector<pair<string, float>> serialize()
	{
		vector<pair<string, float>> params;

		params.push_back(pair<string, float>("amp", a));
		params.push_back(pair<string, float>("freq", f));
		params.push_back(pair<string, float>("wf", wf));
		params.push_back(pair<string, float>("enable", en));

		return params;
	}

	void deserialize(vector<pair<string, float>> params);

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.

	bool isActive;
	bool canBind;

	// UI Elements
	Label lAmp;
	Knob amplitude;
	Label lFreq;
	Knob freq;
	Slider wfSelect;
	WFView wfView;
	TextButton bind;
	TextButton enable;

	// Practical Elements
	string curr_wf;
	DuasynthWaveVoice* generator;
	vector<string> waveforms;
	vector<Knob*> binds;
	double val, last_val;

	double a;
	double f;
	int wf;
	double v;
	int en;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LFO)
};
