/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <list>
using std::list;

#include "../JuceLibraryCode/JuceHeader.h"
#include "Waveforms/DuasynthWaveSound.h"
#include "Knob.h"
#include "WFView.h"
#include "WFChanged.h"

//==============================================================================
/**
*/
class Oscillator  : public Component
{
public:
	Oscillator();
    ~Oscillator();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	void clearSounds();
	void prepareToPlay(int samplesPerBlock, double sampleRate);
	void releaseResources();
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill);

	// This event shouldn't happen in normal use so I'm using it as a way
	// for the listener to communicate back to the parent component (this one).
	void mouseMagnify(const MouseEvent& event, float scaleFactor);

	Synthesiser& getSynth() { return synth; }
	DuasynthWaveSound* getCurrWF() { return curr_wf; }
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
	Synthesiser synth;
	DuasynthWaveSound* curr_wf;
	list<DuasynthWaveSound*> waveforms;

	// Listeners
	WFChanged wfChanged;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
