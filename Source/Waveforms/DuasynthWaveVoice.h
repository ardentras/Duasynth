/*
  ==============================================================================

    DuasynthWaveVoice.h
    Created: 17 Dec 2018 11:26:09pm
    Author:  shaun.rasmusen

  ==============================================================================
*/
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class DuasynthWaveVoice : public SynthesiserVoice
{
public:
	DuasynthWaveVoice() : coarse(0.0), fine(0.0), oct(0.0), buff(0), fm_buff(nullptr) {}

	virtual ~DuasynthWaveVoice() 
	{
	}

	virtual void startNote(float f, float a) {}
	virtual double renderNextSample() { return 0.0; }

	virtual void setFMBuff(float* buffer, float level)
	{
		fm_level = level;
		fm_buff = buffer;
	}

	virtual float* getFMBuff()
	{
		return &buff;
	}

	virtual void setOct(double val) { angleDelta *= std::pow(2.0, val - oct); oct = val; }
	virtual void setCoarse(double val) { angleDelta *= std::pow(2.0, ((val - coarse) * 100.0) / 1200.0); coarse = val; }
	virtual void setFine(double val) { angleDelta *= std::pow(2.0, (val - fine) / 1200.0); fine = val; }
	virtual void setVolume(double val) { volume = val; }

protected:
	double currentAngle;
	double angleDelta;
	double level;
	double tailOff;

	double coarse;
	double fine;
	double oct;
	double volume;

	float buff;
	float* fm_buff;
	float fm_level;
	float last_fm;
};