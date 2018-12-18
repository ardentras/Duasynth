#include "SawWaveSound.h"

SawWaveSound::SawWaveSound()
{
	Path path;

	shape.setSize(150, 100);

	path.addLineSegment(Line<float>(0.0f, shape.getHeight() / 2, shape.getWidth() / 2, 0.0f), LINE_WEIGHT);
	path.addLineSegment(Line<float>(shape.getWidth() / 2, 0.0f, shape.getWidth() / 2, shape.getHeight()), LINE_WEIGHT);
	path.addLineSegment(Line<float>(shape.getWidth() / 2, shape.getHeight(), shape.getWidth(), shape.getHeight() / 2), LINE_WEIGHT);

	shape.setPath(path);
}