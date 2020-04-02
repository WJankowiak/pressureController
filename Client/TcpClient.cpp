#include "TcpClient.hpp"
#include <iostream>
bool TcpClient::connect()
{
	return socket.connect("127.0.0.1", 53000) == sf::Socket::Done;
}

void TcpClient::disconnect()
{
	return socket.disconnect();
}

bool TcpClient::isReceiving()
{
	return socket.receive(cacheData) == sf::Socket::Status::Done;
}

void TcpClient::send_packet(sf::Packet packet_to_send)
{
	sf::Socket::Status st = socket.send(packet_to_send);
}

sf::Packet TcpClient::receive_packet()
{
	sf::Packet received_packet;
	if (socket.receive(received_packet) != sf::Socket::Done)
		std::cout << "Failed to receive data\n";
	return received_packet;
}

short TcpClient::getCurrentPressure()
{
	sf::Packet packet;
	packet << (int)EPacketType::GetPressure;
	send_packet(packet);
	std::cout << "REQUEST TO GET PRESSURE SENT" << std::endl;
	return 0;
}

void TcpClient::setPressure(short pressure)
{
	sf::Packet packet;
	packet << (int)EPacketType::SetPressure << pressure;
	send_packet(packet);
	std::cout << "REQUEST TO SET PRESSURE SENT" << std::endl;
}

void TcpClient::getVersion()
{
	sf::Packet packet;
	packet << (int)EPacketType::GetVersion;
	send_packet(packet);
}

void TcpClient::updatePressure()
{
	short data;
	cacheData >> data;
	if (data == -1) 
	{
		std::cout << "SETTING OF PRESSURE FAILED" << std::endl;
	} else {
		std::cout << "Pressure got updated - Current value: " << data << std::endl;
	}
}

void TcpClient::manageIncomming() {
	int data;
	cacheData >> data;
	EPacketType packet_type = static_cast<EPacketType>(data);
	if (packet_type == EPacketType::GetPressure) {
		short pressure;
		cacheData >> pressure;
		std::cout << "Current pressure is: " << pressure << std::endl;
	}
	else if (packet_type == EPacketType::SetPressure) {
		updatePressure();
	}
	else if (packet_type == EPacketType::GetVersion) {
		int major, minor;
		cacheData >> major >> minor;
		std::cout << "Current version is:" << major << ',' << minor << std::endl;
	}
	else if (packet_type == EPacketType::GetInfo) {
		std::cout << "HARDWARE INFO NOT YET SUPPORTED" << std::endl;
	}
}

