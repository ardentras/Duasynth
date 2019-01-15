/*
  ==============================================================================

    Preset.h
    Created: 14 Jan 2019 7:54:00pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once

#include <sstream>
using std::stringstream;

#include <string>
using std::string;

#include "../JuceLibraryCode/JuceHeader.h"
#include "DuasynthAudioProcessorEditor.h"

#include "../cereal/archives/binary.hpp"
using cereal::BinaryInputArchive;
using cereal::BinaryOutputArchive;

//==============================================================================
/**
*/
class Preset
{
public:
	Preset() : name(), parameters()
	{

	}

	~Preset()
	{

	}

	void serialize(DuasynthAudioProcessorEditor dape)
	{
		stringstream ss;
		BinaryOutputArchive oarch(ss);

		oarch(dape.getProcessor().getAOsc(), dape.getProcessor().getBOsc(), 
			dape.getProcessor().getAFilter(), dape.getProcessor().getBFilter(), 
			dape.getProcessor().getWaveshaper());

		parameters = ss.str();
	}

	void deserialize(DuasynthAudioProcessorEditor* dape)
	{
		stringstream ss(parameters);
		BinaryInputArchive iarch(ss);
	}
	
private:
	string name;
	string parameters;
};
