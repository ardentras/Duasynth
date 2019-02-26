/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "DuasynthAudioProcessor.h"
#include "DuasynthAudioProcessorEditor.h"

//==============================================================================
DuasynthAudioProcessor::DuasynthAudioProcessor() :
#ifndef JucePlugin_PreferredChannelConfigurations
     AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
	a_lfo(), b_lfo(), a_osc(a_lfo, b_lfo), b_osc(a_lfo, b_lfo), 
	a_filter(a_lfo, b_lfo), b_filter(a_lfo, b_lfo), waveshaper(a_lfo, b_lfo),
	chorus(a_lfo, b_lfo), am(0.0), fm(0.0)
{
	// AM Mod
	am_mod.setRange(0.0f, 1.0f, 1.0f / 150);
	am_mod.setValue(0.0f);
	am_mod.setName("am_knob");

	// FM Mod
	fm_mod.setRange(0.0f, 1.0f, 1.0f / 150);
	fm_mod.setValue(0.0f);
	fm_mod.setName("fm_knob");
}

DuasynthAudioProcessor::~DuasynthAudioProcessor()
{
}

//==============================================================================
const String DuasynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DuasynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DuasynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DuasynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DuasynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DuasynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DuasynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DuasynthAudioProcessor::setCurrentProgram (int index)
{
}

const String DuasynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void DuasynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DuasynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

	a_osc.prepareToPlay(sampleRate, samplesPerBlock);
	b_osc.prepareToPlay(sampleRate, samplesPerBlock);

	a_filter.setSampleRate(sampleRate);
	b_filter.setSampleRate(sampleRate);

	chorus.setSampleRate(sampleRate);
	chorus.prepareToPlay(sampleRate, samplesPerBlock);

	waveshaper.setSampleRate(sampleRate);
	waveshaper.prepareToPlay(sampleRate, samplesPerBlock);

	for (int i = 0; i < a_osc.getSynth().getNumVoices(); i++)
	{
		DuasynthWaveVoice* voice = (DuasynthWaveVoice*)a_osc.getSynth().getVoice(i);
		voice->setFMBuffSize(samplesPerBlock);
	}

	for (int i = 0; i < b_osc.getSynth().getNumVoices(); i++)
	{
		DuasynthWaveVoice* voice = (DuasynthWaveVoice*)b_osc.getSynth().getVoice(i);
		voice->setFMBuffSize(samplesPerBlock);
	}

	midiCollector.reset(sampleRate);
}

void DuasynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
	a_osc.releaseResources();
	b_osc.releaseResources();
	a_filter.releaseResources();
	b_filter.releaseResources();
	chorus.releaseResources();
	waveshaper.releaseResources();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DuasynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DuasynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
	AudioBuffer<float> buff2;

    auto totalNumInputChannels  = buffer.getNumChannels();
    auto totalNumOutputChannels = buffer.getNumChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

	midiCollector.removeNextBlockOfMessages(midiMessages, buffer.getNumSamples());

	buff2.makeCopyOf(buffer);

	b_osc.getNextAudioBlock(buff2, midiMessages);
	b_filter.processSamples(buff2, buff2.getNumSamples());

	if (!a_osc.getChangingVoices() && !b_osc.getChangingVoices())
	{
		for (int i = 0; i < a_osc.getSynth().getNumVoices(); i++)
		{
			a_osc.setFMBuff(b_osc.getFMBuff(i), i, fm);
		}
	}

	a_osc.getNextAudioBlock(buffer, midiMessages);
	a_filter.processSamples(buffer, buffer.getNumSamples());
	
	juce::dsp::AudioBlock<float> block = juce::dsp::AudioBlock<float>(buffer).getSubBlock((size_t)0, (size_t)buffer.getNumSamples());
	juce::dsp::AudioBlock<float> block2 = juce::dsp::AudioBlock<float>(buff2).getSubBlock((size_t)0, (size_t)buff2.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        //float* channelData = buffer.getWritePointer (channel);
		for (int i = 0; i < buffer.getNumSamples() / buffer.getNumChannels(); i++)
		{
			block.addSample(channel, i, block2.getSample(channel, i) * am);
		}

		buff2.applyGain(channel, 0, buffer.getNumSamples(), 1.0f - (fm > am ? fm : am));

		buffer.addFrom(channel, 0, buff2, channel, 0, buffer.getNumSamples());
    }

	chorus.processSamples(buffer, buffer.getNumSamples());
	
	if (a_osc.getSynth().hasNoteStarted())
	{
		waveshaper.resetParams();
	}

	waveshaper.processSamples(buffer, buffer.getNumSamples());
}

//==============================================================================
bool DuasynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DuasynthAudioProcessor::createEditor()
{
    return new DuasynthAudioProcessorEditor (*this);
}

//==============================================================================
void DuasynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DuasynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DuasynthAudioProcessor();
}
