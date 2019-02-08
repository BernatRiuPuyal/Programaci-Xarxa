#pragma once
#include <iostream>


void clockManager();


void sharedWrite(std::string msg);


struct _question {
	std::string question;
	std::vector<std::string> options;
	int answer;
	int score;
};
