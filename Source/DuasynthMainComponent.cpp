/*
  ==============================================================================

    DuasynthMainComponent.cpp
    Created: 16 Dec 2018 3:36:18pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DuasynthMainComponent.h"

//==============================================================================
DuasynthMainComponent::DuasynthMainComponent() 
	: a_osc(), a_osc_editor(a_osc)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

	setVisible(true);
	setSize(500, 600);
}

DuasynthMainComponent::~DuasynthMainComponent()
{
}

void DuasynthMainComponent::paint (Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	a_osc_editor.paint(g);
}

void DuasynthMainComponent::resized()
{
	a_osc_editor.setBounds(100, 100, a_osc_editor.getWidth(), a_osc_editor.getHeight());
}
