/*
  ==============================================================================

    HighPassFilter.cpp
    Created: 19 Dec 2018 8:08:46pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "HighPassFilter.h"

void HighPassFilter::createShape(double f, double g, double q)
{
	Path path;

	shape.setSize(150, 100);

	path.addLineSegment(Line<float>(0.0f, shape.getHeight() / 2, (f / 20000.0f) * shape.getWidth() - 10.0f, shape.getHeight() / 2), LINE_WEIGHT);
	path.addArc((f / 20000.0f) * shape.getWidth() - 10.0f, shape.getHeight() / 2, 10.0f, 0.0f, MathConstants<float>::pi / 2.0f, false);
	path.addLineSegment(Line<float>((f / 20000.0f) * shape.getWidth(), (shape.getHeight() / 2.0f) + 10.0f, (f / 20000.0f) * shape.getWidth(), shape.getHeight()), LINE_WEIGHT);

	shape.setPath(path);
}