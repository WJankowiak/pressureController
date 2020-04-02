#pragma once
#include <vector>
#include <SFML/Network.hpp>
#include "PressureController.hpp"
#include "DeviceConnector.hpp"
enum class EPacketType {
	GetPressure,
	SetPressure,
	GetVersion,
	GetInfo
};
class DeviceTcpConnector : public DeviceConnector
{
private:
	void sendDataIfNeeded(sf::TcpSocket* client);
	void manageIncommingRequest(sf::TcpSocket& client_to_check, sf::Packet& packet, sf::TcpSocket* client);
	void chooseResponse(EPacketType packet_type, sf::TcpSocket* client, sf::Packet& packet);
	void sendVersionData(sf::TcpSocket* client);
	void notifyAll();
	void notifyNotSet(sf::TcpSocket* destination);

	bool sendPressureData(sf::TcpSocket* destination);
	bool setPressure(sf::Packet pressure, sf::TcpSocket* destination);
	bool listen();

	sf::TcpListener listener;
	std::vector<sf::TcpSocket*> clients;
	sf::SocketSelector selector;
	PressureController device;

public :	
	DeviceTcpConnector();
	~DeviceTcpConnector() {};
	void run();
};

