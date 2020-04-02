#include "PressureController.hpp"

PressureController::PressureController(short value, std::string info) :
	pressure(value),
	hardwareInfo(info)
{
	version = versionInfo();
	version.versionMajor = 3;
	version.versionMinor = 5;
}

bool PressureController::setPressure(const short& value) {
	if (value <= 10000 && value >= 0) {
		pressure = value;
		return true;
	}
	return false;
}

short PressureController::getPressure() const {
	return pressure;
}

versionInfo PressureController::getVersion() const {
	return version;
}

std::string PressureController::getHardwareInfo() const {
	return hardwareInfo;
}