#pragma once
//#include"MyException.h"
#include"Tape.h"
#include"TXTRepo.h"
#include"TapeValidator.h"
#include"Service.h"
#include<iostream>
#include<assert.h>
#include<string>
#include"WatchList.h"
using namespace std;
class Test
{
public:
	Test();
	void testAll();
	void testTape();
	void testTapeValidator();
	void testRepository();
	void testService();
	void testWatchList();
	void exceptionTitleValidator();
	void exceptionSectionValidator();
	void exceptionYearValidator();
	void exceptionMonthValidator();
	void exceptionDayValidator();
	void exceptionSourceValidator();
	void updateService_NotInRepo(Service & s);
	void updateService_Successful(Service & s);
	void removeService_NotInRepo(Service & s);
	void removeService_Succssesful(Service & s);
	void addService_Successful(Service & s);
	void addService_Duplicat_NotAdded(Service & s);
	void getSetTitle(Tape& t);
	void getSetSection(Tape& t);
	void getSetDate(Tape& t);
	void getSetAccess(Tape& t);
	void getSetSource(Tape& t);
};

