/*
  ==============================================================================

    DuasynthSynthesiser.h
    Created: 2 Jan 2019 3:18:06pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class DuasynthSynthesiser : public Synthesiser
{
public:
	DuasynthSynthesiser() : Synthesiser(), note_started(false), note_playing(false) {}

	void clearVoices() { Synthesiser::clearVoices(); }

	int getNumVoices() const noexcept { return Synthesiser::getNumVoices(); }

	SynthesiserVoice* getVoice(int index) const { return Synthesiser::getVoice(index); }
		
	SynthesiserVoice* addVoice(SynthesiserVoice* newVoice) { return Synthesiser::addVoice(newVoice); }

	void removeVoice(int index) { Synthesiser::removeVoice(index); }

	void clearSounds() { Synthesiser::clearSounds(); }

	int getNumSounds() const noexcept { return Synthesiser::getNumSounds(); }

	SynthesiserSound::Ptr getSound(int index) const noexcept { return Synthesiser::getSound(index); }

	SynthesiserSound* addSound(const SynthesiserSound::Ptr &newSound) { return Synthesiser::addSound(newSound); }

	void removeSound(int index) { Synthesiser::removeSound(index); }

	void setNoteStealingEnabled(bool shouldStealNotes) { Synthesiser::setNoteStealingEnabled(shouldStealNotes); }

	bool isNoteStealingEnabled() const noexcept { return Synthesiser::isNoteStealingEnabled(); }

	virtual void noteOn(int midiChannel, int midiNoteNumber, float velocity) override
	{
		note_playing = true;
		note_started = true;

		Synthesiser::noteOn(midiChannel, midiNoteNumber, velocity);
	}

	virtual void noteOff(int midiChannel, int midiNoteNumber, float velocity, bool allowTailOff) override
	{
		note_playing = false;

		Synthesiser::noteOff(midiChannel, midiNoteNumber, velocity, allowTailOff);
	}

	bool hasNoteStarted() 
	{
		if (note_started)
		{
			note_started = false;
			return true;
		}
		return false;
	}

	bool isNotePlaying() { return note_playing; }

private:
	bool note_started;
	bool note_playing;
};