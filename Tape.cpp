#include "Tape.h"
#include<string>
#include<Windows.h>
#include<shellapi.h>


Tape::Tape() : title(""), section(""), creationDate(Date()), access(0), source("") {}

Tape::Tape(const std::string&  title, const std::string& section, const Date & creationDate, const unsigned int & access, const std::string & source)
{
	this->title = title;
	this->section = section;
	this->creationDate = creationDate;
	this->access = access;
	this->source = source;
}

std::string Tape::toString() {
	return this->title + " / " + this->section + " / " + std::to_string(this->access) + " / " + std::to_string(this->creationDate.getMonth()) + "-" + std::to_string(this->creationDate.getDay()) +
		"-" + std::to_string(this->creationDate.getYear()) + "\n";
}

void Tape::play()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->getSource().c_str(), NULL, SW_SHOWMAXIMIZED);

}

