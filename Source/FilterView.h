/*
  ==============================================================================

    FilterView.h
    Created: 18 Dec 2018 9:53:43pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class FilterView : public Component
{
public:
	FilterView();
	~FilterView();

	void setFilter(DrawablePath);

	void paint(Graphics&) override;
	void resized() override;

private:
	DrawablePath filter;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterView)
};
