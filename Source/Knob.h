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

	bool isBound() { return bound; }
	void setBound(bool b) { bound = b; }

	double getSurplus() { return surplus; }
	void setSurplus(double s) { surplus = s; }

	double getLessInterval() { return less_interval; }
	void setLessInterval(double li) { less_interval = li; }

private:
	bool bound;
	double surplus;
	double less_interval;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Knob)
};
