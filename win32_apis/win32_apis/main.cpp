#include <iostream>

#include "application.hpp"
#include "renderer.hpp"

class RuleEngine : public Application
{
	void Initialize() override
	{
		std::cout << "RuleEngine initialized!\n";
	}

	void Update(int inDeltaTime) override
	{

	}

	void Render(float inAspectRatio) override
	{
		// Use the Application's renderer, not our own
		Renderer* renderer = GetRenderer();
		if (!renderer)
		{
			std::cerr << "No renderer available in RuleEngine!\n";
			return;
		}

		renderer->ClearColorBuffer(0xFF020202);
		renderer->DrawGrid(0xFF333333);
		renderer->DrawRectangle(10, 10, 300, 150, 0xFF579e42);
	}

	void ShutDown() override
	{
		std::cout << "RuleEngine shutting down\n";
	}

	// Remove the private renderer - use Application's instead
};

#if _DEBUG
#pragma comment(linker, "/subsystem:console")

#ifdef _WIN32
#pragma comment(lib, "opengl32.lib")
#endif
int main()
{
	RuleEngine engine;
	engine.StartWindowed(0, 0, 100, 100, 0);
	return 0;
}
#else
#pragma comment(linker, "/subsystem:windows");
#endif
