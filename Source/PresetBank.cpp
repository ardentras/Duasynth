/*
  ==============================================================================

    PresetBank.cpp
    Created: 14 Jan 2019 7:53:19pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "PresetBank.h"

PresetBank::PresetBank()
	: theName("name_label", "Presets"), loadButton("load", ""), saveButton("save", "")
{
	char** err;
	int retval;

	initialiseUI();

	retval = sqlite3_open("file:presets.db", &db);

	if (retval != SQLITE_OK)
	{
		std::cerr << "CRITICAL ERROR: Database for presets failed to open. Closing the program." << std::endl;
		exit(-1);
	}

	retval = sqlite3_exec(db, "SELECT * FROM presets;", NULL, NULL, err);
	if (retval != SQLITE_OK)
	{

	}
}

PresetBank::~PresetBank()
{
	sqlite3_close(db);
}

void PresetBank::initialiseUI()
{
	// Name
	theName.setFont(Font(24.0f, Font::plain));
	theName.setColour(Label::textColourId, Colours::white);
	theName.setJustificationType(Justification::centred);
	addAndMakeVisible(theName);

	// Load button
	loadButton.setButtonText("Load");
	loadButton.changeWidthToFitText();
	addAndMakeVisible(loadButton);

	// Save button
	saveButton.setButtonText("Save");
	saveButton.changeWidthToFitText();
	addAndMakeVisible(saveButton);

	setSize(100, 75);
}

void PresetBank::paint(Graphics&)
{

}

void PresetBank::resized()
{
	theName.setBounds(0.0f, 0.0f, getWidth(), 25.0f);

	loadButton.setBounds(5.0f, 40.0f, 40.0f, 25.0f);
	
	saveButton.setBounds(55.0f, 40.0f, 40.0f, 25.0f);
}

void PresetBank::store(vector<pair<string, vector<pair<string, float>>>> modules)
{
	string statement, csv;
	char** err;
	int retval;

	for (pair<string, vector<pair<string, float>>> module : modules)
	{
		string name = module.first;
		vector<pair<string, float>> params = module.second;

		statement = "INSERT INTO presets VALUES ('" + name + "', '";
		csv = "";

		for (pair<string, float> param : params)
		{
			if (param != params.back())
			{
				csv += param.first + "," + std::to_string(param.second) + ",";
			}
			else
			{
				csv += param.first + "," + std::to_string(param.second);
			}
		}

		statement += csv + "');";

		std::cout << statement << std::endl;

		retval = sqlite3_exec(db, statement.c_str(), NULL, NULL, err);
		sqlite3_free(err);
	}
}

vector<pair<string, vector<pair<string, float>>>> PresetBank::unstore()
{
	vector<pair<string, vector<pair<string, float>>>> params;

	return params;
}