/*
  ==============================================================================

    DuasynthWaveSound.h
    Created: 17 Dec 2018 6:04:02pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#define LINE_WEIGHT 5.0f

class DuasynthWaveSound : public SynthesiserSound
{
public:
	virtual ~DuasynthWaveSound() {}

	virtual bool appliesToNote(int midiNoteNumber) = 0;
	virtual bool appliesToChannel(int midiChannel) = 0;
	virtual DrawablePath getShape() = 0;

	virtual void paint(Graphics& g)
	{
		g.fillPath(shape.getPath());
	}

protected:
	DrawablePath shape;
};

