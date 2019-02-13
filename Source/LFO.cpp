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
	: lAmp("amp_knob", "Amp"), lFreq("freq_knob", "Freq"),
	a(0.0f), f(0.001f), wf(0), en(1), generator(nullptr), last_val(0)
{
	isActive = false;
	canBind = false;

	initialiseLFO();

	initialiseUI();
}

LFO::~LFO()
{
}

void LFO::initialiseUI()
{
	// Amplitude
	amplitude.setRange(0.0f, 0.8f, 1.0 / 150.0);
	amplitude.setValue(0.0f);
	amplitude.addListener(this);
	amplitude.setName("amp_knob");
	addAndMakeVisible(amplitude);

	lAmp.setFont(Font(16.0f, Font::plain));
	lAmp.setColour(Label::textColourId, Colours::white);
	lAmp.setJustificationType(Justification::centred);
	addAndMakeVisible(lAmp);

	// Frequency
	freq.setRange(0.001f, 1.0f, 1.0 / 150.0);
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

	wf = 0;
	curr_wf = waveforms.at(wf);

	updateLFO();
}

void LFO::updateLFO()
{
	DuasynthWaveSound* wf = nullptr;
	if (generator != nullptr)
	{
		delete generator;
	}

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

	generator->setCurrentPlaybackSampleRate(SAMPLE_RATE);
	generator->setVolume(1);

	last_val = generator->renderNextSample();

	if (wf != nullptr)
	{
		wfView.setWaveform(wf->getShape());
	}
	wfView.resized();

	sliderValueChanged(&amplitude);
	sliderValueChanged(&freq);

	delete wf;
}

void LFO::startLFO()
{
	if (!isActive)
	{
		isActive = true;
		startTimerHz(SAMPLE_RATE);
	}
}

void LFO::stopLFO()
{
	if (isActive)
	{
		isActive = false;
		stopTimer();
	}
}

void LFO::timerCallback()
{
	double range, val, delta;

	val = generator->renderNextSample();

	for (Knob* k : binds)
	{
		range = k->getMaximum() - k->getMinimum();

		delta = range * (val - last_val) * .01;
		
		std::cout << val << ", " << last_val << ", " << val-last_val << std::endl;

		if (k->getValue() == k->getMaximum() && k->getSurplus() > 0)
		{
			double new_delta = k->getSurplus() - delta;

			if (new_delta < 0)
			{
				k->setSurplus(0);
				k->setLessInterval(k->getMaximum() + new_delta);
				if (abs(k->getLessInterval()) >= k->getInterval())
				{
					k->setValue(k->getValue() + k->getLessInterval());
					k->setLessInterval(k->getLessInterval() - k->getInterval());
				}
			}
			else
			{
				k->setSurplus(k->getSurplus() + delta);
			}
			std::cout << "gt " << k->getSurplus() << ", " << delta << std::endl;
		}
		else if (k->getValue() == k->getMinimum() && k->getSurplus() < 0)
		{
			double new_delta = k->getSurplus() + delta;

			if (new_delta > 0)
			{
				k->setSurplus(0);
				k->setLessInterval(k->getMinimum() + new_delta);
				if (abs(k->getLessInterval()) >= k->getInterval())
				{
					k->setValue(k->getValue() + k->getLessInterval());
					k->setLessInterval(k->getLessInterval() - k->getInterval());
				}
			}
			else
			{
				k->setSurplus(k->getSurplus() + delta);
			}
			std::cout << "lt " << k->getSurplus() << ", " << delta << std::endl;
		}
		else
		{
			if (k->getValue() + delta > k->getMaximum())
			{
				double new_delta = k->getValue() + delta - k->getMaximum();
				k->setValue(k->getMaximum());
				k->setSurplus(new_delta);
			}
			else if (k->getValue() + delta < k->getMinimum())
			{
				double new_delta = k->getValue() - delta + k->getMaximum();
				k->setValue(k->getMinimum());
				k->setSurplus(new_delta);
			}
			else
			{
				k->setLessInterval(k->getLessInterval() + delta);
				if (abs(k->getLessInterval()) >= k->getInterval())
				{
					k->setValue(k->getValue() + k->getLessInterval());
					k->setLessInterval(0);
				}
				std::cout << "in " << k->getLessInterval() << ", " << delta << std::endl;
			}
		}

		k->valueChanged();
	}

	last_val = val;
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

void LFO::sliderValueChanged(Slider* slider)
{
	if (slider->getName() == "amp_knob")
	{
		generator->stopNote(a, false);
		a = slider->getValue();
		generator->startNote(f, a);
	}
	else if (slider->getName() == "freq_knob")
	{
		generator->stopNote(a, false);
		f = slider->getValue();
		generator->startNote(f, a);
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
	else if (dynamic_cast<Knob*>(slider) != nullptr && canBind)
	{
		Knob* k = (Knob*)slider;
		if (k->isBound())
		{
			removeBind(k);
		}
		else
		{
			addBind(k);
		}
	}
}

void LFO::buttonClicked(Button* button) 
{
	if (button->getName() == "enable")
	{
		if (isActive)
		{
			en = 1;
			stopLFO();
			button->setButtonText("Enable");
		}
		else
		{
			en = 0;
			startLFO();
			updateLFO();
			button->setButtonText("Disable");
		}
	}
	else if (button->getName() == "bind")
	{
		if (canBind)
		{
			canBind = false;
			button->setToggleState(canBind, false);

			Knob knob;
			for (Knob* k : binds)
			{
				k->setColour(Slider::ColourIds::rotarySliderFillColourId, knob.findColour(Slider::ColourIds::rotarySliderFillColourId));
			}
		}
		else
		{
			for (Knob* k : binds)
			{
				k->setColour(Slider::ColourIds::rotarySliderFillColourId, Colour::fromRGB(0, 150, 0));
			}
			canBind = true;
			button->setToggleState(canBind, false);
		}
	}
}

void LFO::deserialize(vector<pair<string, float>> params)
{
	for (pair<string, float> param : params)
	{
		if (param.first == "amp")
		{
			a = param.second;
			amplitude.setValue(a);
		}
		else if (param.first == "freq")
		{
			f = param.second;
			freq.setValue(f);
		}
		else if (param.first == "wf")
		{
			wf = param.second;
			curr_wf = waveforms.at(wf);
		}
		else if (param.first == "enable")
		{
			en = param.second;

			if (en == 1)
			{
				isActive = false;
				enable.setButtonText("Enable");
			}
			else
			{
				isActive = true;
				enable.setButtonText("Disable");
			}
		}
	}

	updateLFO();
}