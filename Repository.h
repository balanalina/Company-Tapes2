#pragma once
#include"Tape.h"
#include"TapeValidator.h"
#include"MyException.h"
#include<iostream>
#include<vector>
#include<string.h>

using namespace std;

typedef Tape TElem;
//interface for all repository classes
class Repository {
protected:
	vector<TElem> tapes;

	string fileName;

	TapeValidator validator;


public:

	//adds the element to the repository
	virtual void addTape(TElem newElem) ;

	//removes the element from position pos from the repository
	virtual void remove(int pos);

	//searches the tape with the gien title
	//returns an emty tape if none of the existing tapes match
	virtual TElem findByTitle(const std::string& title) ;

	//returns the position on whitch the tape with the given title is
	//returns -1 if there is no such tape
	virtual int findPosByTitle(const std::string& title);

	//returns the dynamic vector containing all tapes
	virtual vector<TElem> getTapes() const { return this->tapes; };

	//updates an existing tape
	virtual void updateTape(const unsigned int& pos, const std::string& newTitle, const std::string& newSection, const Date& data, const unsigned int& newAccess, const std::string& newSource);

	virtual void setFileName(string newFileName) { this->fileName = newFileName; }

	//writes the data into the file
	virtual void writeData() = 0;

	//reads the data from the file
	virtual void loadData() = 0;

	virtual ~Repository() {}

};

