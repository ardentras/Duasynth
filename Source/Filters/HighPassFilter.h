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
	HighPassFilter(double f, double g, double q) : cutoff(f), slope(g), res(q), name("high_pass")
	{
		createShape(f, g, q);
	}
	HighPassFilter() : FilterType(), name("high_pass") {}
	~HighPassFilter() {}

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