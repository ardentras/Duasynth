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

	Path path;

	path.addLineSegment(Line<float>(0.0f, 32.5f, 65.0f, 0.0f), 2.0f);
	path.addLineSegment(Line<float>(65.0f, 0.0f, 130.0f, 32.5f), 2.0f);

	waveform.setPath(path);

	addAndMakeVisible(waveform);
}

WFView::~WFView()
{
}

void WFView::paint (Graphics& g)
{
	waveform.paint(g);
}

void WFView::resized()
{

}
