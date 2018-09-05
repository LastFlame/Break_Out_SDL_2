#include "stdafx.h"
#include <assert.h>
#include "Sprite.h"


Sprite::Sprite()
{
}

void Sprite::Init(Uint32 color, unsigned x, unsigned y, unsigned w, unsigned h)
{
	m_img = NULL;

	m_img = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
	assert(m_img);

	SDL_FillRect(m_img, NULL, color);

	m_rect = m_img->clip_rect;
	m_x_origin = m_y_origin = 0;

	m_rect.x = x - m_x_origin;
	m_rect.y = y - m_y_origin;
}

Sprite::~Sprite()
{
	Sprite::Destroy();
}

void Sprite::Destroy(void)
{
	SDL_FreeSurface(m_img);
	m_img = NULL;
}

void Sprite::Draw(SDL_Surface* const dest_surf)
{
	SDL_BlitSurface(m_img, NULL, dest_surf, &m_rect);
}

const SDL_Surface* const Sprite::Get_Image(void) const
{
	return m_img;
}

std::pair<unsigned, unsigned> Sprite::GetOrigins(void) const
{
	return std::make_pair(m_x_origin, m_y_origin);

}

SDL_Rect& Sprite::GetRect(void)
{
	return m_rect;
}
