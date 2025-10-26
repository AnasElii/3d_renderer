#pragma once

class Application;

class IPlatformAdapter {
public:
	virtual void StartWindowed(int x, int y, unsigned int w, unsigned int h, int antialiasing, Application& app, int nCmdShow = 1) = 0;
	virtual void finish(Application& app) = 0;
};
