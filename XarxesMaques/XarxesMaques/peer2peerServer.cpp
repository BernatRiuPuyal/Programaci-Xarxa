#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>


#define NUMPLAYERS 4

struct Direction {

	sf::IpAddress IP;
	unsigned short port;



};


int main() {

	// Listener al puerto 50 000

	sf::TcpListener listener;


	for (int i = 0; i < NUMPLAYERS; i++) {

		sf::TcpSocket sock;

		listener.accept(sock);

		// SEND MESSAGE WITH INFO

		// GET INFORMATION OF THIS SOCKET

		Direction newConection;
		newConection.IP = sock.getRemoteAddress();
		newConection.port = sock.getRemotePort();


	}



}