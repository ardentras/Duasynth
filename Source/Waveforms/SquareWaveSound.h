#pragma once
#include "DuasynthWaveSound.h"

class SquareWaveSound : public DuasynthWaveSound
{
public:
	SquareWaveSound();
	~SquareWaveSound() {}

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

