#pragma once
#include"Tape.h"
#include"MyException.h"


class TapeValidator
{
private:

public:
	static void validate(const Tape& tape);

private:
	static void nameValidator(const string& name,string& s);

	static void sectionValidator(const string& section,string& s);

	static void dateValidator(const Date& date, string& s);

	static void sourceValidator(const string& source,string& s);
};

