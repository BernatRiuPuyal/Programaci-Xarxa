
#include <SFML/Network.hpp>
#include <iostream>




int main() {


	std::cout << "This is the Listener" << std::endl;

	sf::TcpListener listener;

	sf::Socket::Status status = listener.listen(50000);

	sf::TcpSocket socket;

	status = listener.accept(socket);


	if (status == sf::Socket::Done) {
		socket.send("hola", 4);

		char buffer[20];
		size_t size;

		socket.receive(buffer, 20, size);

		buffer[size] = '\0';

		std::cout << buffer << std::endl;
	}
	else {
		std::cout << status << std::endl;
	}


}

//int main() { // reciever
//
//	sf::TcpSocket sock;
//	sf::Socket::Status status = sock.connect("127.0.0.1", 50000, sf::seconds(15.f));
//
//
//	sock.send("hola", 4);
//	char buffer[10];
//	size_t size;
//
//	sock.receive(buffer, 10, size);
//	std::cout << buffer << std::endl;
//}