/*
  ==============================================================================

    WFChanged.h
    Created: 17 Dec 2018 6:49:30pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class WFChanged : public Slider::Listener
{
public:
	WFChanged();
	~WFChanged();

	void sliderValueChanged(Slider* slider) {}
	void sliderDragStarted(Slider* slider) {}
	void sliderDragEnded(Slider* slider);
};