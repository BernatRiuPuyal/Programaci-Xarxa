#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <thread>
#include <string>
#include <iostream>
#include <vector>
#include <mutex>

#define MAX_MENSAJES 30

std::vector<std::string> aMensajes;

std::mutex mutex;

void sharedWrite(sf::String msg) {

	mutex.lock();

	aMensajes.push_back(msg);

	mutex.unlock();

}


void reading(sf::TcpSocket* sock) {

	while (true) {

		sf::Packet pack;

		sf::String str;

		if (sock->receive(pack) == sf::Socket::Done) {

			pack >> str;

			sharedWrite(str);
		}
		else if (sock->receive(pack) == sf::Socket::Disconnected) {
			sharedWrite("OTHER USER DISCONECTED");
			break;
		}
	}

}


int main()
{
	
	
	sf::Vector2i screenDimensions(800, 600);

	sf::RenderWindow window;
	window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Chat");

	sf::Font font;
	if (!font.loadFromFile("courbd.ttf"))
	{
		std::cout << "Can't load the font file" << std::endl;
	}

	sf::String mensaje = " >";

	sf::Text chattingText(mensaje, font, 14);
	chattingText.setFillColor(sf::Color(0, 160, 0));
	chattingText.setStyle(sf::Text::Bold);
	

	sf::Text text(mensaje, font, 14);
	text.setFillColor(sf::Color(0, 160, 0));
	text.setStyle(sf::Text::Bold);
	text.setPosition(0, 560);

	sf::RectangleShape separator(sf::Vector2f(800, 5));
	separator.setFillColor(sf::Color(200, 200, 200, 255));
	separator.setPosition(0, 550);

	// CONNECT SOCKET

	sf::TcpListener listener;

	listener.listen(50000);

	sf::TcpSocket socket;

	if (listener.accept(socket) != sf::Socket::Status::Done) {

		std::cout << "ERROR CONNECTING SERVER";
		exit(1);
	}
	   
	// create thread of reading

	std::thread t(&reading, &socket);

	t.detach();

	
	
	while (window.isOpen())
	{
		sf::Event evento;
		while (window.pollEvent(evento))
		{
			switch (evento.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (evento.key.code == sf::Keyboard::Escape)
					window.close();
				else if (evento.key.code == sf::Keyboard::Return)
				{
					sharedWrite(mensaje);


					
					if (aMensajes.size() > 25)
					{
						aMensajes.erase(aMensajes.begin(), aMensajes.begin() + 1);
					}

					// SEND

					sf::Packet pack;

					pack << mensaje;

					socket.send(pack);

					pack.clear();

					mensaje = ">";
				}
				break;
			case sf::Event::TextEntered:
				if (evento.text.unicode >= 32 && evento.text.unicode <= 126)
					mensaje += (char)evento.text.unicode;
				else if (evento.text.unicode == 8 && mensaje.getSize() > 0)
					mensaje.erase(mensaje.getSize() - 1, mensaje.getSize());
				break;
			}
		}
		window.draw(separator);
		for (size_t i = 0; i < aMensajes.size(); i++)
		{
			std::string chatting = aMensajes[i];
			chattingText.setPosition(sf::Vector2f(0, 20 * i));
			chattingText.setString(chatting);
			window.draw(chattingText);
		}
		std::string mensaje_ = mensaje + "_";
		text.setString(mensaje_);
		window.draw(text);

		
		window.display();
		window.clear();
	}
	
}