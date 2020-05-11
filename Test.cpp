#include "Test.h"
#include"Tape.h"
using namespace std;

Test::Test() {}

void Test::testAll()
{
	testTape();
	testRepository();
	testService();
	testWatchList();
}

void Test::testTape() {
	Tape tape{};
	getSetTitle(tape);
	getSetSection(tape);
	getSetDate(tape);
	getSetAccess(tape);
	getSetSource(tape);
}

void Test::testTapeValidator()
{
	exceptionTitleValidator();
	exceptionSectionValidator();
	exceptionYearValidator();
	exceptionMonthValidator();
	exceptionDayValidator();
	exceptionSourceValidator();

}


void Test::testRepository() {
	TXTRepo repo{};
	repo.addTape(Tape{ "Tape1","FoodCourt",Date{2019,5,16},3,"https://www.youtube.com/watch?v=gpviAfHcVmw" });
	repo.addTape(Tape{ "Tape2","FoodCourt",Date{2019,5,16},3,"https://www.youtube.com/watch?v=gpviAfHcVmw" });
	repo.addTape(Tape{ "Tape3","FoodCourt",Date{2019,5,16},3,"https://www.youtube.com/watch?v=gpviAfHcVmw" });
	repo.addTape(Tape{ "Tape4","FoodCourt",Date{2019,5,16},3,"https://www.youtube.com/watch?v=gpviAfHcVmw" });
	assert(repo.getTapes().size() == 4);
	repo.remove(1);
	repo.remove(1);
	assert(repo.getTapes().size() == 2);
	assert(repo.findByTitle("Tape4").getTitle().compare("Tape4") == 0);
	assert(repo.findPosByTitle("Tape4") == 1);
	TXTRepo r{"someNAme"};
	try {
		r.loadData();
		assert(false);
	}
	catch (std::exception& e) {
		assert(true);
	}
	r.setFileName("Tapes.txt");
	r.loadData();
	assert(r.getTapes().size() == 10);

}

void Test::testService() {
	Repository* r = new TXTRepo {};
	Service service{ r };
	addService_Successful(service);
	addService_Duplicat_NotAdded(service);
	removeService_Succssesful(service);
	removeService_NotInRepo(service);
	updateService_Successful(service);
	updateService_NotInRepo(service);
}

void Test::testWatchList()
{
	WatchList wl{"noFile"};
	assert(wl.isEmpty() == true);
	wl.addTape(Tape{ "Tape1","FoodCourt",Date{2019,5,16},3,"https://www.youtube.com/watch?v=gpviAfHcVmw" });
	wl.addTape(Tape{ "Tape2","FoodCourt",Date{2019,5,16},3,"https://www.youtube.com/watch?v=gpviAfHcVmw" });
	wl.addTape(Tape{ "Tape3","FoodCourt",Date{2019,5,16},3,"https://www.youtube.com/watch?v=gpviAfHcVmw" });
	wl.addTape(Tape{ "Tape4","FoodCourt",Date{2019,5,16},3,"https://www.youtube.com/watch?v=gpviAfHcVmw" });
	assert(wl.isEmpty() == false);
	assert(wl.getCurrentTape().getTitle().compare("Tape1") == 0);
	wl.next();
	assert(wl.getCurrentTape().getTitle().compare("Tape1") != 0);
	wl.next();
	wl.next();
	wl.next();
	assert(wl.getCurrentTape().getTitle().compare("Tape1") == 0);
	assert(wl.find("Tape4") == true);
	assert(wl.find("Tape5") == false);
}

void Test::exceptionTitleValidator()
{
	try {
		TapeValidator::validate(Tape{ "cL", "FoodCourt", Date{ 2019,5,16 }, 3, "https://www.youtube.com/watch?v=gpviAfHcVmw" });
		assert(false);
	}
	catch (MyException& e) {
		assert(true);
	}
}

void Test::exceptionSectionValidator()
{
	try {
		TapeValidator::validate(Tape{ "Tape11", "gl", Date{ 2019,5,16 }, 3, "https://www.youtube.com/watch?v=gpviAfHcVmw" });
		assert(false);
	}
	catch (MyException& e) {
		assert(true);
	}
}

void Test::exceptionYearValidator()
{
	try {
		TapeValidator::validate(Tape{ "Tape11", "FoodCourt", Date{ 2021,5,16 }, 3, "https://www.youtube.com/watch?v=gpviAfHcVmw" });
		assert(false);
	}
	catch (MyException& e) {
		assert(true);
	}
	try {
		TapeValidator::validate(Tape{ "Tape11", "FoodCourt", Date{ 2014,5,16 }, 3, "https://www.youtube.com/watch?v=gpviAfHcVmw" });
		assert(false);
	}
	catch (MyException& e) {
		assert(true);
	}
}

void Test::exceptionMonthValidator()
{
	try {
		TapeValidator::validate(Tape{ "Tape11", "FoodCourt", Date{ 2019,0,16 }, 3, "https://www.youtube.com/watch?v=gpviAfHcVmw" });
		assert(false);
	}
	catch (MyException& e) {
		assert(true);
	}
	try {
		TapeValidator::validate(Tape{ "Tape11", "FoodCourt", Date{ 2019,13,16 }, 3, "https://www.youtube.com/watch?v=gpviAfHcVmw" });
		assert(false);
	}
	catch (MyException& e) {
		assert(true);
	}
}

void Test::exceptionDayValidator()
{
	try {
		TapeValidator::validate(Tape{ "Tape11", "FoodCourt", Date{ 2019,5,32 }, 3, "https://www.youtube.com/watch?v=gpviAfHcVmw" });
		assert(false);
	}
	catch (MyException& e) {
		assert(true);
	}
}

void Test::exceptionSourceValidator()
{
	try {
		TapeValidator::validate(Tape{ "Tape11", "FoodCourt", Date{ 2019,5,16 }, 3, "www.youtube.com/watch?v=gpviAfHcVmw" });
		assert(false);
	}
	catch (MyException& e) {
		assert(true);
	}
}

void Test::updateService_NotInRepo(Service& s) {
	s.updateTape("Tape23541212", "", "", Date{}, 0, "");
	assert(s.getAllTapes().at(0).getAccess() != 0);
}

void Test::updateService_Successful(Service& s) {
	s.updateTape("Tape2", "Tape1", "Food", Date{ 2020,5,20 }, 20, "link");
	assert(s.getAllTapes().at(0).getAccess() == 20);
	assert(s.getAllTapes().at(0).getCreationDate().getYear() == 2020);
}

void Test::removeService_NotInRepo(Service& s) {
	s.removeTapeFromRepository("Taoe345");
	assert(s.getAllTapes().size() == 1);
}

void Test::removeService_Succssesful(Service& s) {
	s.removeTapeFromRepository("Tape1");
	assert(s.getRepo()->getTapes().size() == 1);
}

void Test::addService_Successful(Service& s) {
	s.addTapeToRepository("Tape1", "FoodCourt", Date{ 2019,5,16 }, 3, "https://www.youtube.com/watch?v=gpviAfHcVmw");
	s.addTapeToRepository("Tape2", "FoodCourt", Date{ 2019,5,16 }, 3, "https://www.youtube.com/watch?v=gpviAfHcVmw");
	//s.addTapeToRepository("Tape4", "FoodCourt", Date{ 2019,5,16 }, 3, "https://www.youtube.com/watch?v=gpviAfHcVmw");
	assert(s.getAllTapes().size() == 2);
}

void Test::addService_Duplicat_NotAdded(Service& s) {
	s.addTapeToRepository("Tape1", "FoodCourt", Date{ 2019,5,16 }, 3, "https://www.youtube.com/watch?v=gpviAfHcVmw");
	assert(s.getAllTapes().size() == 2);
}

void Test::getSetTitle(Tape& t) {
	t.setTitle("Tape12");
	assert(t.getTitle().compare("Tape12") == 0);
}

void Test::getSetSection(Tape& t) {
	t.setSection("Food");
	assert(t.getSection().compare("Food") == 0);
}

void Test::getSetDate(Tape& t) {
	t.setDate(Date{ 2019,5,6 });
	assert(t.getCreationDate().getDay() == 6);
	assert(t.getCreationDate().getMonth() == 5);
	assert(t.getCreationDate().getYear() == 2019);
}

void Test::getSetAccess(Tape& t) {
	t.setAccess(13);
	assert(t.getAccess() == 13);
}

void Test::getSetSource(Tape& t) {
	t.setSource("https://www.youtube.com/watch?v=gpviAfHcVmw");
	assert(t.getSource().compare("https://www.youtube.com/watch?v=gpviAfHcVmw") == 0);
}