/*
  ==============================================================================

    FilterType.h
    Created: 19 Dec 2018 6:37:31pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once

#include <string>
using std::string;

#include "../JuceLibraryCode/JuceHeader.h"

#define LINE_WEIGHT 5.0f

//==============================================================================
/*
*/
class FilterType
{
public:
	FilterType() : cutoff(0.0), slope(0.0), res(0.0) {}
	~FilterType() {}

	DrawablePath getShape()
	{
		return shape;
	}

	virtual void createShape(double f, double g, double q) {}

	void setCutoff(double val)
	{
		cutoff = val;
	}

	void setSlope(double val)
	{
		slope = val;
	}

	void setRes(double val)
	{
		res = val;
	}

	virtual string getName() { return ""; }

protected:
	DrawablePath shape;

	double cutoff;
	double slope;
	double res;
};

