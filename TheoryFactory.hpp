#pragma once
//THIS FILE SHOWS POSSIBLE IMPLEMENTATION OF DEVICE CONNECTOR FACTORY
#ifdef SHOWOFF
#define

enum class EConnectorType {
	TCP,
	UDP,
	OTHER
};
//Assume this static method is defined in DeviceConnector.hpp
DeviceConnector* Create(EConnectorType type) {
	if (type == EConnectorType::TCP) {
		return new DeviceTcpConnector;
	} else if (type == EConnectorType::UDP) {
		return new DeviceUdpConnector;
	} else if (type == EConnectorType::Other) {
		return new DeviceOtherConnector;
	} else return NULL;
}
#endif