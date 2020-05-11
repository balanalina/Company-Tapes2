#include "TapeValidator.h"

void TapeValidator::validate(const Tape & tape)
{
	string err = "";
	nameValidator(tape.getTitle(),err);
	sectionValidator(tape.getSection(),err);
	dateValidator(tape.getCreationDate(),err);
	sourceValidator(tape.getSource(),err);
	if(err.size() != 0)
		throw MyException{err};
}

//the name must be at least 3 characters and start with an upper letter
void TapeValidator::nameValidator(const string & name,string& s)
{
	if (name.size() < 3 || islower(name[0]))
		s += "Title must be at least 3 characters and start with an upper letter! \n" ;
}

void TapeValidator::sectionValidator(const string & section,string& s)
{
	if(section.size() < 3 || islower(section[0]) )
		s += "Section must be at least 3 characters and start with an upper letter! \n" ;
}

void TapeValidator::dateValidator(const Date & date,string& s)
{
	if(date.getYear() > 2020 || date.getYear() < 2015)
		s += "The tape must be at most 5 years old! \n";
	if(date.getMonth() > 12 || date.getMonth() == 0)
		s += "That month doesn't really exist! \n";
	if(date.getDay() < 1 || date.getDay() > 31)
		s += "There is no such day that month! \n";
}

void TapeValidator::sourceValidator(const string & source, string& s)
{
	if(source.size() < 8 || source.rfind("https://",0) != 0)
		s += "The source must be valid! \n";
}
