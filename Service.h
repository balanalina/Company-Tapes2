#pragma once
#include"TapeValidator.h"
#include"TXTRepo.h"

class Service
{
private:
	Repository* repo;


public:

	Service() {};
	Service(Repository* r) : repo{ r } {}
	~Service() { delete repo; }

	void setRepository(Repository* r) { this->repo = r; }

	Repository* getRepo() { return this->repo; }
	vector<TElem> getAllTapes() const { return this->repo->getTapes(); }

	void loadData() { this->repo->loadData(); }
	void writeData() { this->repo->writeData(); }

	void addTapeToRepository(const std::string& title, const std::string& section, const Date& date, const unsigned int& access, const std::string& source);
	void removeTapeFromRepository(const std::string& title);
	void updateTape(const std::string& title, const std::string& newTitle, const std::string& newSection, const Date& data, const unsigned int& newAccess, const std::string& newSource);
};

