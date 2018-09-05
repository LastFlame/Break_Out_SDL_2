#pragma once
#include "Engine.h"
#include "Sprite.h"
#include <vector>

class Break_Out : public Engine
{
public:
	Break_Out();
	~Break_Out();

protected:
	void Handle_Input(void) override;
	void Render(void) override;
	void Init_Assets(void) override;
	void Game_Logic(void) override;

private:
	void Reset_Assets(void);
	void Reset_Player(void);
	void Reset_Ball(void);

	std::unique_ptr<Sprite> m_player;
	std::unique_ptr<Sprite> m_ball;
	std::vector<std::vector<std::shared_ptr<Sprite>>>  m_bricks;

	int m_ball_dir_y;
	int m_ball_dir_x;

	unsigned const BALL_SPEED = 5;
	unsigned const ROW_COUNT = 13;
	unsigned const COLOUMN_COUNT = 6;
	unsigned const BRICK_W = 32;
	unsigned const BRICK_H = 16;

	bool m_IsGameStarted;
};