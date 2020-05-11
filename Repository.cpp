#include "Repository.h"
#include<vector>

void Repository::addTape(TElem newElem)
{
	validator.validate(newElem);
	this->tapes.push_back(newElem);
}

void Repository::remove(int pos)
{
	this->tapes.erase(this->tapes.begin() + pos);
}

int Repository::findPosByTitle(const std::string & title)
{
	for (int i = 0; i< this->tapes.size(); i++)
		if (this->tapes.at(i).getTitle().compare(title) == 0)
			return i;
	return -1;
}

void Repository::updateTape(const unsigned int& pos, const std::string & newTitle, const std::string & newSection, const Date & data, const unsigned int & newAccess, const std::string & newSource)
{
	this->tapes.at(pos).setTitle(newTitle);
	this->tapes.at(pos).setSection(newSection);
	this->tapes.at(pos).setAccess(newAccess);
	this->tapes.at(pos).setDate(data);
	this->tapes.at(pos).setSource(newSource);
}

TElem Repository::findByTitle(const std::string& title)
{
	for (TElem const& elem : this->tapes)
		if (elem.getTitle().compare(title) == 0)
			return elem;
	return Tape{};
}
