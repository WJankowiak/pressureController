#include "PressureControllerHandler.hpp"

PressureControllerHandler::PressureControllerHandler()
{
	status = EDeviceState::Ok;
	device->setPressure(20);
}

bool PressureControllerHandler::setPressure(const short& pressure)
{
	if (!configurationOngoing)
	{
		configurationOngoing = true;
		device->setPressure(pressure);
		configurationOngoing = false;
		return true;
	}
	else {
		return false;
	}
}

short PressureControllerHandler::getPressure()
{
	if(!configurationOngoing)
	{
		return device->getPressure();
	}
	else {
		return -1;
	}
}

EDeviceState PressureControllerHandler::getDeviceStatus()
{
	return status;
}
