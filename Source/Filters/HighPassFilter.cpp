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

	shape.setSize(133, 78);

	path.startNewSubPath(Point<float>(shape.getWidth(), shape.getHeight() / 2));
	path.lineTo(((f - 1.0f) / 3.0f * shape.getWidth()) + 10.0f, shape.getHeight() / 2);
	path.quadraticTo(((f - 1.0f) / 3.0f * shape.getWidth()) + 5.0f, shape.getHeight() / 2, (f - 1.0f) / 3.0f * shape.getWidth(), (shape.getHeight() / 2) - (((q / 3.0f) - (1.0f / 3.0f)) * shape.getHeight() / 2));
	path.quadraticTo(((f - 1.0f) / 3.0f * shape.getWidth()) - 5.0f, (shape.getHeight() / 2) - (((q / 3.0f) - (1.0f / 3.0f)) * shape.getHeight()), (f - 1.0f) / 3.0f * shape.getWidth() - 10.0f, shape.getHeight());
	path.lineTo(shape.getWidth(), shape.getHeight());
	path.closeSubPath();

	shape.setPath(path);
}