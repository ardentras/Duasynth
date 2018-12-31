/*
  ==============================================================================

    NotchFilter.h
    Created: 19 Dec 2018 8:08:59pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once

#include "FilterType.h"

class NotchFilter : public FilterType
{
public:
	NotchFilter() : FilterType(2.5, 0.0, 1.0), name("notch")
	{
		createShape(cutoff, slope, res);
	}

	NotchFilter(double f, double g, double q) : FilterType(f, g, q), name("notch")
	{
		createShape(f, g, q);
	}

	~NotchFilter() {}

	DrawablePath getShape() { return shape; }

	string getName() { return name; }

	virtual void createShape(double f, double g, double q);

private:
	string name;
};