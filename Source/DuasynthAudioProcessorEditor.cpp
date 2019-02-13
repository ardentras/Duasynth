/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "DuasynthAudioProcessor.h"
#include "DuasynthAudioProcessorEditor.h"

//==============================================================================
DuasynthAudioProcessorEditor::DuasynthAudioProcessorEditor(DuasynthAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p), oscs("", "Oscillators"),
	filters("", "Filters"), lfos("", "LFOs"), mods("", "AM Mod FM")
{
	// Oscillators label
	oscs.setFont(Font(24.0f, Font::plain));
	oscs.setColour(Label::textColourId, Colours::white);
	oscs.setJustificationType(Justification::centred);
	addAndMakeVisible(oscs);
	addAndMakeVisible(processor.getAOsc());
	addAndMakeVisible(processor.getBOsc());

	// Filters label
	filters.setFont(Font(24.0f, Font::plain));
	filters.setColour(Label::textColourId, Colours::white);
	filters.setJustificationType(Justification::centred);
	addAndMakeVisible(filters);
	addAndMakeVisible(processor.getAFilter());
	addAndMakeVisible(processor.getBFilter());

	// LFOs label
	lfos.setFont(Font(24.0f, Font::plain));
	lfos.setColour(Label::textColourId, Colours::white);
	lfos.setJustificationType(Justification::centred);
	addAndMakeVisible(lfos);
	addAndMakeVisible(processor.getALFO());
	addAndMakeVisible(processor.getBLFO());

	// Presets
	addAndMakeVisible(preset);

	Button* button = (Button*)preset.getChildComponent(1);
	button->addListener(this);
	button = (Button*)preset.getChildComponent(2);
	button->addListener(this);

	// Modulations Label
	mods.setFont(Font(24.0f, Font::plain));
	mods.setColour(Label::textColourId, Colours::white);
	mods.setJustificationType(Justification::centred);
	addAndMakeVisible(mods);
	addAndMakeVisible(processor.getAMMod());
	addAndMakeVisible(processor.getFMMod());
	processor.getAMMod().addListener(this);
	processor.getFMMod().addListener(this);

	addAndMakeVisible(processor.getChorus());

	addAndMakeVisible(processor.getWaveshaper());

	setSize (475, 600);
}

DuasynthAudioProcessorEditor::~DuasynthAudioProcessorEditor()
{
}

//==============================================================================
void DuasynthAudioProcessorEditor::paint (Graphics& g)
{
}

void DuasynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	
	// Oscillators
	oscs.setBounds(
		ELEM_PADDING, // x
		ELEM_PADDING, // y
		(processor.getAOsc().getWidth() + ELEM_PADDING) * 2, // width
		25.0f); // height
	processor.getAOsc().setBounds(
		ELEM_PADDING, 
		ELEM_PADDING + oscs.getBounds().getHeight(), 
		processor.getAOsc().getWidth(), 
		processor.getAOsc().getHeight());
	processor.getBOsc().setBounds(
		(ELEM_PADDING * 2) + processor.getAOsc().getWidth(), 
		ELEM_PADDING + oscs.getBounds().getHeight(), 
		processor.getBOsc().getWidth(), 
		processor.getBOsc().getHeight());
	
	// Filters
	filters.setBounds(
		ELEM_PADDING, 
		10.0f + ELEM_PADDING + processor.getAOsc().getHeight() + oscs.getBounds().getHeight(), 
		(processor.getAFilter().getWidth() + ELEM_PADDING) * 2, 
		25.0f);
	processor.getAFilter().setBounds(
		ELEM_PADDING, 
		10.0f + ELEM_PADDING + processor.getAOsc().getHeight() + oscs.getBounds().getHeight() + filters.getBounds().getHeight(), 
		processor.getAFilter().getWidth(), 
		processor.getAFilter().getHeight());
	processor.getBFilter().setBounds(
		(ELEM_PADDING * 2) + processor.getAFilter().getWidth(), 
		10.0f + ELEM_PADDING + processor.getAOsc().getHeight() + oscs.getBounds().getHeight() + filters.getBounds().getHeight(), 
		processor.getBFilter().getWidth(), 
		processor.getBFilter().getHeight());

	// LFOs
	lfos.setBounds(
		ELEM_PADDING,
		20.0f + ELEM_PADDING + processor.getAOsc().getHeight() + oscs.getBounds().getHeight() + processor.getAFilter().getHeight() + filters.getHeight(),
		(processor.getAFilter().getWidth() + ELEM_PADDING) * 2,
		25.0f);
	processor.getALFO().setBounds(
		ELEM_PADDING,
		20.0f + ELEM_PADDING + processor.getAOsc().getHeight() + oscs.getBounds().getHeight() + filters.getBounds().getHeight() + processor.getAFilter().getHeight() + lfos.getBounds().getHeight(),
		processor.getALFO().getWidth(),
		processor.getALFO().getHeight());
	processor.getBLFO().setBounds(
		(ELEM_PADDING * 2) + processor.getAFilter().getWidth(),
		20.0f + ELEM_PADDING + processor.getAOsc().getHeight() + oscs.getBounds().getHeight() + filters.getBounds().getHeight() + processor.getAFilter().getHeight() + lfos.getBounds().getHeight(),
		processor.getBLFO().getWidth(),
		processor.getBLFO().getHeight());

	// Right Column (Preset, Mods, Chorus, WS)
	preset.setBounds(
		(ELEM_PADDING * 3) + (processor.getAFilter().getWidth() * 2) + 40,
		ELEM_PADDING,
		preset.getWidth(),
		preset.getHeight());
	mods.setBounds(
		(ELEM_PADDING * 3) + (processor.getAFilter().getWidth() * 2) + 40,
		ELEM_PADDING + preset.getHeight(),
		preset.getWidth(),
		25.0f);
	processor.getAMMod().setBounds(
		(ELEM_PADDING * 3) + (processor.getAFilter().getWidth() * 2) + 33,
		ELEM_PADDING + preset.getHeight() + 30.0f,
		50.0f,
		50.0f);
	processor.getFMMod().setBounds(
		(ELEM_PADDING * 3) + (processor.getAFilter().getWidth() * 2) + 100,
		ELEM_PADDING + preset.getHeight() + 30.0f,
		50.0f,
		50.0f);
	processor.getChorus().setBounds(
		(ELEM_PADDING * 3) + (processor.getAFilter().getWidth() * 2) + 40,
		ELEM_PADDING + preset.getHeight() + 80,
		processor.getWaveshaper().getWidth(),
		processor.getWaveshaper().getHeight());
	processor.getWaveshaper().setBounds(
		(ELEM_PADDING * 3) + (processor.getAFilter().getWidth() * 2) + 40, 
		ELEM_PADDING + preset.getHeight() + processor.getChorus().getHeight() + 100, 
		processor.getWaveshaper().getWidth(), 
		processor.getWaveshaper().getHeight());
}

void DuasynthAudioProcessorEditor::sliderDragEnded(Slider* slider)
{
	if (slider->getName() == "fm_knob")
	{
		processor.setFM(slider->getValue());
	}
	else if (slider->getName() == "am_knob")
	{
		processor.setAM(slider->getValue());
	}
}

void DuasynthAudioProcessorEditor::buttonClicked(Button* button)
{
	vector<pair<string, vector<pair<string, float>>>> params;
	string name;

	if (button->getName() == "load")
	{
		DialogWindow::LaunchOptions lo;
		LoadPresetComponent* lpc = new LoadPresetComponent();
		OptionalScopedPointer<Component> osp;
		osp.set(lpc, false);

		lpc->setComboBox(preset.getPresets());

		lo.dialogTitle = "Load Preset";
		lo.content = osp;

		int retval = lo.runModal();

		if (retval == 2)
		{
			ComboBox* cb = (ComboBox*)lpc->getChildComponent(1);

			name = cb->getItemText(cb->getSelectedItemIndex()).toStdString();

			params = preset.unstore(name);

			for (pair<string, vector<pair<string, float>>> param : params)
			{
				if (param.first == "a_osc")
				{
					processor.getAOsc().deserialize(param.second);
				}
				else if (param.first == "b_osc")
				{
					processor.getBOsc().deserialize(param.second);
				}
				else if (param.first == "a_filter")
				{
					processor.getAFilter().deserialize(param.second);
				}
				else if (param.first == "b_filter")
				{
					processor.getBFilter().deserialize(param.second);
				}
				else if (param.first == "chorus")
				{
					processor.getChorus().deserialize(param.second);
				}
				else if (param.first == "waveshaper")
				{
					processor.getWaveshaper().deserialize(param.second);
				}
				else if (param.first == "a_lfo")
				{
					processor.getALFO().deserialize(param.second);
				}
				else if (param.first == "b_lfo")
				{
					processor.getBLFO().deserialize(param.second);
				}
			}
		}

		delete lpc;
	}
	else if (button->getName() == "save")
	{
		DialogWindow::LaunchOptions lo;
		CreatePresetComponent* cpc = new CreatePresetComponent();
		OptionalScopedPointer<Component> osp;
		osp.set(cpc, false);

		lo.dialogTitle = "Create Preset";
		lo.content = osp;

		int retval = lo.runModal();

		if (retval == 2)
		{
			TextEditor* t = (TextEditor*)cpc->getChildComponent(1);

			name = t->getText().toStdString();

			params.push_back(pair<string, vector<pair<string, float>>>("a_osc", processor.getAOsc().serialize()));
			params.push_back(pair<string, vector<pair<string, float>>>("b_osc", processor.getBOsc().serialize()));
			params.push_back(pair<string, vector<pair<string, float>>>("a_filter", processor.getAFilter().serialize()));
			params.push_back(pair<string, vector<pair<string, float>>>("b_filter", processor.getBFilter().serialize()));
			params.push_back(pair<string, vector<pair<string, float>>>("chorus", processor.getChorus().serialize()));
			params.push_back(pair<string, vector<pair<string, float>>>("waveshaper", processor.getWaveshaper().serialize()));
			params.push_back(pair<string, vector<pair<string, float>>>("a_lfo", processor.getALFO().serialize()));
			params.push_back(pair<string, vector<pair<string, float>>>("b_lfo", processor.getBLFO().serialize()));

			preset.store(name, params);
		}

		delete cpc;
	}
}

