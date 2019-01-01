#pragma once
#include "DuasynthWaveSound.h"

class SineWaveSound : public DuasynthWaveSound
{
public:
	SineWaveSound();
	~SineWaveSound() {}

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

