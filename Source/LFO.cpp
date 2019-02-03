/*
  ==============================================================================

    LFO.cpp
    Created: 2 Feb 2019 5:09:28pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "LFO.h"
#include "Waveforms/SawWaveSound.h"
#include "Waveforms/SawWaveVoice.h"
#include "Waveforms/TriangleWaveSound.h"
#include "Waveforms/TriangleWaveVoice.h"
#include "Waveforms/SineWaveSound.h"
#include "Waveforms/SineWaveVoice.h"
#include "Waveforms/SquareWaveSound.h"
#include "Waveforms/SquareWaveVoice.h"

//==============================================================================
LFO::LFO()
	: lAmp("amp_knob", "Amp"), lFreq("freq_knob", "Freq"), canBind(false),
	isActive(false), a(0.0f), f(0.0f), wf(0), en(1), generator(nullptr)
{
	initialiseLFO();

	initialiseUI();
}

LFO::~LFO()
{
}

void LFO::initialiseUI()
{
	// Coarse tuning
	amplitude.setRange(-1.0f, 1.0f, 1.0 / 150.0);
	amplitude.setValue(0.0f);
	amplitude.addListener(this);
	amplitude.setName("amp_knob");
	addAndMakeVisible(amplitude);

	lAmp.setFont(Font(16.0f, Font::plain));
	lAmp.setColour(Label::textColourId, Colours::white);
	lAmp.setJustificationType(Justification::centred);
	addAndMakeVisible(lAmp);

	// Fine tuning
	freq.setRange(0.001f, 10.0f, 1.0 / 150.0);
	freq.setValue(0.0f);
	freq.addListener(this);
	freq.setName("freq_knob");
	addAndMakeVisible(freq);

	lFreq.setFont(Font(16.0f, Font::plain));
	lFreq.setColour(Label::textColourId, Colours::white);
	lFreq.setJustificationType(Justification::centred);
	addAndMakeVisible(lFreq);

	// Waveform select
	wfSelect.setSliderStyle(Slider::SliderStyle::IncDecButtons);
	wfSelect.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	wfSelect.setMinAndMaxValues(0.0, 1.0);
	wfSelect.setRange(wfSelect.getMinValue(), wfSelect.getMaxValue(), 1.0);
	wfSelect.setTextBoxIsEditable(false);
	wfSelect.addListener(this);
	wfSelect.setName("wf_select");
	addAndMakeVisible(wfSelect);

	// Waveform view
	addAndMakeVisible(wfView);

	// Enable button
	enable.setButtonText("Enable");
	enable.setName("enable");
	enable.addListener(this);
	enable.changeWidthToFitText();
	addAndMakeVisible(enable);

	// Bind button
	bind.setButtonText("Bind");
	bind.setName("bind");
	bind.addListener(this);
	bind.changeWidthToFitText();
	bind.setColour(TextButton::ColourIds::buttonOnColourId, Colour::fromRGB(0, 150, 0));
	addAndMakeVisible(bind);

	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(150, 160);
}

void LFO::initialiseLFO()
{
	waveforms.push_back("saw");
	waveforms.push_back("triangle");
	waveforms.push_back("sine");
	waveforms.push_back("square");
	//waveforms.push_back("noise");

	wf = 0;
	curr_wf = waveforms.at(wf);

	updateLFO();
}

void LFO::updateLFO()
{
	releaseResources();
	DuasynthWaveSound* wf;

	if (curr_wf == "saw")
	{
		wf = new SawWaveSound();
		generator = new SawWaveVoice();
	}
	else if (curr_wf == "triangle")
	{
		wf = new TriangleWaveSound();
		generator = new TriangleWaveVoice();
	}
	else if (curr_wf == "sine")
	{
		wf = new SineWaveSound();
		generator = new SineWaveVoice();
	}
	else if (curr_wf == "square")
	{
		wf = new SquareWaveSound();
		generator = new SquareWaveVoice();
	}

	wfView.setWaveform(wf->getShape());
	wfView.resized();

	sliderValueChanged(&amplitude);
	sliderValueChanged(&freq);

	delete wf;
}

//==============================================================================
void LFO::paint(Graphics& g)
{
}

void LFO::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor...
	enable.setBounds(getWidth() - 57.0f, 2.0f, 50.0f, 18.0f);
	bind.setBounds(15.0f, getHeight() - 37.5f, 40.0f, 25.0f);

	wfSelect.setBounds(10.0f, 2.0f, 50.0f, 18.0f);

	wfView.setBounds(10.0f, 22.0f, getWidth() - 17.0f, (getHeight() / 2) - 2.0f);
	wfView.setSize(wfView.getBounds().getWidth(), wfView.getBounds().getHeight());

	amplitude.setBounds(60.0f, getHeight() - 57.5f, 50.0f, 50.0f);
	lAmp.setBounds(60.0f, getHeight() - 15.0f, 50.0f, 15.0f);

	freq.setBounds(100.0f, getHeight() - 57.5f, 50.0f, 50.0f);
	lFreq.setBounds(100.0f, getHeight() - 15.0f, 50.0f, 15.0f);
}

void LFO::prepareToPlay(double sampleRate, int samplesPerBlock)
{

}

void LFO::releaseResources()
{
}

void LFO::getNextAudioBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
}

void LFO::sliderValueChanged(Slider* slider)
{
	if (slider->getName() == "amp_knob")
	{
		a = slider->getValue();
	}
	else if (slider->getName() == "freq_knob")
	{
		f = slider->getValue();
	}
}

void LFO::sliderDragEnded(Slider* slider)
{
	if (slider->getName() == "wf_select")
	{
		string temp;
		if (slider->getValue() >= slider->getMaxValue())
		{
			wf++;
			if (wf >= waveforms.size())
			{
				wf = 0;
			}
		}
		else if (slider->getValue() <= slider->getMinValue())
		{
			wf--;
			if (wf < 0)
			{
				wf = waveforms.size() - 1;
			}
		}

		curr_wf = waveforms.at(wf);

		updateLFO();

		wfView.resized();
	}
}
