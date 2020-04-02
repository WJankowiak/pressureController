#pragma once
#include <string>

struct versionInfo {
	char versionMajor;
	char versionMinor;

	versionInfo(char major = 1, char minor = 0) :
		versionMajor(major),
		versionMinor(minor)
	{}
};

class PressureController {
private:
	// value indicating current pressure of the device
	short pressure;

	//Manufacturer's name of the device.
	const std::string hardwareInfo;

	//Current software version installed
	versionInfo version;

public:

	PressureController(short value = 0, std::string info = "Default Name");

	bool setPressure(const short& value);

	short getPressure() const;

	versionInfo getVersion() const;

	std::string getHardwareInfo() const;
};