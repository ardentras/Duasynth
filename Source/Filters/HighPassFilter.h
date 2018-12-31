/*
  ==============================================================================

    HighPassFilter.h
    Created: 19 Dec 2018 8:08:46pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once

#include "FilterType.h"

class HighPassFilter : public FilterType
{
public:
	HighPassFilter() : FilterType(2.5, 0.0, 1.0), name("high_pass")
	{
		createShape(cutoff, slope, res);
	}

	HighPassFilter(double f, double g, double q) : FilterType(f, g, q), name("high_pass")
	{
		createShape(f, g, q);
	}

	~HighPassFilter() {}

	DrawablePath getShape() { return shape; }

	string getName() { return name; }

	virtual void createShape(double f, double g, double q);

private:
	string name;
};