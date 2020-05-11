#pragma once
#include<iostream>
using namespace std;

class MyException : public std::exception {
private:
	string errorMessage;

public:
	MyException(const string& message) :errorMessage{ message } {}

	const char* what() const throw() override {
		return this->errorMessage.c_str();
	}

};
