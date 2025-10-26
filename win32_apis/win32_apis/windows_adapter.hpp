#pragma once
#include <vector>

#include "application.hpp"
#include "iplatform_adapter.hpp"

#ifdef _WIN32

#include <windows.h>

class WindowsAdapter : public IPlatformAdapter
{
public:
	struct MonitorInfo
	{
		HMONITOR hMonitor;
		RECT rect;
		int index;
	};

public:
	WindowsAdapter();
	~WindowsAdapter();

public:
	void StartWindowed(int x, int y, unsigned int w, unsigned int h, int antialiasing, Application& app, int nCmdShow = 1) override;
	void finish(Application& app) override;

	void InitializePixelBuffer(HDC hdc);
	void PresentPixelBuffer(HDC hdc);
	void CleanupPixelBuffer();

	RECT GetMonitorRect(int monitorIndex);
	int GetMonitorCount();

	unsigned long getTime();

	static WindowsAdapter& GetInstance();

private:
	static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	// Member variables
	HINSTANCE m_instance;
	HWND m_hWnd;
	HDC m_hdc;

private:
	uint32_t* m_color_buffer;
	HBITMAP m_bitmap = nullptr;
	HDC m_memory_dc = nullptr;
	int m_buffer_width = 0;
	int m_buffer_height = 0;
	unsigned long m_time = 0;

private:
	static std::vector<MonitorInfo> m_monitors;
	uint8_t m_monitor_count;
	LONG m_monitor_width;
	LONG m_monitor_height;

	Application* m_application = nullptr;

};

#endif