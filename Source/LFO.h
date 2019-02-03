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

//==============================================================================
/**
*/
class LFO : public Component, private Slider::Listener, private Button::Listener
{
public:
	LFO();
	~LFO();

	void initialiseUI();
	void initialiseLFO();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

	void prepareToPlay(double sampleRate, int samplesPerBlock);
	void releaseResources();
	void getNextAudioBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages);

	void sliderValueChanged(Slider* slider) override;
	void sliderDragEnded(Slider* slider) override;

	void updateLFO();

	string getCurrWF() { return curr_wf; }

	bool isLFOActive() { return isActive; }

	void buttonClicked(Button* button) {
		if (button->getName() == "enable")
		{
			if (isActive)
			{
				en = 1;
				isActive = false;
				button->setButtonText("Enable");
			}
			else
			{
				en = 0;
				isActive = true;
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
			}
			else
			{
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
	vector<string> waveforms;

	double a;
	double f;
	int wf;
	double v;
	int en;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LFO)
};
