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
	BandPassFilter(double f, double g, double q) : cutoff(f), slope(g), res(q), name("band_pass")
	{
		createShape(f, g, q);
	}
	BandPassFilter() : FilterType(), name("band_pass") {}
	~BandPassFilter() {}

	DrawablePath getShape() { return shape; }

	string getName() { return name; }

	virtual void createShape(double f, double g, double q);

protected:
	DrawablePath shape;

	double cutoff;
	double slope;
	double res;

private:
	string name;
};