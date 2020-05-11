#include "TXTRepo.h"

void TXTRepo::writeData()
{
	//delete the existing content
	ofstream emptyFile(this->fileName, ios::trunc);
	emptyFile.close();

	//write the new content to the file
	ofstream myFile;
	myFile.open(this->fileName);
	if (myFile.is_open()) {
		for (TElem el : this->tapes) {
			string line; //format for output
			line = el.getTitle() + "," + el.getSection() + "," + to_string(el.getAccess()) + "," + to_string(el.getCreationDate().getMonth()) + "," +
				to_string(el.getCreationDate().getDay()) + "," + to_string(el.getCreationDate().getYear()) + "," + el.getSource() + "\n";
			myFile << line;
		}
		myFile.close();
	}
	else
		throw MyException {"Could not open the file! \n"};
}

//read data from file
void TXTRepo::loadData()
{
	ifstream myFile;
	myFile.open(this->fileName);
	if (myFile.is_open()) {
		string input;
		vector<string> result;
		string token;
		while (!myFile.eof()) {
			getline(myFile, input);
			//split the input by delimiter
			result.clear();
			stringstream ss(input);
			while (getline(ss, token, ',')) {
				result.push_back(token);
			}
			if (result.size() == 7)
				this->tapes.push_back(Tape{ result.at(0),result.at(1),Date{static_cast<unsigned int>(stoi(result.at(5))),static_cast<unsigned int>(stoi(result.at(4))),static_cast<unsigned int>(stoi(result.at(3)))},static_cast<unsigned int>(stoi(result.at(2))),result.at(6) });
		}
		myFile.close();
	}
	else
		throw MyException { "Could not open the file! \n" };
}
