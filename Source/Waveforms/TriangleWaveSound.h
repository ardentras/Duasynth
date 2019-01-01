#pragma once
#include "DuasynthWaveSound.h"

class TriangleWaveSound : public DuasynthWaveSound
{
public:
	TriangleWaveSound();
	~TriangleWaveSound() {}

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

