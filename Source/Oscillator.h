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
#include "Knob.h"
#include "WFView.h"

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
	Label lOctVal;
	Slider volume;
	WFView wfView;

	// Practical Elements
	Synthesiser synth;
	SynthesiserSound::Ptr curr_wf;
	list<SynthesiserSound::Ptr> waveforms;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
