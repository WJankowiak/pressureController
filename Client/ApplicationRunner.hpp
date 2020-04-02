#pragma once
#include "TcpClient.hpp"
class ApplicationRunner
{
private:
	TcpClient client;
	int controller;
	void printMenu();
	void handleMenu();
	void handleIncoming();

public:
	void run();
};

