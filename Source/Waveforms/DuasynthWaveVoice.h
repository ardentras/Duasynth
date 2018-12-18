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
	virtual ~DuasynthWaveVoice() {}

	virtual void setOct(double val) = 0;
	virtual void setCoarse(double val) = 0;
	virtual void setFine(double val) = 0;
};