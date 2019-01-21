/*
  ==============================================================================

    Preset.h
    Created: 14 Jan 2019 7:54:00pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once

#include <vector>
using std::vector;

#include <utility>
using std::pair;

#include <string>
using std::string;

#include "../JuceLibraryCode/JuceHeader.h"

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

	void setName(string n) { name = n; }
	string getName() { return name; }
	void addParam(string name, vector<pair<string, float>> val) { parameters.push_back(pair<string, vector<pair<string, float>>>(name, val)); }
	vector<pair<string, vector<pair<string, float>>>> getParameters() { return parameters; }

private:
	string name;
	vector<pair<string, vector<pair<string, float>>>> parameters;
};
