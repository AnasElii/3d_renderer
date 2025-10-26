#pragma once

#include "iplatform_adapter.hpp"
#include "renderer.hpp"

class Application
{
public:
	Application();
	virtual ~Application();

public:
	virtual void Initialize() {}
	virtual void Update(int inDeltaTime) {}
	virtual void Render(float inAspectRatio) {}
	virtual void ShutDown() {}

public:
	void StartWindowed(int x, int y, int width, int height, int antialiasing);
	void finish();

public:
	Renderer* GetRenderer() { return m_renderer; }

private:
	IPlatformAdapter* m_platform_adapter;
	Renderer* m_renderer;

#ifdef _WIN32 // Allow WindowsAdapter to call SetupRe
	friend class WindowsAdapter;
#endif
	void SetupRenderer(uint32_t* color_buffer, int width, int height);

};
