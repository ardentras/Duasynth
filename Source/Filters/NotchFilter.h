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
	NotchFilter(double f, double g, double q) : cutoff(f), slope(g), res(q), name("notch")
	{
		createShape(f, g, q);
	}
	NotchFilter() : FilterType(), name("notch") {}
	~NotchFilter() {}

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