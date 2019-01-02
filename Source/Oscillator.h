/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <list>
using std::list;

#include <string>
using std::string;

#include "../JuceLibraryCode/JuceHeader.h"
#include "Waveforms/DuasynthWaveSound.h"
#include "Waveforms/DuasynthWaveVoice.h"
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
private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.

	// UI Elements
	Label lCoarse;
	Knob coarse;
	Label lFine;
	Knob fine;
	Slider octave;
	Label lOctave;
	Slider wfSelect;
	Slider volume;
	WFView wfView;

	// Practical Elements
	DuasynthSynthesiser synth;
	string curr_wf;
	list<string> waveforms;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
