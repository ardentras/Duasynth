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
	DuasynthSynthesiser() : Synthesiser(), note_started(false) {}

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
		note_started = true;

		Synthesiser::noteOn(midiChannel, midiNoteNumber, velocity);
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

private:
	bool note_started;
};