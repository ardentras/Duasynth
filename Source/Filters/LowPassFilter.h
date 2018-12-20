/*
  ==============================================================================

    LowPassFilter.h
    Created: 19 Dec 2018 6:44:51pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once

#include "FilterType.h"

class LowPassFilter : public FilterType
{
public:
	LowPassFilter() : FilterType(632.45, 0.0, 1.0), name("low_pass")
	{
		createShape(cutoff, slope, res);
	}

	LowPassFilter(double f, double g, double q) : FilterType(f, g, q), name("low_pass")
	{ 
		createShape(f, g, q); 
	}

	~LowPassFilter() {}

	DrawablePath getShape() { return shape; }

	string getName() { return name; }

	virtual void createShape(double f, double g, double q);

private:
	string name;
};