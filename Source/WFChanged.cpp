/*
  ==============================================================================

    WFChanged.cpp
    Created: 17 Dec 2018 6:49:30pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "WFChanged.h"

WFChanged::WFChanged()
{
}

WFChanged::~WFChanged()
{
}

void WFChanged::sliderDragEnded(Slider* slider)
{
	MouseEvent* me = nullptr;
	if (slider->getValue() >= slider->getMaxValue())
	{
		slider->getParentComponent()->mouseMagnify(*me, 1.0f);
	}
	else if (slider->getValue() <= slider->getMinValue())
	{
		slider->getParentComponent()->mouseMagnify(*me, -1.0f);
	}
}