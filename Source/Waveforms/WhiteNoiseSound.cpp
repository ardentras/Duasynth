/*
  ==============================================================================

    WhiteNoiseSound.cpp
    Created: 13 Feb 2019 4:26:39pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "WhiteNoiseSound.h"
WhiteNoiseSound::WhiteNoiseSound()
{
	Path path;

	shape.setSize(150, 100);

	for (int i = 0; i < 1000; i++)
	{
		path.addPolygon(Point<float>(rand() % 150, rand() % 100), 4, 2);
	}

	shape.setPath(path);
}