#pragma once
#include <SFML/Network.hpp>

enum class EPacketType {
	GetPressure,
	SetPressure,
	GetVersion,
	GetInfo
};

struct versionInfo {
	char versionMajor;
	char versionMinor;

	versionInfo(char major = 1, char minor = 0) :
		versionMajor(major),
		versionMinor(minor)
	{}
};

class TcpClient
{
private:
	sf::TcpSocket socket;
	sf::Packet cacheData;
	void send_packet(sf::Packet packet_to_send);

	sf::Packet receive_packet();

public:
	bool connect();

	void disconnect();

	bool isReceiving();

	short getCurrentPressure();

	void setPressure(short pressure);

	void getVersion();

	void updatePressure();

	void manageIncomming();

};

