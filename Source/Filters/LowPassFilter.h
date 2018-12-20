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
	LowPassFilter(double f, double g, double q) : cutoff(f), slope(g), res(q), name("low_pass")
	{ 
		createShape(f, g, q); 
	}
	LowPassFilter() : FilterType(), name("low_pass") {}
	~LowPassFilter() {}

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