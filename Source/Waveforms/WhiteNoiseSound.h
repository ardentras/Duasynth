/*
  ==============================================================================

    WhiteNoiseSound.h
    Created: 13 Feb 2019 4:26:39pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once
#include "DuasynthWaveSound.h"

class WhiteNoiseSound : public DuasynthWaveSound
{
public:
	WhiteNoiseSound();
	~WhiteNoiseSound() {}

	bool appliesToNote(int midiNoteNumber) override
	{
		return true;
	}
	bool appliesToChannel(int midiChannel) override
	{
		return true;
	}
	DrawablePath getShape()
	{
		return shape;
	}
};