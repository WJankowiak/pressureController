#pragma once
class DeviceConnector
{
protected:
	virtual void notifyAll() = 0;

public:
	virtual ~DeviceConnector() {}
	virtual bool listen() = 0;
	virtual void run() = 0;
};

