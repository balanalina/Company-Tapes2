#include "UI.h"
#include<ctime>
#include<stdlib.h>

using namespace std;

void UI::run()
{
	cout << "Enter the mode (A / B) : ";
	std::string mode;
	getline(cin, mode);
	this->setMode(mode);
	this->fileChoice();
	int command;
	try {
		this->service.loadData();
	}
	catch (std::exception& e) {
		cout << e.what();
		std::exit(EXIT_FAILURE);
	}
	while (true) {
		UI::printMenu();
		cout << "Enter the commmand:";
		cin >> command;
		if (command == 0)
			break;
		if (command == 4 && this->Mode.compare("A") == 0) {
			vector<TElem> tapes = this->service.getAllTapes();
			for (TElem elem : tapes)
				cout << elem.toString();
		}
		if (command == 1 && this->Mode.compare("A") == 0) {
			std::string title = UI::readTitle();
			std::string section = UI::readSection();
			Date d = UI::readDate();
			std::string source = UI::readSource();
			try {
				this->service.addTapeToRepository(title, section, d, 0, source);
			}
			catch(std::exception& e){
				cout << e.what();
			}
		}
		if (command == 3 && this->Mode.compare("A") == 0) {
			std::string title;
			title = UI::readTitle();
			this->service.removeTapeFromRepository(title);
		}
		if (command == 2 & this->Mode.compare("A") == 0) {
			std::string title;
			title = UI::readTitle();
			cout << "Enter the new values!" << endl;
			std::string newTitle = UI::readTitle();
			std::string section = UI::readSection();
			Date d = UI::readDate();
			std::string source = UI::readSource();
			this->service.updateTape(title, newTitle, section, d, 0, source);
		}
		if (command == 1 && this->Mode.compare("B") == 0) {
			std::string userC = "";
			int i = 0;
			vector<TElem> tapes = this->service.getAllTapes();
			while (true) {
				if (i == tapes.size())
					i = 0;
				if (userC.compare("add") != 0) {
					cout << tapes.at(i).toString();
					tapes.at(i).play();
				}
				cout << "add (add the tape to your watchlist)" << endl;
				cout << "next (view the next tape)" << endl;
				cout << "exit" << endl;
				cin >> userC;
				if (userC.compare("next") == 0)
					i++;
				else
					if (userC.compare("add") == 0) {
						if (this->myWl->find(tapes.at(i).getTitle()) == false) {
							this->myWl->addTape(tapes.at(i));
							if (this->myWl->getFileName().find(".csv") != string::npos || this->myWl->getFileName().find(".CSV") != string::npos)
								this->myWl->writeData();
							else
								this->myWl->writeHTML();
						}
					}
					else
						break;
			}
		}
		if (command == 2 && this->Mode.compare("B") == 0) {
			vector<TElem> watchlist = this->myWl->getTapes();
			for (TElem elem : watchlist)
				cout << elem.toString();
		}
		if (command == 4 && this->Mode.compare("B") == 0) {
			std::string section = UI::readSection();
			unsigned int access = UI::readAccess();
			vector<TElem> tapes = this->service.getAllTapes();
			for (int i = 0; i < tapes.size(); i++)
				if (tapes.at(i).getSection().compare(section) == 0 && tapes.at(i).getAccess() < access)
					cout << tapes.at(i).toString();
		}
		if (command == 3 && this->Mode.compare("B") == 0) {
			if (this->myWl->getFileName().find(".csv") != string::npos || this->myWl->getFileName().find(".CSV") != string::npos) {
				string openNotepad = "notepad \"" + this->myWl->getFileName() + "\"";
				system(openNotepad.c_str());
			}
			else {
				string open = this->myWl->getFileName();
				ShellExecute(NULL, "open", open.c_str(), NULL, NULL, SW_SHOWNORMAL);

			}
		}

	}
	try {
		if(this->Mode.compare("A") == 0)
			this->service.writeData();
		else {
			if ((this->myWl->isEmpty() == true && this->myWl->getFileName().find(".html") == string::npos) || (this->myWl->isEmpty() == true && this->myWl->getFileName().find(".HTML") == string::npos))
				this->myWl->writeHTML();
		}
	}
	catch (std::exception e) {
		cout << e.what();
	}
}


void UI::printMenu()
{
	if (this->Mode.compare("A") == 0) {
		cout << "Menu:" << endl;
		cout << "0.Exit" << endl;
		cout << "1.Add Tape" << endl;
		cout << "2.Update Tape" << endl;
		cout << "3.Delete Tape" << endl;
		cout << "4.List Tapes" << endl;
	}
	else {
		cout << "Menu:" << endl;
		cout << "0.Exit" << endl;
		cout << "1.List Tapes" << endl;
		cout << "2.See Watch List" << endl;
		cout << "3.See Watch List File" << endl;
		cout << "4.List Section Access Count" << endl;
	}

}

void UI::fileChoice()
{
	if (this->Mode.compare("A") == 0) {
		string answer;
		cout << "Use default file? (Yes/No):  ";
		cin >> answer;
		if (answer.compare("Yes") == 0)
			this->service.setRepository(new TXTRepo{ "Tapes.txt" });
		else {
			string fileName;
			cout << "Enter the file name: ";
			cin >> fileName;
			this->service.setRepository(new TXTRepo{ fileName });
		}
	}
	else {
		this->service.setRepository(new TXTRepo{ "Tapes.txt" });
		string fileType;
		string answer;
		cout << "Choose the type of file (CSV,HTML): ";
		cin >> fileType;
		if (fileType.compare("HTML") == 0) {
			cout<<"Use default file? (Yes/No):  ";
			cin >> answer;
			if (answer.compare("Yes") == 0)
				this->myWl = new WatchList{"watchList.html"};
			else {
				string fileName;
				cout << "Enter the file name: ";
				cin >> fileName;
				this->myWl = new WatchList{ fileName };
			}
		}
		else {
			cout << "Use default file? (Yes/No):  ";
			cin >> answer;
			if (answer.compare("Yes") == 0)
				this->myWl = new WatchList{"watchList.csv"};
			else
			{
				string fileName;
				cout << "Enter the file name: ";
				cin >> fileName;
				this->myWl = new WatchList{fileName};
			}
		}

	}
	
}

const std::string UI::readTitle() {
	cout << "Enter the title of the tape: ";
	std::string title;
	cin >> title;
	return title;
}

const std::string UI::readSection() {
	cout << "Enter the section presented in the tape: ";
	std::string section;
	getline(cin, section);
	getline(cin, section);
	//cin >> section;
	return section;
}

const Date UI::readDate() {
	unsigned int year, month, day;
	cout << "Enter the year of the tape's creation: ";
	cin >> year;
	cout << "Enter the month:";
	cin >> month;
	cout << "Enter the day:";
	cin >> day;
	return Date(year, month, day);
}

const unsigned int UI::readAccess() {
	unsigned int access;
	cout << "Enter the access count: ";
	cin >> access;
	return access;
}


const std::string UI::readSource()
{
	std::string source;
	cout << "Enter the footage preview: ";
	cin >> source;
	return source;
}

UI::~UI() {
	delete this->myWl;
}
