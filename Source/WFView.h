/*
  ==============================================================================

    WFView.h
    Created: 16 Dec 2018 6:22:02pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class WFView    : public Component
{
public:
    WFView();
    ~WFView();

	void setWaveform(DrawablePath);

    void paint (Graphics&) override;
    void resized() override;

private:
	DrawablePath waveform;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WFView)
};
