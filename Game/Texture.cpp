#include "stdafx.h"
#include "Texture.h"
//#include "SDL_image.h"


Texture::Texture()
{
	m_ptr_texture = nullptr;
	m_width = 0;
	m_height = 0;
}


Texture::~Texture()
{
	free();
}

bool Texture::load_from_files(const char* path, SDL_Renderer* const renderer)
{
	////get rid of the preexisting texture if is present
	//free();

	////final texture
	//SDL_Texture*  l_ptr_final_texutre = nullptr;

	////load at specific path
	//SDL_Surface* l_ptr_loaded_surface = IMG_Load(path);

	//if (l_ptr_loaded_surface == nullptr)
	//{
	//	printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	//}
	//else
	//{
	//	//color key image, color cyan 
	//	SDL_SetColorKey(l_ptr_loaded_surface, SDL_TRUE, SDL_MapRGB(l_ptr_loaded_surface->format, 0, 0xFF, 0xFF));

	//	//create texture from the surface pixels
	//	l_ptr_final_texutre = SDL_CreateTextureFromSurface(renderer, l_ptr_loaded_surface);

	//	if (l_ptr_final_texutre == nullptr)
	//	{
	//		printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
	//	}
	//	else
	//	{
	//		//get image dimension
	//		m_width = l_ptr_loaded_surface->w;
	//		m_height = l_ptr_loaded_surface->h;
	//	}

	//	//free loaded surface
	//	SDL_FreeSurface(l_ptr_loaded_surface);
	//}

	//m_ptr_texture = l_ptr_final_texutre;
	//return m_ptr_texture != nullptr;
	return NULL;
}

void Texture::free()
{
	//clear texture if exist
	if (m_ptr_texture != nullptr)
	{
		SDL_DestroyTexture(m_ptr_texture);
		m_ptr_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}

void Texture::render(Uint32 x, Uint32 y, SDL_Renderer* ptr_renderer, SDL_Rect* ptr_rect = nullptr)
{
	//set rendering space and render to screen
	SDL_Rect render_quad = { x , y, m_width, m_height };

	if (ptr_rect != nullptr)
	{
		render_quad.w = ptr_rect->w;
		render_quad.h = ptr_rect->h;
	}
	SDL_RenderCopy(ptr_renderer, m_ptr_texture, nullptr, &render_quad);
}

void Texture::set_blend(SDL_BlendMode blend_mode)
{
	SDL_SetTextureBlendMode(m_ptr_texture, blend_mode);
}

void Texture::set_alpha(Uint8 alpha)
{
	//set texture alpha
	SDL_SetTextureAlphaMod(m_ptr_texture, alpha);
}

const int Texture::get_width() const
{
	return m_width;
}

const int Texture::get_height() const
{
	return m_height;
}
