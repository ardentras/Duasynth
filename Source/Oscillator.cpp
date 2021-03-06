/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#include "Oscillator.h"
#include "Waveforms/SawWaveSound.h"
#include "Waveforms/SawWaveVoice.h"
#include "Waveforms/TriangleWaveSound.h"
#include "Waveforms/TriangleWaveVoice.h"
#include "Waveforms/SineWaveSound.h"
#include "Waveforms/SineWaveVoice.h"
#include "Waveforms/SquareWaveSound.h"
#include "Waveforms/SquareWaveVoice.h"
#include "Waveforms/WhiteNoiseSound.h"
#include "Waveforms/WhiteNoiseVoice.h"

//==============================================================================
Oscillator::Oscillator(LFO& a, LFO& b) : Oscillator()
{
	coarse.addListener(&a);
	coarse.addListener(&b);
	fine.addListener(&a);
	fine.addListener(&b);
	//volume.addListener(&a);
	//volume.addListener(&b);
}

Oscillator::Oscillator()
	: lCoarse("coarse_knob", "Coarse"), lFine("fine_knob", "Fine"),
	  lOctave("octave_adj", "Oct"), c(0.0f), f(0.0f), o(0), wf(0), v(127.0f * 0.8f)
{
	initialiseSynth();

	initialiseUI();
}

Oscillator::~Oscillator()
{
}

void Oscillator::initialiseUI()
{
	// Coarse tuning
	coarse.setRange(-24.0f, 24.0f, 1.0);
	coarse.setValue(0.0f);
	coarse.addListener(this);
	coarse.setName("coarse_knob");
	addAndMakeVisible(coarse);

	lCoarse.setFont(Font(16.0f, Font::plain));
	lCoarse.setColour(Label::textColourId, Colours::white);
	lCoarse.setJustificationType(Justification::centred);
	addAndMakeVisible(lCoarse);

	// Fine tuning
	fine.setRange(-100.0f, 100.0f, 1.0);
	fine.setValue(0.0f);
	fine.addListener(this);
	fine.setName("fine_knob");
	addAndMakeVisible(fine);

	lFine.setFont(Font(16.0f, Font::plain));
	lFine.setColour(Label::textColourId, Colours::white);
	lFine.setJustificationType(Justification::centred);
	addAndMakeVisible(lFine);

	// Octave adj.
	octave.setSliderStyle(Slider::SliderStyle::IncDecButtons);
	octave.setRange(-2.0, 2.0, 1.0);
	octave.setValue(0.0);
	octave.setTextBoxIsEditable(false);
	octave.addListener(this);
	octave.setName("octave_adj");
	addAndMakeVisible(octave);

	lOctave.setFont(Font(16.0f, Font::plain));
	lOctave.setColour(Label::textColourId, Colours::white);
	lOctave.setJustificationType(Justification::centred);
	addAndMakeVisible(lOctave);

	// Waveform select
	wfSelect.setSliderStyle(Slider::SliderStyle::IncDecButtons);
	wfSelect.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	wfSelect.setMinAndMaxValues(0.0, 1.0);
	wfSelect.setRange(wfSelect.getMinValue(), wfSelect.getMaxValue(), 1.0);
	wfSelect.setTextBoxIsEditable(false);
	wfSelect.addListener(this);
	wfSelect.setName("wf_select");
	addAndMakeVisible(wfSelect);

	// Volume adj.
	volume.setSliderStyle(Slider::LinearBarVertical);
	volume.setRange(0.0, 127.0, 1.0);
	volume.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	volume.setValue(127.0f * 0.8f);
	volume.addListener(this);
	volume.setName("volume");
	addAndMakeVisible(volume);

	// Waveform view
	addAndMakeVisible(wfView);

	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(150, 160);
}

void Oscillator::initialiseSynth()
{
	waveforms.push_back("saw");
	waveforms.push_back("triangle");
	waveforms.push_back("sine");
	waveforms.push_back("square");
	waveforms.push_back("noise");

	wf = 0;
	curr_wf = waveforms.at(wf);

	updateSynth();
}

void Oscillator::updateSynth()
{
	isChangingVoices = true;

	releaseResources();

	if (curr_wf == "saw")
	{
		for (int i = 0; i < NUM_VOICES; i++)
		{
			synth.addVoice(new SawWaveVoice());
			synth.addSound(new SawWaveSound());
		}
	}
	else if (curr_wf == "triangle")
	{
		for (int i = 0; i < NUM_VOICES; i++)
		{
			synth.addVoice(new TriangleWaveVoice());
			synth.addSound(new TriangleWaveSound());
		}
	}
	else if (curr_wf == "sine")
	{
		for (int i = 0; i < NUM_VOICES; i++)
		{
			synth.addVoice(new SineWaveVoice());
			synth.addSound(new SineWaveSound());
		}
	}
	else if (curr_wf == "square")
	{
		for (int i = 0; i < NUM_VOICES; i++)
		{
			synth.addVoice(new SquareWaveVoice());
			synth.addSound(new SquareWaveSound());
		}
	}
	else if (curr_wf == "noise")
	{
		for (int i = 0; i < NUM_VOICES; i++)
		{
			synth.addVoice(new WhiteNoiseVoice());
			synth.addSound(new WhiteNoiseSound());
		}
	}

	// Need to get reference and then immediately dereference to thwart
	// the annoying Ptr wrapper on getSound()'s return type
	DuasynthWaveSound* temp = (DuasynthWaveSound*)&*(synth.getSound(0));
	wfView.setWaveform(temp->getShape());
	wfView.resized();

	sliderDragEnded(&octave);
	sliderValueChanged(&coarse);
	sliderValueChanged(&fine);
	sliderValueChanged(&volume);

	isChangingVoices = false;
}

//==============================================================================
void Oscillator::paint (Graphics& g)
{
}

void Oscillator::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor...
	volume.setBounds(2.0f, 2.0f, 11.0f, getHeight() - 2.0f);

	wfSelect.setBounds(15.0f, 2.0f, 50.0f, 18.0f);

	wfView.setBounds(15.0f, 22.0f, getWidth() - 17.0f, (getHeight() / 2) - 2.0f);
	wfView.setSize(wfView.getBounds().getWidth(), wfView.getBounds().getHeight());

	octave.setBounds(20.0f, getHeight() - 57.5f, 50.0f, 40.0f);
	lOctave.setBounds(20.0f, getHeight() - 15.0f, 50.0f, 15.0f);

	coarse.setBounds(65.0f, getHeight() - 57.5f, 50.0f, 50.0f);
	lCoarse.setBounds(65.0f, getHeight() - 15.0f, 50.0f, 15.0f);
	
	fine.setBounds(105.0f, getHeight() - 57.5f, 50.0f, 50.0f);
	lFine.setBounds(105.0f, getHeight() - 15.0f, 50.0f, 15.0f);
}

void Oscillator::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	synth.setCurrentPlaybackSampleRate(sampleRate);
	for (int i = 0; i < synth.getNumVoices(); i++)
	{
		synth.getVoice(i)->setCurrentPlaybackSampleRate(sampleRate);
	}
	synth.setMinimumRenderingSubdivisionSize(samplesPerBlock);
}

void Oscillator::releaseResources()
{
	synth.clearSounds();
	synth.clearVoices();
}

void Oscillator::getNextAudioBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	if (!isChangingVoices)
	{
		synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	}
}

void Oscillator::sliderValueChanged(Slider* slider)
{
	if (slider->getName() == "coarse_knob" || slider->getName() == "fine_knob" || slider->getName() == "volume")
	{
		for (int i = 0; i < synth.getNumVoices(); i++)
		{
			DuasynthWaveVoice* voice = (DuasynthWaveVoice*)synth.getVoice(i);
			if (slider->getName() == "coarse_knob")
			{
				c = slider->getValue();
				voice->setCoarse(c);
			}
			else if (slider->getName() == "fine_knob")
			{
				f = slider->getValue();
				voice->setFine(f);
			}
			else if (slider->getName() == "volume")
			{
				v = slider->getValue();
				voice->setVolume(v);
			}
		}
	}
}

void Oscillator::sliderDragEnded(Slider* slider)
{
	if (slider->getName() == "octave_adj")
	{
		o = slider->getValue();
		for (int i = 0; i < synth.getNumVoices(); i++)
		{
			DuasynthWaveVoice* voice = (DuasynthWaveVoice*)synth.getVoice(i);
			voice->setOct(o);
		}
	}
	else if (slider->getName() == "wf_select")
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

		updateSynth();
		
		wfView.resized();
	}
}
