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

#include "../cereal/archives/json.hpp"
using namespace cereal;

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
		JSONOutputArchive oarch(ss);

		parameters = ss.str();
	}

	DuasynthAudioProcessorEditor* deserialize()
	{
		DuasynthAudioProcessorEditor* dape = new DuasynthAudioProcessorEditor();

		JSONInputArchive iarch();
		return dape;
	}
	
private:
	string name;
	string parameters;
};
