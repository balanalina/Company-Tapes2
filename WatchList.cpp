#include "WatchList.h"

WatchList::WatchList(const string& fileName)
{
	this->fileName = fileName;
	this->current = 0;
}


bool WatchList::isEmpty()
{
	if (this->tapes.size() == 0)
		return true;
	return false;
}

void WatchList::play()
{
	this->tapes.at(this->current).play();
	//this->tapes.getElem(this->current).play();
}

TElem WatchList::getCurrentTape()
{
	//return this->tapes.getElem(this->current);
	return this->tapes.at(this->current);

}

void WatchList::next()
{
	this->current++;
	if (this->current == this->tapes.size())
		this->current = 0;

}

bool WatchList::find(std::string title) {
	for (TElem const& el : this->tapes) {
		if (el.getTitle().compare(title) == 0)
			return true;
	}
	return false;
}

void WatchList::addTape(TElem newElem)
{
	this->tapes.push_back(newElem);
}

void WatchList::loadData()
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
				//Tape t = new Tape{ result.at(0),result.at(1),Date{static_cast<unsigned int>(stoi(result.at(5))),static_cast<unsigned int>(stoi(result.at(4))),static_cast<unsigned int>(stoi(result.at(3)))},static_cast<unsigned int>(stoi(result.at(2))),result.at(6) };
				this->tapes.push_back(Tape{ result.at(0),result.at(1),Date{static_cast<unsigned int>(stoi(result.at(5))),static_cast<unsigned int>(stoi(result.at(4))),static_cast<unsigned int>(stoi(result.at(3)))},static_cast<unsigned int>(stoi(result.at(2))),result.at(6) });
		}
		myFile.close();
	}
	else
		throw MyException{ "Could not open the file! \n" };
}

void WatchList::writeData()
{
	//delete the existing content
	ofstream emptyFile(this->fileName, ios::trunc);
	emptyFile.close();

	//write the new content to the file
	ofstream myFile;
	myFile.open(this->fileName);
	if (myFile.is_open()) {
		for (TElem el : this->tapes) {
			string line; //formt for output
			line = el.getTitle() + "," + el.getSection() + "," + to_string(el.getAccess()) + "," + to_string(el.getCreationDate().getMonth()) + "," +
				to_string(el.getCreationDate().getDay()) + "," + to_string(el.getCreationDate().getYear()) + "," + el.getSource() + "\n";
			myFile << line;
		}
		myFile.close();
	}
	else
		throw MyException{ "Could not open the file! \n" };
}

void WatchList::writeHTML()
{
	//delete the existing content
	ofstream emptyFile(this->fileName, ios::trunc);
	emptyFile.close();

	//write the new content to the file
	ofstream myFile;
	myFile.open(this->fileName);
	myFile << "<!DOCTYPE HTML><head>Watch list</head><body>\n";
	myFile << "<table border = \"1\">\n";
	myFile << "<tr>\n<td>Title</td>\n<td>Section</td>\n<td>Access</td>\n<td>Date</td>\n<td>Source</td>\n</tr>\n";
	if (myFile.is_open()) {
		if (this->tapes.size() != 0) {
			for (TElem el : this->tapes) {
				myFile << "<tr>\n";
				string line;
				line = "<td>" + el.getTitle() + "</td>\n<td>" + el.getSection() + "</td>\n<td>" +
					to_string(el.getAccess()) + "</td>\n<td>" + el.getCreationDate().DateToString() +
					"</td>\n<td><a href=\"" + el.getSource() + "\">Link</a></td>\n";
				myFile << line;
				myFile << "</tr>\n";
			}
		}
		myFile << "</table>\n</body>\n</hmtl>";
		myFile.close();
	}
	else
		throw MyException{ "Could not open the file! \n" };
}
