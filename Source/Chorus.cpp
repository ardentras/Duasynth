/*
  ==============================================================================

    Chorus.cpp
    Created: 22 Jan 2019 6:33:16pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "Chorus.h"

//==============================================================================
Chorus::Chorus() :
	lMix("mix_knob", "Mix"), lPitch("pitch_knob", "Pitch"),
	lWidth("width_knob", "Width"), lSpeed("speed_knob", "Speed"),
	lDepth("depth_knob", "Depth"), theName("name_label", "Chorus"),
	isActive(false), m(0.0), p(0.0), w(0.5), s(19.9 / 2.0), d(63.0), en(1),
	currentAngle(0.0), angleDelta(0.0)
{
	initialiseUI();

	initialiseChorus();
}

Chorus::~Chorus()
{
}

void Chorus::initialiseUI()
{
	// Name
	theName.setFont(Font(24.0f, Font::plain));
	theName.setColour(Label::textColourId, Colours::white);
	theName.setJustificationType(Justification::centred);
	addAndMakeVisible(theName);

	// Mix
	mix.setRange(0.0f, 1.0f, 1.0f / 150.0f);
	mix.setValue(1.0f);
	mix.addListener(this);
	mix.setName("mix_knob");
	addAndMakeVisible(mix);

	lMix.setFont(Font(16.0f, Font::plain));
	lMix.setColour(Label::textColourId, Colours::white);
	lMix.setJustificationType(Justification::centred);
	addAndMakeVisible(lMix);

	// Pitch
	pitch.setRange(-1.0f, 1.0f, 1.0f / 150.0f);
	pitch.setValue(0.0f);
	pitch.addListener(this);
	pitch.setName("pitch_knob");
	addAndMakeVisible(pitch);

	lPitch.setFont(Font(16.0f, Font::plain));
	lPitch.setColour(Label::textColourId, Colours::lightgrey);
	lPitch.setJustificationType(Justification::centred);
	addAndMakeVisible(lPitch);

	// Width
	width.setRange(0.0f, 1.0f, 1.0f / 150.0f);
	width.setValue(0.5f);
	width.addListener(this);
	width.setName("width_knob");
	addAndMakeVisible(width);

	lWidth.setFont(Font(16.0f, Font::plain));
	lWidth.setColour(Label::textColourId, Colours::white);
	lWidth.setJustificationType(Justification::centred);
	addAndMakeVisible(lWidth);

	// LFO Speed
	speed.setRange(0.1f, 20.0f, 19.9f / 150.0f);
	speed.setValue(19.9f / 2.0f);
	speed.addListener(this);
	speed.setName("speed_knob");
	addAndMakeVisible(speed);

	lSpeed.setFont(Font(16.0f, Font::plain));
	lSpeed.setColour(Label::textColourId, Colours::white);
	lSpeed.setJustificationType(Justification::centred);
	addAndMakeVisible(lSpeed);

	// LFO Depth
	depth.setRange(0.0f, 127.0f, 1.0f / 127.0f);
	depth.setValue(63.0f);
	depth.addListener(this);
	depth.setName("depth_knob");
	addAndMakeVisible(depth);

	lDepth.setFont(Font(16.0f, Font::plain));
	lDepth.setColour(Label::textColourId, Colours::white);
	lDepth.setJustificationType(Justification::centred);
	addAndMakeVisible(lDepth);

	// Enable button
	enable.setButtonText("Enable");
	enable.addListener(this);
	enable.changeWidthToFitText();
	addAndMakeVisible(enable);

	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(100, 200);
}

void Chorus::initialiseChorus()
{
	level = d * 0.15;

	double cyclesPerSample = s / sampleRate;
	angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
}

void Chorus::updateChorus()
{
	sliderValueChanged(&mix);
	sliderValueChanged(&pitch);
	sliderValueChanged(&width);
	sliderValueChanged(&speed);
	sliderValueChanged(&depth);
}

//==============================================================================
void Chorus::paint(Graphics& g)
{
}

void Chorus::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor...
	theName.setBounds(0.0f, 0.0f, getWidth(), 25.0f);

	mix.setBounds(getWidth() / 4.0f, 18.0f, 50.0f, 50.0f);
	lMix.setBounds(getWidth() / 4.0f, 60.5, 50.0f, 15.0f);

	speed.setBounds(0.0f, 68.0f, 50.0f, 50.0f);
	lSpeed.setBounds(0.0f, 110.5f, 50.0f, 15.0f);

	pitch.setBounds(50.0f, 68.0f, 50.0f, 50.0f);
	lPitch.setBounds(50.0f, 110.5f, 50.0f, 15.0f);

	width.setBounds(0.0f, 118.0f, 50.0f, 50.0f);
	lWidth.setBounds(0.0f, 160.5f, 50.0f, 15.0f);

	depth.setBounds(50.0f, 118.0f, 50.0f, 50.0f);
	lDepth.setBounds(50.0f, 160.5f, 50.0f, 15.0f);

	enable.setBounds((getWidth() / 2.0f) - 25.0f, 182.0f, 50.0f, 18.0f);
}

void Chorus::prepareToPlay(double sampleRate, int samplesPerBlock)
{
}

void Chorus::processSamples(AudioBuffer<float>& buffer, int numSamples)
{
	if (isActive)
	{
		// Evidently this is the only way to get this block into new memory
		AudioBuffer<float> initial(buffer.getNumChannels(), numSamples);
		initial = buffer;

		// Process waveshaping
		juce::dsp::AudioBlock<float> block = juce::dsp::AudioBlock<float>(buffer).getSubBlock((size_t)0, (size_t)numSamples);
		//juce::dsp::ProcessContextNonReplacing<float> context = juce::dsp::ProcessContextNonReplacing<float>(initial, block);
		processLFO(block, numSamples);

		// Mix the two signals
		//block = context.getOutputBlock();
		block.multiply(m);
		block.addWithMultiply(juce::dsp::AudioBlock<float>(initial).getSubBlock((size_t)0, (size_t)numSamples), 1.0f - m);
	}
}

void Chorus::processLFO(juce::dsp::AudioBlock<float> block, int numSamples)
{
	if (angleDelta != 0.0)
	{
		while (--numSamples >= 0)
		{
			double currentSample;

			currentSample = (double)(level * sin(currentAngle));

			currentAngle += angleDelta;

			if (currentAngle > (MathConstants<double>::twoPi))
			{
				currentAngle -= MathConstants<double>::twoPi;
			}
		}
	}
}

void Chorus::releaseResources()
{
}

void Chorus::sliderValueChanged(Slider* slider)
{
	if (slider->getName() == "mix_knob")
	{
		m = slider->getValue();
	}
	else if (slider->getName() == "pitch_knob")
	{
		p = slider->getValue();
	}
	else if (slider->getName() == "width_knob")
	{
		w = slider->getValue();
	}
	else if (slider->getName() == "speed_knob")
	{
		s = slider->getValue();
	}
	else if (slider->getName() == "depth_knob")
	{
		d = slider->getValue();
	}
}