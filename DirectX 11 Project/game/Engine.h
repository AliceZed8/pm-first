#pragma once
#include "WindowContainer.h"
#include "Timer.h"

class Engine: WindowContainer {
public:
	Engine (HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
	bool ProcessMessage();
	bool run();
	void Update();
	void RenderFrame();
private:
	Timer timer;
};