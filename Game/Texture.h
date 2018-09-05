#pragma once
#include <SDL.h>


class Texture
{
public:

	//init variables
	Texture();

	//free memory
	~Texture();

	//load images at path
	bool load_from_files(const char* path, SDL_Renderer* const renderer);

	//free texture
	void free();

	//render texture at given point
	void render(Uint32 x, Uint32 y, SDL_Renderer* const ptr_renderer, SDL_Rect* ptr_rect);

	//set bled mode of the texture
	void set_blend(SDL_BlendMode blend);

	//set the alpha color of the texture
	void set_alpha(Uint8 alpha);

	//get image dimensions
	const int get_width() const;
	const int get_height() const;

private:

	//the actual hardware texture
	SDL_Texture* m_ptr_texture;

	//image dimensions
	Uint32 m_width;
	Uint32 m_height;

};

