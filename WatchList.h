#pragma once
#include"Tape.h"
#include"Repository.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>

using namespace std;

class WatchList : public virtual Repository
{
private:
	unsigned int current;
	
public:
	WatchList(const string& fileName);

	//checks if the watch list is empty
	bool isEmpty();

	//starts the watch list
	void play();

	//returns the tape that is currently playing
	TElem getCurrentTape();

	//moves to the next element
	void next();

	//checks by title if the tape is or not in the watchlist
	bool find(std::string title);

	void addTape(TElem newElem) override;

	//reads the data from the file
	void loadData() override;

	//writes the data into the file
	void writeData() override;

	//writes the data into an html file
	void writeHTML();

	string getFileName() const { return this->fileName; };

};

