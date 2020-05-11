#pragma once
#include<iostream>
#include<string>


//Class used for storing dates.
class Date {
private:
	unsigned int year;
	unsigned int month;
	unsigned int day;
public:
	Date() : year(0), month(0), day(0) {}
	Date(unsigned int year, unsigned int month, unsigned int day) : year(year), month(month), day(day) {}

	unsigned int getYear() const { return year; }
	unsigned int getMonth() const { return month; }
	unsigned int getDay() const { return day; }
	void setYear(unsigned int newYear) { year = newYear; }
	void setMonth(unsigned int newMonth) { month = newMonth; }
	void setDay(unsigned int newDay) { day = newDay; }
	std::string DateToString() {
		return std::to_string(month) + "/" + std::to_string(day) +
			"/" + std::to_string(year);
	}

};

class Tape
{
private:
	std::string title;
	std::string section;
	Date creationDate;
	unsigned int access;
	std::string source;

public:
	//default constructor
	Tape();
	//constructor with parameters
	Tape(const std::string& title, const std::string& section, const Date& creationDate, const unsigned int& access, const std::string& source);
	//getters
	std::string getTitle() const { return title; }
	std::string getSection() const { return section; }
	Date getCreationDate() const { return creationDate; }
	unsigned int getAccess() const { return access; }
	std::string getSource() const { return source; }
	//setters
	void setTitle(const std::string& newTitle) { title = newTitle; }
	void setSection(const std::string& newSection) { section = newSection; }
	void setDate(const Date& newDate) { creationDate = newDate; }
	void setAccess(const unsigned int& newAccess) { access = newAccess; }
	void setSource(const std::string& newSource) { source = newSource; }
	//returns a string with the tape's data
	std::string toString();
	//plays the tape
	void play();

	//~Tape(){}
};
