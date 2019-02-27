
#include <SFML/Network.hpp>
#include <vector>


#define MAXPLAYERS 4

int main() {


	sf::TcpSocket sock;

	sock.connect("hole", 50000);


	std::vector<sf::Socket*> sockets;


	//RECIEVE PEERS INFORMATION
	sf::Packet pack;

	sock.receive(pack);

	// extract pack
	int numSocks;

	sf::IpAddress  adress;
	unsigned short port;

	for (int i = 0; i < numSocks; i++) {

		sf::TcpSocket * newSock = new sf::TcpSocket;

		newSock->connect(adress, port);

		sockets.push_back(newSock);


	}

	unsigned short localPort = sock.getLocalPort();

	sf::TcpListener listener;

	listener.listen(localPort);

	for (int i = sockets.size(); i < MAXPLAYERS; i++)
	{
		sf::TcpSocket *newSock = new sf::TcpSocket;

		listener.accept(*newSock);

		sockets.push_back(newSock);
	}



}

