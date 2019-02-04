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

#include "Waveforms/DuasynthWaveSound.h"
#include "Waveforms/DuasynthWaveVoice.h"
#include "LFO.h"
#include "DuasynthSynthesiser.h"
#include "Knob.h"
#include "WFView.h"

#define NUM_VOICES 6

//==============================================================================
/**
*/
class Oscillator  : public Component, private Slider::Listener
{
public:
	Oscillator();
	Oscillator(LFO& a, LFO& b);
	~Oscillator();

	void initialiseUI();
	void initialiseSynth();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	void prepareToPlay(double sampleRate, int samplesPerBlock);
	void releaseResources();
	void getNextAudioBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages);

	void sliderValueChanged(Slider* slider) override;
	void sliderDragEnded(Slider* slider) override;

	void updateSynth();

	DuasynthSynthesiser& getSynth() { return synth; }
	string getCurrWF() { return curr_wf; }

	vector<pair<string, float>> serialize()
	{
		vector<pair<string, float>> params;

		params.push_back(pair<string, float>("coarse", c));
		params.push_back(pair<string, float>("fine", f));
		params.push_back(pair<string, float>("octave", o));
		params.push_back(pair<string, float>("wf", wf));
		params.push_back(pair<string, float>("volume", v));

		return params;
	}

	void deserialize(vector<pair<string, float>> params)
	{
		for (pair<string, float> param : params)
		{
			if (param.first == "coarse")
			{
				c = param.second;
				coarse.setValue(c);
			}
			else if (param.first == "fine")
			{
				f = param.second;
				fine.setValue(f);
			}
			else if (param.first == "octave")
			{
				o = param.second;
				octave.setValue(o);
			}
			else if (param.first == "wf")
			{
				wf = param.second;
				curr_wf = waveforms.at(wf);
			}
			else if (param.first == "volume")
			{
				v = param.second;
			}
		}

		updateSynth();
	}

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.

	// UI Elements
	Label lCoarse;
	Knob coarse;
	Label lFine;
	Knob fine;
	Label lOctave;
	Slider octave;
	Slider wfSelect;
	Slider volume;
	WFView wfView;

	// Practical Elements
	DuasynthSynthesiser synth;
	string curr_wf;
	vector<string> waveforms;

	double c;
	double f;
	int o;
	int wf;
	double v;
	
	bool isChangingVoices;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
