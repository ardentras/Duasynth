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

#include <windows.h>

#include "../JuceLibraryCode/JuceHeader.h"
#include "Waveforms/DuasynthWaveSound.h"
#include "Waveforms/DuasynthWaveVoice.h"
#include "Knob.h"
#include "WFView.h"

#define SAMPLE_RATE 4096

//==============================================================================
/**
*/
class LFO : public Component, public Slider::Listener, private Button::Listener
{
public:
	LFO();
	~LFO();

	void initialiseUI();
	void initialiseLFO();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

	double tick();

	void sliderValueChanged(Slider* slider) override;
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

	void buttonClicked(Button* button) {
		if (button->getName() == "enable")
		{
			if (isActive)
			{
				en = 1;
				stopLFO();
				button->setButtonText("Enable");
			}
			else
			{
				en = 0;
				startLFO();
				updateLFO();
				button->setButtonText("Disable");
			}
		}
		else if (button->getName() == "bind")
		{
			if (canBind)
			{
				canBind = false;
				button->setToggleState(canBind, false);

				Knob knob;
				for (Knob* k : binds)
				{
					k->setColour(Slider::ColourIds::rotarySliderFillColourId, knob.findColour(Slider::ColourIds::rotarySliderFillColourId));
				}
			}
			else
			{
				for (Knob* k : binds)
				{
					k->setColour(Slider::ColourIds::rotarySliderFillColourId, Colour::fromRGB(0, 150, 0));
				}
				canBind = true;
				button->setToggleState(canBind, false);
			}
		}
	}

	vector<pair<string, float>> serialize()
	{
		vector<pair<string, float>> params;

		params.push_back(pair<string, float>("amp", a));
		params.push_back(pair<string, float>("freq", f));
		params.push_back(pair<string, float>("wf", wf));
		params.push_back(pair<string, float>("enable", en));

		return params;
	}

	void deserialize(vector<pair<string, float>> params)
	{
		for (pair<string, float> param : params)
		{
			if (param.first == "amp")
			{
				a = param.second;
				amplitude.setValue(a);
			}
			else if (param.first == "freq")
			{
				f = param.second;
				freq.setValue(f);
			}
			else if (param.first == "wf")
			{
				wf = param.second;
				curr_wf = waveforms.at(wf);
			}
			else if (param.first == "enable")
			{
				en = param.second;

				if (en == 1)
				{
					isActive = false;
					enable.setButtonText("Enable");
				}
				else
				{
					isActive = true;
					enable.setButtonText("Disable");
				}
			}
		}

		updateLFO();
	}

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
	AudioBuffer<double> buff;
	vector<string> waveforms;
	vector<Knob*> binds;

	DWORD threadID;
	HANDLE thread;

	double a;
	double f;
	int wf;
	double v;
	int en;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LFO)
};
