#pragma once
#include "DuasynthWaveSound.h"

class SawWaveSound : public DuasynthWaveSound
{
public:
	SawWaveSound();
	~SawWaveSound() {}

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

private:
	DrawablePath shape;
};

