#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class TriangleWaveSound : public SynthesiserSound
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

private:
	DrawablePath shape;
};

