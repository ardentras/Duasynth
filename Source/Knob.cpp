/*
  ==============================================================================

    Knob.cpp
    Created: 16 Dec 2018 4:49:27pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Knob.h"

//==============================================================================
Knob::Knob() : Slider()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

	setSliderStyle(Slider::Rotary);
	setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	setRange(0.0, 127.0, 1.0);
	setValue(64);
}

Knob::~Knob()
{
}

void Knob::paint(Graphics& g)
{
	Slider::paint(g);
}

void Knob::resized()
{
	Slider::resized();
}