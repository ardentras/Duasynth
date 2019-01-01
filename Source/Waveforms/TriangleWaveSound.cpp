#include "TriangleWaveSound.h"

TriangleWaveSound::TriangleWaveSound()
{
	Path path;

	shape.setSize(150, 100);

	path.startNewSubPath(0.0f, shape.getHeight() / 2);
	path.lineTo(shape.getWidth() / 4, 0.0f);
	path.lineTo(shape.getWidth() / 4 * 3, shape.getHeight());
	path.lineTo(shape.getWidth(), shape.getHeight() / 2);
	path.closeSubPath();

	shape.setPath(path);
}