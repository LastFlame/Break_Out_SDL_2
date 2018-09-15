#include "stdafx.h"
#include "Break_Out.h"
#include "EngineUtility.h"
#include <random>

Break_Out::Break_Out()
{
	DEBUG_PRINT("Break out constructor called");
	m_ball_dir_y = 1;
	m_ball_dir_x = 0;
	m_IsGameStarted = false;

}



void Break_Out::Handle_Input(void)
{
	while (SDL_PollEvent(&input_event) > 0)
	{
		//quit the game
		if (input_event.type == SDL_QUIT)
		{
			Engine::m_is_running = false;

		}

		//handle player movement.
		switch (input_event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			if ((m_player->GetRect().x + m_player->GetRect().w) + 10 < m_window_widht)
				m_player->GetRect().x += 10;
			break;
		case SDLK_LEFT:
			if (m_player->GetRect().x + -10 > 0)
				m_player->GetRect().x -= 10;
			break;
		case SDLK_SPACE:
			if (!m_IsGameStarted)
			{
				m_IsGameStarted = true;
			}
			break;
		}

	}
}

void Break_Out::Game_Logic(void)
{
	if (m_IsGameStarted)
	{

		//check if the ball is over the vertical bounds,
		//and bounce it.
		if (m_ball->GetRect().x > 610 || m_ball->GetRect().x < 2)
		{
			m_ball_dir_x *= -1;
		}

		//check if the ball is over the horizontal bound
		//and bounce it.
		else if (m_ball->GetRect().y > 800 || m_ball->GetRect().y < 16)
		{
			m_ball_dir_y *= -1;
		}
		//check if the ball is under the player,
		//and restart the game.
		else if (m_ball->GetRect().y > m_player->GetRect().y)
		{
			std::cout << "GAME OVER!" << std::endl;

			m_IsGameStarted = false;
			Reset_Assets();
			Reset_Player();
			Reset_Ball();

			return;
		}

		m_ball->GetRect().y += m_ball_dir_y * BALL_SPEED;
		m_ball->GetRect().x -= m_ball_dir_x * BALL_SPEED;

		////temp check
		engine_utility::box_collision(&m_ball->GetRect(), &m_player->GetRect(), m_ball_dir_y, m_ball_dir_x);

		//check the collisions on every brick.
		for (unsigned x = 0; x < m_bricks.size(); x++)
		{
			for (unsigned y = 0; y < m_bricks[x].size(); y++)
			{
				if (m_bricks[x][y]->Get_Image() == NULL)
				{
					continue;
				}

				if (engine_utility::box_collision(&m_ball->GetRect(), &m_bricks[x][y]->GetRect(), m_ball_dir_y, m_ball_dir_x))
				{
					m_bricks[x][y]->Destroy();

				}
			}
		}

	}
}

void Break_Out::Init_Assets(void)
{
	//Temp screen format pointer.
	SDL_PixelFormat* m_screen_format = NULL;
	m_screen_format = m_ptr_screen->format;


	//Instantiate player sprite and paint it.
	m_player = std::make_unique<Sprite>();
	m_player->Init(SDL_MapRGB(m_screen_format, 255, 0, 0), m_window_widht / 2, m_window_height - 32, 64, 16);

	m_ball = std::make_unique<Sprite>();
	m_ball->Init(SDL_MapRGB(m_screen_format, 0, 255, 0), (m_window_widht / 2) + 16, m_window_height - 128, 16, 16);


	//Instantiate all the bricks and paint them.
	for (unsigned x = 0; x < ROW_COUNT; x++)
	{
		m_bricks.push_back(std::vector<std::shared_ptr<Sprite>>());

		for (unsigned y = 0; y < COLOUMN_COUNT; y++)
		{
			m_bricks[x].push_back(std::make_unique<Sprite>());
			m_bricks[x][y]->Init(SDL_MapRGB(m_screen_format, engine_utility::Random_Range(10, 255), engine_utility::Random_Range(10, 255), engine_utility::Random_Range(10, 255)), (x * 48), 16 + (y * 32), BRICK_W, BRICK_H);
		}
	}

	//Delete temp screen format.
	m_screen_format = NULL;
	delete m_screen_format;

}

void Break_Out::Render(void)
{
	//Background color.
	SDL_FillRect(m_ptr_screen, NULL, SDL_MapRGB(m_ptr_screen->format, 0, 0, 0));

	//Draw player on the screen.
	m_player->Draw(m_ptr_screen);

	//Draw all the brick on the screen.
	for (unsigned x = 0; x < m_bricks.size(); x++)
	{
		for (unsigned y = 0; y < m_bricks[x].size(); y++)
		{
			m_bricks[x][y]->Draw(m_ptr_screen);
		}
	}

	//Draw the ball on the screen.
	m_ball->Draw(m_ptr_screen);
}

void Break_Out::Reset_Assets(void)
{
	for (unsigned int x = 0; x < ROW_COUNT; x++)
	{
		for (unsigned int y = 0; y < COLOUMN_COUNT; y++)
		{
			if (m_bricks[x][y]->Get_Image() == NULL)
			{
				m_bricks[x][y]->Init(SDL_MapRGB(m_ptr_screen->format, engine_utility::Random_Range(10, 255), engine_utility::Random_Range(10, 255), engine_utility::Random_Range(10, 255)),
					m_bricks[x][y]->GetRect().x, m_bricks[x][y]->GetRect().y, BRICK_W, BRICK_H);
			}
		}
	}
}

void Break_Out::Reset_Player(void)
{
	m_player->GetRect().x = m_window_widht / 2;
	m_player->GetRect().y = m_window_height - 32;
}

void Break_Out::Reset_Ball(void)
{
	m_ball->GetRect().x = (m_window_widht / 2) + 16;
	m_ball->GetRect().y = m_window_height - 128;

	m_ball_dir_x = 0;
	m_ball_dir_y = 1;
}

Break_Out::~Break_Out()
{
	//Delete the player and clear the pointer.
	m_player->Destroy();

	//Delete all the brick sprites pointer from the memory.
	for (unsigned x = 0; x < m_bricks.size(); x++)
	{
		for (unsigned y = 0; y < m_bricks[x].size(); y++)
		{
			m_bricks[x][y]->Destroy();
		}
	}

	//Free memory and close all the subsystems.
	Kill_Sys();
}

