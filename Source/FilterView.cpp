/*
  ==============================================================================

    FilterView.cpp
    Created: 18 Dec 2018 9:53:43pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "FilterView.h"

///==============================================================================
FilterView::FilterView() : filter()
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.

	addAndMakeVisible(filter);
}

FilterView::~FilterView()
{
}

void FilterView::setFilter(DrawablePath path)
{
	filter.setPath(path.getPath());
}

void FilterView::paint(Graphics& g)
{
	g.setColour(Colour(1.0f, 0.0f, 1.0f, 1.0f));
	g.fillRect(0.0f, 0.0f, (float)getWidth(), (float)getHeight());
}

void FilterView::resized()
{
	Path temp = filter.getPath();
	//temp.scaleToFit(0, 0, getWidth(), getHeight(), true);
	filter.setPath(temp);
}

