/*
  ==============================================================================

    Chorus.h
    Created: 22 Jan 2019 6:33:16pm
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

#include <cassert>

#include "../JuceLibraryCode/JuceHeader.h"

#include "Stk/DelayL.h"
using stk::DelayL;

#include "LFO.h"
#include "Knob.h"

//==============================================================================
/**
*/
class Chorus : public Component, private Slider::Listener, private Button::Listener
{
public:
	Chorus();
	Chorus(LFO& a, LFO& b);
	~Chorus();

	void initialiseUI();
	void initialiseChorus();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

	void prepareToPlay(double sampleRate, int samplesPerBlock);
	void processSamples(AudioBuffer<float>& buffer, int numSamples);
	void processLFO(juce::dsp::AudioBlock<float>& block, const juce::dsp::AudioBlock<float> initial, int numSamples);
	void releaseResources();

	void updateChorus();

	void sliderValueChanged(Slider* slider) override;

	void setSampleRate(double rate) { sampleRate = rate; }

	bool isChorusActive() { return isActive; }

	void setActive(bool active) { isActive = active; }

	void buttonClicked(Button* button)
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
			button->setButtonText("Disable");
		}
	}

	vector<pair<string, float>> serialize()
	{
		vector<pair<string, float>> params;

		params.push_back(pair<string, float>("mix", m));
		params.push_back(pair<string, float>("pitch", p));
		params.push_back(pair<string, float>("width", w));
		params.push_back(pair<string, float>("speed", s));
		params.push_back(pair<string, float>("depth", d));
		params.push_back(pair<string, float>("enable", en));

		return params;
	}

	void deserialize(vector<pair<string, float>> params)
	{
		for (pair<string, float> param : params)
		{
			if (param.first == "mix")
			{
				m = param.second;
				mix.setValue(m);
			}
			else if (param.first == "pitch")
			{
				p = param.second;
				pitch.setValue(p);
			}
			else if (param.first == "width")
			{
				w = param.second;
				width.setValue(w);
			}
			else if (param.first == "speed")
			{
				s = param.second;
				speed.setValue(s);
			}
			else if (param.first == "depth")
			{
				d = param.second;
				depth.setValue(d);
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

		updateChorus();
	}

private:
	// This reference is provided as s quick way for your editor to
	// access the processor object that created it.

	bool isActive;

	// UI Elements
	Label theName;
	Label lMix;
	Knob mix;
	Label lPitch;
	Knob pitch;
	Label lWidth;
	Knob width;
	Label lSpeed;
	Knob speed;
	Label lDepth;
	Knob depth;
	TextButton enable;

	// Practical Elements
	juce::dsp::Reverb::Parameters param;
	juce::dsp::ProcessorChain<juce::dsp::Reverb> processorChain;
	DelayL delayline;
	double sampleRate;
	int spb;

	double m;
	double s;
	double d;
	double p;
	double w;
	int en;

	double currentAngle;
	double angleDelta;
	double level;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Chorus)
};
