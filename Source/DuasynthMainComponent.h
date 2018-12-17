/*
  ==============================================================================

    DuasynthMainComponent.h
    Created: 16 Dec 2018 3:36:18pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"
#include "OscillatorEditor.h"

//==============================================================================
/*
*/
class DuasynthMainComponent : public AudioAppComponent
{
public:
    DuasynthMainComponent();
    ~DuasynthMainComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    MidiKeyboardState keyboardState;
	Oscillator a_osc;
	OscillatorEditor a_osc_editor;
	/*Oscillator b_osc;
	OscillatorEditor b_osc_editor;*/
    //PresetBank presetBank;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DuasynthMainComponent)
};
