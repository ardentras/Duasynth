#include "SineWaveSound.h"

SineWaveSound::SineWaveSound()
{
	Path path;

	shape.setSize(150, 100);

	path.startNewSubPath(0.0f, shape.getHeight() / 2);
	path.quadraticTo(shape.getWidth() / 8, 0.0f, shape.getWidth() / 4, 0.0f);
	path.quadraticTo(shape.getWidth() * 3 / 8, 0.0f, shape.getWidth() / 2, shape.getHeight() / 2);
	path.quadraticTo(shape.getWidth() * 5 / 8, shape.getHeight(), shape.getWidth() / 4 * 3, shape.getHeight());
	path.quadraticTo(shape.getWidth() * 7 / 8, shape.getHeight(), shape.getWidth(), shape.getHeight() / 2);
	path.closeSubPath();

	shape.setPath(path);
}