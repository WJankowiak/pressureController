#include "DeviceTcpConnector.hpp"
#include <iostream>
#include <SFML/Network.hpp>

void DeviceTcpConnector::notifyAll()
{
	std::cout << "SENDING pressure data to all clients" << std::endl;
	sf::Packet pressureData;
	pressureData <<(int)EPacketType::SetPressure<< device.getPressure();
	for (sf::TcpSocket* client : clients) {
		if (client->send(pressureData) != sf::Socket::Status::Done) {
			std::cout << "SENDING UNSUCCESFULL" << std::endl;
		}
	}
}

void DeviceTcpConnector::notifyNotSet(sf::TcpSocket* destination) {
	std::cout << "SENDING pressure data set Fail" << std::endl;
	sf::Packet pressureData;
	pressureData << (int)EPacketType::SetPressure << -1;
		if (destination->send(pressureData) != sf::Socket::Status::Done) {
			std::cout << "SENDING UNSUCCESFULL" << std::endl;
		}
}

DeviceTcpConnector::DeviceTcpConnector()
{
	if (listener.listen(53000) != sf::Socket::Done)
	{
		std::cout << "...FAILED TO INITIALIZE SERVER..." << std::endl;
		return;
	}
	std::cout << "...SERVER INITIALIZED SUCCESFULLY..." << std::endl;
}

bool DeviceTcpConnector::listen()
{
	if (listener.listen(53000) != sf::Socket::Done)
	{
		return false;
	}
	return true;
}

void DeviceTcpConnector::run()
{
	selector.add(listener);
	while (true)
	{
		if (selector.wait()) 
		{
			if (selector.isReady(listener))
			{
				sf::TcpSocket* client = new sf::TcpSocket();
				if (client && listener.accept(*client) == sf::Socket::Done)
				{
					clients.push_back(client);
					selector.add(*client);
					std::cout << "...NEW CLIENT CONNECTED..." << std::endl;
				}
			}
			for (std::vector<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); it++)
			{
				sendDataIfNeeded(*it);
			}
		}
	}
}

void DeviceTcpConnector::sendDataIfNeeded(sf::TcpSocket* client)
{
		sf::TcpSocket& client_to_check = *client;
		if (selector.isReady(client_to_check))
		{
			sf::Packet packet;
			manageIncommingRequest(client_to_check, packet, client);
		}
		std::cout << "REQUESTS HANDLED" << std::endl;
}

void DeviceTcpConnector::manageIncommingRequest(sf::TcpSocket& client_to_check, sf::Packet& packet, sf::TcpSocket* client)
{
	if (client_to_check.receive(packet) == sf::Socket::Done) {
		std::cout << "PACKET RECEIVED" << std::endl;
		int type;
		packet >> type;
		EPacketType packet_type = static_cast<EPacketType>(type);
		chooseResponse(packet_type, client, packet);
	}
}

void DeviceTcpConnector::chooseResponse(EPacketType packet_type, sf::TcpSocket* client, sf::Packet& packet)
{
	if (packet_type == EPacketType::GetPressure) {
		sendPressureData(client);
	}
	else if (packet_type == EPacketType::SetPressure) {
		setPressure(packet, client);
	}
	else if (packet_type == EPacketType::GetVersion) {
		sendVersionData(client);
	}
	else if (packet_type == EPacketType::GetInfo) {
		sf::Packet packet;
		packet << (int)EPacketType::GetInfo;
		client->send(packet);
	}
}

void DeviceTcpConnector::sendVersionData(sf::TcpSocket* client)
{
	auto version = device.getVersion();
	std::cout << "VERSION INFO REQUESTED" << std::endl;
	sf::Packet packet;
	packet << (int)EPacketType::GetVersion << version.versionMajor << version.versionMinor;
	client->send(packet);
}

bool DeviceTcpConnector::sendPressureData(sf::TcpSocket* destination)
{
	std::cout << "PRESSURE DATA REQUESTED" << std::endl;
	sf::Packet packet;
	packet<<(int)EPacketType::GetPressure<< device.getPressure();
	destination->send(packet);
	return true;
}

bool DeviceTcpConnector::setPressure(sf::Packet packet, sf::TcpSocket* destination)
{
	std::cout << "PRESSURE DATA CHANGE REQUESTED" << std::endl;
	short pressure;
	packet >> pressure;
	std::cout << "SETTING PRESSURE DATA" << std::endl;
	if (device.setPressure(pressure)) {
		notifyAll();
	}
	else {
		notifyNotSet(destination);
	}
	return true;
}


