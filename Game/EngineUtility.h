#pragma once
#include <SDL.h>
#include <string>
#include <random>

namespace engine_utility
{
	bool box_collision(SDL_Rect* const a, SDL_Rect* const b, int &ball_y_dir, int &ball_x_dir)
	{
		//sides of the rectangles declaration
		uint16_t right_a, right_b;
		uint16_t top_a, top_b;
		uint16_t left_a, left_b;
		uint16_t bottom_a, bottom_b;

		//get the center of the images.
		const uint16_t h_center_b = ((b->h / 2) + b->y);
		const uint16_t h_center_a = ((a->h / 2) + a->y);

		const uint16_t w_center_b = ((b->w / 2) + b->x);
		const uint16_t w_center_a = ((a->w / 2) + a->x);

		//set the standard offset from the center of the images.
		const uint16_t b_center_offset = 5;


		//get A sides
		left_a = a->x;
		top_a = a->y;
		right_a = a->w + a->x;
		bottom_a = a->y + a->h;

		//get B sides
		left_b = b->x;
		top_b = b->y;
		right_b = b->w + b->x;
		bottom_b = b->y + b->h;


		//y collisions
		if (bottom_a <= top_b)
		{
			return false;
		}

		if (top_a >= bottom_b)
		{
			return false;
		}


		//x collisions
		if (right_a <= left_b)
		{
			return false;
		}

		if (left_a >= right_b)
		{
			return false;
		}

		std::string c_angle = "no coll";

		///     10.6
		/// -l- -c- -r


		//collision point detection.
		if (h_center_a < h_center_b) //top case.
		{
			c_angle = "top";
			ball_y_dir *= -1;

			if (w_center_a > w_center_b + b_center_offset) //right case
			{
				c_angle += " right";
				ball_x_dir = -1;
			}
			else if (w_center_a < w_center_b - b_center_offset)
			{
				c_angle += " left";
				ball_x_dir = 1;
			}
			else
			{
				c_angle += " center";
				ball_x_dir = 0;
			}

		}
		else if (h_center_a > h_center_b) //down case.
		{
			c_angle = "down";

			ball_y_dir *= -1;

			if (w_center_a > w_center_b + b_center_offset) //right case
			{
				c_angle += " right";
				ball_x_dir = -1;
			}
			else if (w_center_a < w_center_b - b_center_offset)
			{
				c_angle += " left";
				ball_x_dir = 1;
			}
			else
			{
				c_angle += " center";
				ball_x_dir = 0;
			}

		}

		return true;

	}

	int Random_Range(int min, int max)
	{
		std::random_device seeder;
		std::mt19937 engine(seeder());
		std::uniform_int_distribution<int> random_n(min, max);
		return random_n(engine);
	}

	struct v2
	{
		int x;
		int y;
	};
}