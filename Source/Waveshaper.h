/*
  ==============================================================================

    Waveshaper.h
    Created: 31 Dec 2018 12:36:40pm
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

#include "LFO.h"
#include "Knob.h"

//==============================================================================
/**
*/
class Waveshaper : public Component, private Slider::Listener, private Button::Listener
{
public:
	Waveshaper();
	Waveshaper(LFO& a, LFO& b);
	~Waveshaper();

	void initialiseUI();
	void initialiseWaveshaper();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

	void prepareToPlay(double sampleRate, int samplesPerBlock);
	void processSamples(AudioBuffer<float>& buffer, int numSamples);
	void releaseResources();

	void updateWaveshaper();

	void sliderValueChanged(Slider* slider) override;

	void setSampleRate(double rate) { sampleRate = rate; }

	bool isWaveshaperActive() { return isActive; }

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

	void resetParams()
	{
		if (a > 0.0f)
		{
			da = 0.0f;
			dc = (dda * -1.0f) * c;
		}
	}

	vector<pair<string, float>> serialize()
	{
		vector<pair<string, float>> params;

		params.push_back(pair<string, float>("mix", m));
		params.push_back(pair<string, float>("pregain", preg));
		params.push_back(pair<string, float>("postgain", postg));
		params.push_back(pair<string, float>("attack", a));
		params.push_back(pair<string, float>("curve", c));
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
			else if (param.first == "pregain")
			{
				preg = param.second;
				pregain.setValue(preg);
			}
			else if (param.first == "postgain")
			{
				postg = param.second;
				postgain.setValue(postg);
			}
			else if (param.first == "attack")
			{
				a = param.second;
				attack.setValue(a);
			}
			else if (param.first == "curve")
			{
				c = param.second;
				curve.setValue(c);
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

		updateWaveshaper();
	}

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.

	bool isActive;

	// UI Elements
	Label theName;
	Label lMix;
	Knob mix;
	Label lPregain;
	Knob pregain;
	Label lPostgain;
	Knob postgain;
	Label lAttack;
	Knob attack;
	Label lCurve;
	Knob curve;
	TextButton enable;

	// Practical Elements
	juce::dsp::ProcessorChain<juce::dsp::Gain<float>, juce::dsp::WaveShaper<float>, juce::dsp::Gain<float>> processorChain;
	
	double sampleRate;
	double m;
	double a;
	double da;
	double dda;
	double c;
	double dc;
	double preg;
	double postg;
	int en;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Waveshaper)
};
