/*
  ==============================================================================

    BandPassFilter.cpp
    Created: 19 Dec 2018 8:08:36pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "BandPassFilter.h"

void BandPassFilter::createShape(double f, double g, double q)
{
	Path path;

	shape.setSize(133, 78);

	path.startNewSubPath(Point<float>(((f - 1.0f) / 3.0f * shape.getWidth()) - 10.0f, shape.getHeight()));
	path.quadraticTo(((f - 1.0f) / 3.0f * shape.getWidth()), -1.0f * (((q / 3.0f) - (1.0f / 3.0f)) * shape.getHeight()), ((f - 1.0f) / 3.0f * shape.getWidth()) + 10.0f, shape.getHeight());
	path.lineTo(((f - 1.0f) / 3.0f * shape.getWidth()) - 10.0f, shape.getHeight());
	path.closeSubPath();

	shape.setPath(path);
}