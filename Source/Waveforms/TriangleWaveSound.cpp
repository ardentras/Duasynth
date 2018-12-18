#include "TriangleWaveSound.h"

TriangleWaveSound::TriangleWaveSound()
{
	Path path;

	shape.setSize(150, 100);

	path.addLineSegment(Line<float>(0.0f, shape.getHeight() / 2, shape.getWidth() / 4, 0.0f), LINE_WEIGHT);
	path.addLineSegment(Line<float>(shape.getWidth() / 4, 0.0f, shape.getWidth() / 4 * 3, shape.getHeight()), LINE_WEIGHT);
	path.addLineSegment(Line<float>(shape.getWidth() / 4 * 3, shape.getHeight(), shape.getWidth(), shape.getHeight() / 2), LINE_WEIGHT);

	shape.setPath(path);
}