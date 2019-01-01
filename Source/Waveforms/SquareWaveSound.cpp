#include "SquareWaveSound.h"

SquareWaveSound::SquareWaveSound()
{
	Path path;

	shape.setSize(150, 100);

	path.startNewSubPath(0.0f, shape.getHeight() / 2);
	path.lineTo(0.0f, 0.0f);
	path.lineTo(shape.getWidth() / 2, 0.0f);
	path.lineTo(shape.getWidth() / 2, shape.getHeight());
	path.lineTo(shape.getWidth(), shape.getHeight());
	path.lineTo(shape.getWidth(), shape.getHeight() / 2);
	path.closeSubPath();

	shape.setPath(path);
}