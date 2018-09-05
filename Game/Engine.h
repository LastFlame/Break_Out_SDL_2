#pragma once

#include "SDL.h"
//#include "SDL_ttf.h"
#include <iostream>

static bool print_debug = true;
#define DEBUG_PRINT(str) if(print_debug) std::cout<< str << std::endl

class Engine
{
protected:

	SDL_Window * m_ptr_window;
	SDL_Surface* m_ptr_screen;

	//TTF_Font* m_ptr_font;
	SDL_Event input_event;

	bool m_is_running;
	bool m_font_sys_init;

	unsigned m_window_widht;
	unsigned m_window_height;

public:
	void Init_Sys(void);
	void Init_Window(const char * name, unsigned x = SDL_WINDOWPOS_UNDEFINED, unsigned y = SDL_WINDOWPOS_UNDEFINED, unsigned w = 600, unsigned h = 400, Uint32 flags = NULL);
	/*void Init_Font(const char* font_path, unsigned font_size);*/
	

	void Start_Game(void);

	const SDL_Window* const Get_Window(void) const;
	SDL_Surface* const Get_Screen(void) const;

    const std::pair<unsigned, unsigned> Get_Window_Size() const;
	
protected:
	Engine();
	~Engine();


	void virtual Game_Logic(void) = 0;
	void virtual Handle_Input(void) = 0;
	void virtual Init_Assets(void) = 0;
	void virtual Render(void) = 0;

	void Update_Window() const;
	void VSync(Uint32 starting_tick);
	void Kill_Sys();
};

