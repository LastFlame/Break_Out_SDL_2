#pragma once
#include <SDL.h>
#include <utility>

///////////
class Sprite
{
public:
	Sprite();
	~Sprite();
	void Init(Uint32 color, unsigned x, unsigned y, unsigned w, unsigned h);
	void Destroy(void);
	void Draw(SDL_Surface* const dest_surf);
	const SDL_Surface* const Get_Image(void)const;
	std::pair<unsigned, unsigned> GetOrigins(void) const;
	SDL_Rect& GetRect(void);

private:
	unsigned m_y_origin;
	unsigned m_x_origin;
	SDL_Surface* m_img;
	SDL_Rect m_rect;

};

