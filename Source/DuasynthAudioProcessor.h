/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"
#include "Filter.h"
#include "Waveshaper.h"
#include "Chorus.h"
#include "LFO.h"

//==============================================================================
/**
*/
class DuasynthAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    DuasynthAudioProcessor();
    ~DuasynthAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	MidiMessageCollector* getMidiCollector() { return &midiCollector; }

	Oscillator& getAOsc() { return a_osc; }
	Oscillator& getBOsc() { return b_osc; }
	Filter& getAFilter() { return a_filter; }
	Filter& getBFilter() { return b_filter; }
	Chorus& getChorus() { return chorus; }
	Waveshaper& getWaveshaper() { return waveshaper; }
	LFO& getALFO() { return a_lfo; }
	LFO& getBLFO() { return b_lfo; }

private:
    //==============================================================================
	Oscillator a_osc;
	Oscillator b_osc;
	Filter a_filter;
	Filter b_filter;
	Chorus chorus;
	Waveshaper waveshaper;
	LFO a_lfo;
	LFO b_lfo;

	MidiMessageCollector midiCollector;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DuasynthAudioProcessor)
};
