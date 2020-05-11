#pragma once
#include"Repository.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

class TXTRepo : public virtual Repository {

public:
	TXTRepo(){}

	//constructor
	TXTRepo(const string& fileName) { this->fileName = fileName; } 
	 
	//writes the data into the file
	void writeData() override;

	//reads the data from the file
	void loadData() override;

	~TXTRepo() {}
	
};

