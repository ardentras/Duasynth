/*
  ==============================================================================

    BandPassFilter.h
    Created: 19 Dec 2018 8:08:36pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once

#include "FilterType.h"

class BandPassFilter : public FilterType
{
public:
	BandPassFilter() : FilterType(2.5, 0.0, 1.0), name("band_pass")
	{
		createShape(cutoff, slope, res);
	}

	BandPassFilter(double f, double g, double q) : FilterType(f, g, q), name("band_pass")
	{
		createShape(f, g, q);
	}

	~BandPassFilter() {}

	DrawablePath getShape() { return shape; }

	string getName() { return name; }

	virtual void createShape(double f, double g, double q);

private:
	string name;
};