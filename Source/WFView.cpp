/*
  ==============================================================================

    WFView.cpp
    Created: 16 Dec 2018 6:22:02pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WFView.h"

//==============================================================================
WFView::WFView() : waveform()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

	addAndMakeVisible(waveform);
}

WFView::~WFView()
{
}

void WFView::setWaveform(DrawablePath path)
{
	waveform.setPath(path.getPath());
}

void WFView::paint (Graphics& g)
{
	g.setColour(Colour(1.0f, 0.0f, 1.0f, 1.0f));
	g.fillRect(0.0f, 0.0f, (float)getWidth(), (float)getHeight());
}

void WFView::resized()
{
	Path temp = waveform.getPath();
	temp.scaleToFit(0, 0, getWidth(), getHeight(), true);
	waveform.setPath(temp);
}
