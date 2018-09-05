#include "stdafx.h"
#include "Engine.h"
#include <assert.h>


const int MAX_FRAME_RATE = 60;
const int FPS_DIVISION = 1000 / MAX_FRAME_RATE;



Engine::Engine()
{
	Engine::m_ptr_window = NULL;
	Engine::m_ptr_screen = NULL;
	//Engine::m_ptr_font = NULL;

	Engine::m_is_running = true;
	Engine::m_font_sys_init = false;

	Engine::m_window_widht = 0;
	Engine::m_window_height = 0;

	DEBUG_PRINT("Engine constructor called");
}

Engine::~Engine()
{
	Engine::Kill_Sys();
	DEBUG_PRINT("Engine distructor called");
}

//Initialize all the SDL subsystems. Assert if fails.
void Engine::Init_Sys(void)
{
	//init SDL library.
	assert(SDL_Init(SDL_INIT_VIDEO) >= 0);

	//init text library.
	//assert(TTF_Init() >= 0);

}

//Create a window with the given params. Assert if it fails.
void Engine::Init_Window(const char * name, unsigned x, unsigned y, unsigned w, unsigned h, Uint32 flags)
{
	//Create a window and assert if SDL fails to create it.
	Engine::m_ptr_window = SDL_CreateWindow(name, x, y, w, h, flags);
	assert(Engine::m_ptr_window);

	//Get the window surface and assert if SDL fails.
	m_ptr_screen = SDL_GetWindowSurface(Engine::m_ptr_window);
	assert(Engine::m_ptr_screen);

	Engine::m_window_widht = w;
	Engine::m_window_height = h;
}

//Get the window reference in memory.
const SDL_Window* const Engine::Get_Window(void) const
{
	return Engine::m_ptr_window;
}

//Get the screen surface reference in memory.
SDL_Surface* const Engine::Get_Screen(void) const
{
	return Engine::m_ptr_screen;
}

const std::pair<unsigned, unsigned> Engine::Get_Window_Size() const
{
	 return std::make_pair(m_window_widht, m_window_height);
}

//Initialize the font subsystem. Assert if fails.
//void Engine::Init_Font(const char* font_path, unsigned font_size)
//{
//	Engine::m_ptr_font = TTF_OpenFont(font_path, font_size);
//	assert(Engine::m_ptr_font);
//
//	Engine::m_font_sys_init = true;
//}

//Main loop of the game.
void Engine::Start_Game(void)
{
	Init_Assets();

	Uint32 fps_ticks = 0;
	unsigned counted_fps = 0;

	while (m_is_running)
	{
		fps_ticks = SDL_GetTicks();
		unsigned avg_fps = counted_fps / (SDL_GetTicks() / 1000.f);

		Handle_Input();
		Game_Logic();
		
		Render();
		Engine::Update_Window();

		++counted_fps;
		Engine::VSync(fps_ticks);
	}
}

void Engine::Game_Logic(void)
{
	DEBUG_PRINT("Game logic empty\n");
}

void Engine::Init_Assets(void)
{
	DEBUG_PRINT("init assets empty");
}

void Engine::Render(void)
{
	//change when heredit from this.
	DEBUG_PRINT("Called empty render");
}

void Engine::Handle_Input(void)
{
	//change when heredit from this.
	DEBUG_PRINT("Called empty Handle input");
}

//update the window surface to refresh and paint everything on the screen.
void Engine::Update_Window() const
{
	SDL_UpdateWindowSurface(m_ptr_window);
}


//Limit the game frame rate.
void Engine::VSync(Uint32 starting_tick)
{
	int end_ticks = SDL_GetTicks() - starting_tick;
	if (end_ticks < FPS_DIVISION)
	{
		//Wait remaining time 
		SDL_Delay(FPS_DIVISION - end_ticks);
	}
}


//Clear all the pointers and close all the subsystems.
void Engine::Kill_Sys()
{
	SDL_DestroyWindow(m_ptr_window);
	m_ptr_window = NULL;

	SDL_FreeSurface(m_ptr_screen);
	m_ptr_screen = NULL;

	//if (m_font_sys_init)
	//{
	//	TTF_CloseFont(m_ptr_font);
	//	m_ptr_font = NULL;
	//	TTF_Quit();
	//}

	SDL_Quit();

}
