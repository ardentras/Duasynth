/*
  ==============================================================================

    PresetBank.cpp
    Created: 14 Jan 2019 7:53:19pm
    Author:  shaun.rasmusen

  ==============================================================================
*/

#include "PresetBank.h"

int parse_params(void* preset, int count, char** data, char** cols);

int parse_params(void* preset, int count, char** data, char** cols)
{
	Preset* p = (Preset*)(preset);
	vector<pair<string, float>> params;
	pair<string, float> pr;

	if (data[2] != NULL)
	{
		char* tok = strtok(data[2], ",");

		while (tok != NULL)
		{
			pr.first = tok;
			tok = strtok(NULL, ",");
			pr.second = atof(tok);
			params.push_back(pr);

			tok = strtok(NULL, ",");
		}

		p->addParam(data[1], params);
	}

	return 0;
}

PresetBank::PresetBank()
	: theName("name_label", "Presets"), loadButton("load", ""), saveButton("save", "")
{
	char** err = nullptr;
	int retval;

	initialiseUI();

	sqlite3_config(SQLITE_CONFIG_URI, -1);

	retval = sqlite3_open("file:presets.db", &db);

	if (retval != SQLITE_OK)
	{
		std::cerr << "CRITICAL ERROR: Database for presets failed to open. Closing the program." << std::endl;
		exit(-1);
	}

	char* stmt = "CREATE TABLE IF NOT EXISTS presets(name TEXT);";
	sqlite3_exec(db, stmt, NULL, NULL, err);
	if (err != nullptr)
	{
		sqlite3_free(err);
		err = nullptr;
	}

	char* stmt2 = "CREATE TABLE IF NOT EXISTS preset_params(id INT, name TEXT, params TEXT);";
	sqlite3_exec(db, stmt2, NULL, NULL, err);
	if (err != nullptr)
	{
		sqlite3_free(err);
		err = nullptr;
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

void PresetBank::store(string name, vector<pair<string, vector<pair<string, float>>>> modules)
{
	string statement, csv;
	char** err = nullptr;
	int retval;
	bool exists = false;

	Preset p;

	p.setName(name);

	statement = "SELECT * FROM presets WHERE name = '" + name + "';";

	retval = sqlite3_exec(db, statement.c_str(), NULL, NULL, err);
	if (err != nullptr)
	{
		sqlite3_free(err);
		err = nullptr;
	}

	if (!exists)
	{
		statement = "INSERT INTO presets VALUES ('" + name + "');";

		retval = sqlite3_exec(db, statement.c_str(), NULL, NULL, err);
		if (err != nullptr)
		{
			sqlite3_free(err);
			err = nullptr;
		}
	}

	for (pair<string, vector<pair<string, float>>> module : modules)
	{
		string name = module.first;
		vector<pair<string, float>> params = module.second;

		if (exists)
		{
			statement = "UPDATE preset_params SET params = '";
		}
		else
		{
			statement = "INSERT INTO preset_params VALUES ((SELECT rowid FROM presets WHERE name = '" + p.getName() + "'), '" + name + "', '";
		}

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

		p.addParam(name, params);

		if (exists)
		{
			statement = " WHERE id = (SELECT rowid FROM presets WHERE name = '" + p.getName() + "') AND name = '" + name + "';";
		}
		else
		{
			statement += csv + "');";
		}

		retval = sqlite3_exec(db, statement.c_str(), NULL, NULL, err);
		if (err != nullptr)
		{
			sqlite3_free(err);
			err = nullptr;
		}
	}

	curr_preset = p;
}

vector<pair<string, vector<pair<string, float>>>> PresetBank::unstore(string name)
{
	string statement, csv;
	char** err = nullptr;
	int retval;

	statement = "SELECT * FROM preset_params WHERE id = (SELECT rowid FROM presets WHERE name = '" + name + "');";

	retval = sqlite3_exec(db, statement.c_str(), parse_params, &curr_preset, err);
	if (err != nullptr)
	{
		sqlite3_free(err);
		err = nullptr;
	}

	return curr_preset.getParameters();
}