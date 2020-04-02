#include "ApplicationRunner.hpp"
#include <iostream>
#include <thread>
void ApplicationRunner::run()
{
	printMenu();
	controller = 10;
	while (controller > 0) {
		std::thread th1(&ApplicationRunner::handleMenu,this);
		std::thread th2(&ApplicationRunner::handleIncoming,this);
		th2.join();
		th1.join();
	}
} 

void ApplicationRunner::printMenu() {
	std::cout << "If not yet connected, press 1 to connect to DEVICE" << std::endl;
	std::cout << "Press 2 to get current PRESSURE set on DEVICE" << std::endl;
	std::cout << "Press 3 to change PRESSURE set on DEVICE" << std::endl;
	std::cout << "Press 4 to get SOFTWARE VERSION of the DEVICE" << std::endl;
	std::cout << "Press 5 to disconnect from DEVICE" << std::endl;
	std::cout << "Press 0 to exit program" << std::endl << std::endl;
}

void ApplicationRunner::handleIncoming()
{
	if (client.isReceiving())
	{
		client.manageIncomming();
	}
}

void ApplicationRunner::handleMenu()
{
	if (std::cin >> controller)
	{
		switch (controller)
		{
			case 1:
			{
				std::cout << "Connection " << (client.connect() ? "Succesfull" : "Unsuccesfull") << std::endl;
				break;
			}
			case 2:
			{
				client.getCurrentPressure();
				break;
			}
			case 3:
			{
				std::cout << "Provide a value to set: ";
				std::cin.clear();
				int value;
				std::cin >> value;
				client.setPressure(value);
				break;
			}
			case 4:
			{
				client.getVersion();
				break;
			}
			case 5:
			{
				client.disconnect();
				break;
			}
			default:
			{
				std::cout << "WRONG OPTION" << std::endl;
				break;
			}
		}
		printMenu();
	}
}