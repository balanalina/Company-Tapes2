#include "Service.h"

void Service::addTapeToRepository(const std::string & title, const std::string & section, const Date & date, const unsigned int & access, const std::string & source)
{
	if (this->repo->findPosByTitle(title) != -1) {
		return;
	}
	this->repo->addTape(Tape{ title,section,date,access,source });
}

void Service::removeTapeFromRepository(const std::string& title)
{
	int pos = this->repo->findPosByTitle(title);
	if (pos == -1)
		return;
	this->repo->remove(pos);
}

void Service::updateTape(const std::string & title, const std::string & newTitle, const std::string & newSection, const Date & data, const unsigned int & newAccess, const std::string & newSource)
{
	if (this->repo->findPosByTitle(title) == -1)
		return;
	this->repo->updateTape(this->repo->findPosByTitle(title), newTitle, newSection, data, newAccess, newSource);
}
