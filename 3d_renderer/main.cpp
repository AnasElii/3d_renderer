#include <iostream>
#include <SDL3/SDL.h>

namespace
{
	bool is_running = false;

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* color_buffer_texture = NULL;

	uint32_t* color_buffer = NULL;
}

#define active_display 3

static bool initialize_window(uint16_t* width, uint16_t* height) {
	if (!SDL_Init(SDL_INIT_VIDEO) || !SDL_Init(SDL_INIT_EVENTS)) {
		std::cerr << "Error initializing SDL.\n";
		return false;
	}

	// Get list of all displays
	int num_displays = 0;
	SDL_DisplayID* displays = SDL_GetDisplays(&num_displays);

	if (!displays || num_displays < active_display)
	{
		std::cerr << "Not enough displays! Found " << num_displays << "displays, need at least " << active_display << "\n";
		if (displays) SDL_free(displays);
		return false;
	}

	// Query the fullscreen width and height
	const SDL_DisplayMode* display_mode = SDL_GetCurrentDisplayMode(active_display);

	if (!display_mode)
	{
		std::cerr << "Query display failed!\n";
		return false;
	}

	std::cout << "Width: " << display_mode->w << "\nHeight: " << display_mode->h << "\nDisplay Refresh rate: " << display_mode->refresh_rate << "\n";

	*width = display_mode->w;
	*height = display_mode->h;

	// Get the bounds of the 2th display to position the window correctly
	SDL_Rect display_bounds;
	if (!SDL_GetDisplayBounds(active_display, &display_bounds))
	{
		std::cerr << "Failed to get display bounds from display 2!\n";
		return false;
	}

	std::cout << "active display w: " << display_bounds.w << ", h: " << display_bounds.h <<
		", x: " << display_bounds.x << ", y: " << display_bounds.y << "\n";

	window = SDL_CreateWindow(
		"3D Renderer",
		//display_mode->w,
		//display_mode->h,
		0,
		0,
		SDL_WINDOW_BORDERLESS
	);

	if (!window) {
		std::cerr << "Error creating window!\n";
		return false;
	}

	// Position the window on the secondary monitor
	if (!SDL_SetWindowPosition(window, display_bounds.x, display_bounds.y))
	{
		std::cerr << "Failed to position window on monitor " << active_display << "\n";
		// Continue this is not critical
	}

	renderer = SDL_CreateRenderer(
		window,
		NULL
	);
	if (!renderer) {
		std::cerr << "Error creating renderer!\n";
		return false;
	}

	SDL_SetWindowFullscreen(window, true);
	return true;
}

void setup(uint16_t width, uint16_t height) {
	color_buffer = new uint32_t[width * height];
	memset(color_buffer, 0, width * height * sizeof(uint32_t));

	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		width,
		height
	);
}

void process_input(const SDL_Event* event) {
	SDL_assert(event->type == SDL_EVENT_KEY_DOWN || event->type == SDL_EVENT_QUIT);

	switch (event->type) {
	case SDL_EVENT_KEY_DOWN:
		if (event->key.key == SDLK_W) {
			std::cout << "Move Forward\n";
		}
		else if (event->key.key == SDLK_S) {
			std::cout <<"Move Backward\n";
		}
		else if (event->key.key == SDLK_A) {
			std::cout <<"Move Left\n";
		}
		else if (event->key.key == SDLK_D) {
			std::cout <<"Move Right\n";
		}
		else if (event->key.key == SDLK_SPACE) {
			std::cout <<"Move Up\n";
		}
		else if (event->key.key == SDLK_LCTRL) {
			std::cout <<"Move Down\n";
		}
		break;
	}
}

void update() {


}

void render_color_buffer(uint16_t width)
{
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer,
		(sizeof(uint32_t) * width)
	);
	SDL_RenderTexture(renderer, color_buffer_texture, NULL, NULL);
}

namespace
{
	namespace exercise {
		// Exercise 01
		static void draw_grid(const int x, const int y, const uint16_t width, const uint16_t height, const uint32_t grid_color)
		{
			// Draw a 3x3 thick line
			int line_size = 20;
			for (int dy = 0; dy <= line_size; dy++)
			{
				for (int dx = 0; dx <= line_size; dx++)
				{
					int new_x = x + dx;
					int new_y = y + dy;

					if (new_x < width && new_y < height)
					{
						color_buffer[(width * new_y) + new_x] = grid_color;
					}
				}
			}
		}

		static void draw_rectangle( const int x, const int y, const uint16_t width, const uint16_t height, const uint32_t grid_color)
		{
			
		}
	}
}

void clear_color_buffer(uint16_t width, uint16_t height, uint32_t color)
{
	for (unsigned int y = 0; y < height; y++)
	{
		bool on_horizontal_line = (y % 120 == 0);
		for (unsigned int x = 0; x < width; x++)
		{
			bool on_vertical_line = (x % 120 == 0);

			if (on_vertical_line || on_horizontal_line)
			{
				uint32_t grid_color = 0xFFd4d4d4;
				exercise::draw_grid(x, y, width, height, grid_color);
				if ((x + 20) < width) {x += 20;}

			} else
			{
				color_buffer[(width * y) + x] = color;
			}

		}
		if ((y + 20) < height && on_horizontal_line) {y += 20;}
	}
}

void render(uint16_t width, uint16_t height) {
	SDL_SetRenderDrawColor(
		renderer,
		0,
		234,
		200,
		255
	);
	SDL_RenderClear(renderer);

	clear_color_buffer(width, height, 0xFF020202);
	render_color_buffer(width);

	SDL_RenderPresent(renderer);
}

void destroy_window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main() {
	uint16_t width;
	uint16_t height;

	is_running = initialize_window(&width, &height);

	setup(width, height);

	while (is_running)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_KEY_DOWN)
					if (e.key.key == SDLK_ESCAPE)
						is_running = false;
					else
						process_input(&e);
		}
		update();
		render(width, height);
	}

	destroy_window();

	std::cout <<"Hello Mother!\n";
	return 0;
}