/*
  ==============================================================================

    Waveshaper.cpp
    Created: 31 Dec 2018 12:36:40pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "Waveshaper.h"

//==============================================================================
Waveshaper::Waveshaper() :
	lMix("mix_knob", "Mix"), lPostgain("post_knob", "Post"),
	lAttack("attack_knob", "Attack"), lPregain("pre_knob", "Pre"),
	lCurve("curve_knob", "Curve"), theName("name_label", "Waveshaper"),
	isActive(false), m(1.0), a(0.0), c(0.0), preg(0.8f), postg(((1.0f - 0.35f) * 0.8f) + 0.35f), en(1)
{
	initialiseUI();

	initialiseWaveshaper();
}

Waveshaper::~Waveshaper()
{
}

void Waveshaper::initialiseUI()
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

	// Pregain
	pregain.setRange(0.0f, 1.0f, 1.0f / 150.0f);
	pregain.setValue(0.8f);
	pregain.addListener(this);
	pregain.setName("pre_knob");
	addAndMakeVisible(pregain);

	lPregain.setFont(Font(16.0f, Font::plain));
	lPregain.setColour(Label::textColourId, Colours::white);
	lPregain.setJustificationType(Justification::centred);
	addAndMakeVisible(lPregain);

	// Postgain
	postgain.setRange(0.30f, 1.0f, 1.0f / 100.0f);
	postgain.setValue(((1.0f - 0.35f) * 0.8f) + 0.35f);
	postgain.addListener(this);
	postgain.setName("post_knob");
	addAndMakeVisible(postgain);

	lPostgain.setFont(Font(16.0f, Font::plain));
	lPostgain.setColour(Label::textColourId, Colours::lightgrey);
	lPostgain.setJustificationType(Justification::centred);
	addAndMakeVisible(lPostgain);

	// Attack
	attack.setRange(0.0f, 1.0f, 1.0f / 150.0f);
	attack.setValue(0.0f);
	attack.addListener(this);
	attack.setName("attack_knob");
	addAndMakeVisible(attack);

	lAttack.setFont(Font(16.0f, Font::plain));
	lAttack.setColour(Label::textColourId, Colours::white);
	lAttack.setJustificationType(Justification::centred);
	addAndMakeVisible(lAttack);

	// Curve
	curve.setRange(-1.0f, 1.0f, 1.0f / 150.0f);
	curve.setValue(0.0f);
	curve.addListener(this);
	curve.setName("curve_knob");
	addAndMakeVisible(curve);

	lCurve.setFont(Font(16.0f, Font::plain));
	lCurve.setColour(Label::textColourId, Colours::white);
	lCurve.setJustificationType(Justification::centred);
	addAndMakeVisible(lCurve);

	// Enable button
	enable.setButtonText("Enable");
	enable.addListener(this);
	enable.changeWidthToFitText();
	addAndMakeVisible(enable);

	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(100, 200);
}

void Waveshaper::initialiseWaveshaper()
{
	juce::dsp::WaveShaper<float>& waveshaper = processorChain.template get<1>();
	waveshaper.functionToUse = [](float x) { return tanh(x); };

	auto& preGain = processorChain.template get<0>();
	preGain.setGainDecibels(40.0f * 0.8f);
	auto& postGain = processorChain.template get<2>();
	postGain.setGainDecibels((100 * (((1.0f - 0.3f) * 0.8f) + 0.3f)) - 100.0f);
}

void Waveshaper::updateWaveshaper()
{
	sliderValueChanged(&mix);
	sliderValueChanged(&postgain);
	sliderValueChanged(&attack);
	sliderValueChanged(&pregain);
	sliderValueChanged(&curve);
}

//==============================================================================
void Waveshaper::paint(Graphics& g)
{
}

void Waveshaper::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor...
	theName.setBounds(0.0f, 0.0f, getWidth(), 25.0f);

	mix.setBounds(getWidth() / 4.0f, 18.0f, 50.0f, 50.0f);
	lMix.setBounds(getWidth() / 4.0f, 60.5, 50.0f, 15.0f);

	pregain.setBounds(0.0f, 68.0f, 50.0f, 50.0f);
	lPregain.setBounds(0.0f, 110.5f, 50.0f, 15.0f);

	postgain.setBounds(50.0f, 68.0f, 50.0f, 50.0f);
	lPostgain.setBounds(50.0f, 110.5f, 50.0f, 15.0f);

	attack.setBounds(0.0f, 118.0f, 50.0f, 50.0f);
	lAttack.setBounds(0.0f, 160.5f, 50.0f, 15.0f);

	curve.setBounds(50.0f, 118.0f, 50.0f, 50.0f);
	lCurve.setBounds(50.0f, 160.5f, 50.0f, 15.0f);

	enable.setBounds((getWidth() / 2.0f) - 25.0f, 182.0f, 50.0f, 18.0f);
}

void Waveshaper::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	processorChain.prepare({ sampleRate, (uint32)samplesPerBlock, 2 });
}

void Waveshaper::processSamples(AudioBuffer<float>& buffer, int numSamples)
{
	if (isActive)
	{
		// Evidently this is the only way to get this block into new memory
		AudioBuffer<float> initial(buffer.getNumChannels(), numSamples);
		initial = buffer;

		// Process waveshaping
		juce::dsp::AudioBlock<float> block = juce::dsp::AudioBlock<float>(buffer).getSubBlock((size_t)0, (size_t)numSamples);
		juce::dsp::ProcessContextNonReplacing<float> context = juce::dsp::ProcessContextNonReplacing<float>(initial, block);
		processorChain.process(context);

		// Mix the two signals
		block = context.getOutputBlock();
		block.multiply(m * da);
		block.addWithMultiply(juce::dsp::AudioBlock<float>(initial).getSubBlock((size_t)0, (size_t)numSamples), 1.0f - (m * da));

		if (a <= 0.0f)
		{
			da = 1.0f;
		}
		else if (da < 1.0f)
		{
			float t = numSamples / sampleRate;
			dda = t / (5.0f * a);

			da += dda + dc;
			if (dc < dda * c)
			{
				dc += ((dda * c) * 2.0f) * dda;
			}
		}
	}
}

void Waveshaper::releaseResources()
{
	processorChain.reset();
}

void Waveshaper::sliderValueChanged(Slider* slider)
{
	if (slider->getName() == "mix_knob")
	{
		m = slider->getValue();
	}
	else if (slider->getName() == "pre_knob")
	{
		auto& preGain = processorChain.template get<0>();
		preg = slider->getValue();
		preGain.setGainDecibels(40.0f * preg);
	}
	else if (slider->getName() == "post_knob")
	{
		auto& postGain = processorChain.template get<2>();
		postg = slider->getValue();
		postGain.setGainDecibels((100 * postg) - 100.0f);
	}
	else if (slider->getName() == "attack_knob")
	{
		a = slider->getValue();
	}
	else if (slider->getName() == "curve_knob")
	{
		c = slider->getValue();
	}
}