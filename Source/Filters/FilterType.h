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
class FilterType : Component
{
public:
	FilterType() {}
	FilterType(double f, double g, double q) : cutoff(f), slope(g), res(q) {}
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

	void paint(Graphics& g)
	{
		g.strokePath(shape.getPath(), PathStrokeType(LINE_WEIGHT));
	}

	void resized() { }


protected:
	DrawablePath shape;

	double cutoff;
	double slope;
	double res;
};

