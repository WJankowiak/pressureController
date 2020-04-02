#pragma once
#include "PressureController.hpp"
#include<memory>
enum class EDeviceState {
	Ok,
	DataInvalid
};

class PressureControllerHandler
{
private:
	std::shared_ptr<PressureController> device;

	//Current status of the device
	EDeviceState status;

	bool configurationOngoing = false;

public:
	/*public constructor.
	 * No pressure on device assumed
	*/
	PressureControllerHandler();

	bool setPressure(const short& pressure);

	short getPressure();

	EDeviceState getDeviceStatus();
};

