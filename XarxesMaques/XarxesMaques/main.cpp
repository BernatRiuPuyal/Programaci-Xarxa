
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include "main.h"

int score;

std::mutex mutex;

std::vector<_question> questions;

int numQuestion;

bool end = false;

bool responseAnswered = false;

void sharedWrite(std::string msg) {

	mutex.lock();
	std::cout << msg << std::endl;
	mutex.unlock();

}
void sharedEndl() {
	mutex.lock();
	std::cout << std::endl;
	mutex.unlock();
}

char IntToStr(int i) {

	char numOption = i + '0';
	return numOption;
}




int main() {

	// SET QUESTIONS
	numQuestion = 0;
	score = 0;

	questions.push_back({ "3+4 ?", {"2", "6", "7" }, 3, 1 });
	questions.push_back({ "3*4 ? ", {"7", "12", "15" }, 2, 1 });
	questions.push_back({ "2-4 ? ", {"2", "-2", "6" }, 2 , 1});
	questions.push_back({ "9+0 ? ", {"9", "90", "10" }, 1, 1 });
	questions.push_back({ "How are you?", {"well", "so so", "sad" }, 1 , 1});
	
	   

	std::cout << "Game Started" << std::endl;

	score = 0;
	
	std::thread clockManager(clockManager);

	clockManager.detach();

	
	


	while (!end) {

		std::string input;

		std::cin >> input;

		if (input == "q") { // quit
			end = true;
		}
		else {
			int response = atoi(input.c_str());

			if (response == questions[numQuestion].answer) {
				score += questions[numQuestion].score;
				sharedWrite((std::string)"Correct Answer! | Score: " + std::to_string(score));
			}
			else {
				sharedWrite((std::string)"Wrong Answer! | Score: " + std::to_string(score));
			}
		}
			   
		responseAnswered = true;

	}

	

}

void clockManager() { // message each 5 seconds 

	sf::Clock clock;

	clock.restart();
	responseAnswered = true;

	while (numQuestion < questions.size()) {
		if (clock.getElapsedTime().asSeconds() > 5 /* number of seconds to wait*/) {

			if (!responseAnswered) {
				score--;
				sharedEndl();
				sharedWrite("Question not answered! Score: " + std::to_string(score));
				sharedEndl();
			}

			//ask question
			sharedEndl();
			sharedWrite(questions[numQuestion].question);

			for (int i = 1;i <= 3; i++) {		
				char numOption = IntToStr(i);
				sharedWrite( numOption + (std::string)") " + questions[numQuestion].options[i - 1]);
			}
			sharedEndl();
			numQuestion++;
			responseAnswered = false;

			//reset clock
			clock.restart();

		}
	}

	end = true;


}