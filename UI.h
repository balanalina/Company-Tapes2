#pragma once
#include"MyException.h"
#include"Service.h"
#include<Windows.h>
#include<string>
#include<stdlib.h>
#include<time.h>
#include"WatchList.h"
using namespace std;

class UI
{
private:
	WatchList* myWl;
	Service service;
	std::string Mode;

public:
	UI(const Service& s, WatchList* wl) : service(s), Mode(""), myWl(wl) {}

	void run();
	void setMode(const std::string& m) { Mode = m; }
	~UI();

private:
	void init();
	void printMenu();
	const std::string readTitle();
	const std::string readSection();
	const Date readDate();
	const std::string readSource();
	const unsigned int readAccess();
	void fileChoice();

};

