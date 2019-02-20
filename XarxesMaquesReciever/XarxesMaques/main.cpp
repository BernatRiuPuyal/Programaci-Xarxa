
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <list>


bool end = false;

void ClientHandler(sf::TcpSocket *sock) {

	while (!end) {



	}

}


int main() {

	// Init Listener

	

	sf::TcpListener listener;

	std::list<sf::TcpSocket*> sockets;


	while (end) {

		sf::TcpSocket* sock = new sf::TcpSocket;

		listener.accept(*sock);

		


	}




}