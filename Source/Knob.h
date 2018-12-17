/*
  ==============================================================================

    Knob.h
    Created: 16 Dec 2018 4:49:27pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Knob    : public Slider
{
public:
    Knob();
    ~Knob();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Knob)
};
