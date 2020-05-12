#include <chrono>
#include <thread>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <tuple>
#include <cmath>
#include <functional>
#include <vector>

#include "limpanLibs/lib/random.h"

#include "window.h"
#include "rect.h"
#include "snake.h"
#include "food.h"

/*
Controls: wasd or arrow keys to move snake arround. Space to make it stop if DEBUG option is on in inputEvents


TODO:
	- Get Eat food to work <-- done
		- Grow onto snake making it larger
	- Lägg till rörelse regler


	- Inherita nödvändiga grejer i rect classen

	- Gör spelbrädan mindre var 10 gång ormen äter mat

	- Lägg till så att rect classen centrerar objecten på rendern

	- set Default DIR till STOP


Bug:
	- Om man går till hörnet av spelplanen och försöker gå ut så kan man göra det
		- Tror man måste kolla ifall den är i ett hörn och göra xPos och yPos velocity till 0
*/

std::size_t hash(std::tuple<int, int> pos)
{
	std::size_t h1 = std::hash<int>{}(std::get<0>(pos));
	std::size_t h2 = std::hash<int>{}(std::get<1>(pos));
	return h1 ^ (h2 << 1); // or use boost::hash_combine
}

/*

	Check if food and snake head touch

	int snakeXLeft = std::get<0>(snakePosition)
	int snakeXRight = std::get<0>(snakePosition) + size

	int snakeYUp = std::get<1>(snakePosition)
	int snakeYDown = std::get<1>(snakePosition) + size

	snakeXLeft <= foodXRight || snakeXLeft >= foodXLeft
	snakeXRight <= foodXRight || snakeXRight >= foodXLeft

	snakeYUp <= foodYRight || snakeYLeft >= foodYLeft
	snakeYRight <= foodYRight || snakeYRight >= foodYLeft
		
*/

bool valueInRange(int value, int min, int max)
{
	return (value >= min) && (value <= max);
}

bool rectOverlap(std::tuple<int, int> snakePos, std::tuple<int, int> foodPos, int foodSize, int snakeSize)
{
	bool xOverlap = valueInRange(std::get<0>(snakePos), std::get<0>(foodPos), std::get<0>(foodPos) + foodSize) ||
					valueInRange(std::get<0>(foodPos), std::get<0>(snakePos), std::get<0>(snakePos) + snakeSize);

	bool yOverlap = valueInRange(std::get<1>(snakePos), std::get<1>(foodPos), std::get<1>(foodPos) + foodSize) ||
					valueInRange(std::get<1>(foodPos), std::get<1>(snakePos), std::get<1>(snakePos) + snakeSize);

	return xOverlap && yOverlap;
}

void inputEvents(limpan::window &frame, SDL_Event &event, limpan::Snake::DIRECTION &direction)
{

	auto windowID = SDL_GetWindowID(frame.getWindow());
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			frame.setClosed(true);
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_q:
			case SDLK_ESCAPE:
				frame.setClosed(true);
				break;
			case SDLK_LEFT:
			case SDLK_a:

				if (direction != limpan::Snake::RIGHT)
					direction = limpan::Snake::LEFT;
				break;

			case SDLK_RIGHT:
			case SDLK_d:

				if (direction != limpan::Snake::LEFT)
					direction = limpan::Snake::RIGHT;
				break;

			case SDLK_UP:
			case SDLK_w:

				if (direction != limpan::Snake::DOWN)
					direction = limpan::Snake::UP;
				break;

			case SDLK_DOWN:
			case SDLK_s:

				if (direction != limpan::Snake::UP)
					direction = limpan::Snake::DOWN;
				break;

			// DEBUG
			case SDLK_SPACE:

				direction = limpan::Snake::STOP;
				break;
			}
			break;

		case SDL_WINDOWEVENT:
			break;
		default:
			break;
		}
	}
}

int main()
{
	limpan::random r;
	limpan::window frame("Snake game");

	limpan::Snake snake(&frame);
	limpan::Food food(&frame);

	// limpan::rect food(&frame, r.GetUniformInt<int>(0, frame.getWindowWidth() - 20), r.GetUniformInt<int>(0, frame.getWindowHeight() - 20), 20, 20, {0, 255, 0, 255});

	int snakeHeadWidth = snake.getHeadHeight();
	int snakeHeadHeight = snake.getHeadWidth();

	int foodWidth = 20;
	int foodHeight = 20;

	// std::tuple<int, int, int, int> snakeColor(255, 255, 255, 255);

	// limpan::rect snake(&frame, r.GetUniformInt<int>(0, frame.getWindowWidth() - size), r.GetUniformInt<int>(0, frame.getWindowHeight() - size), 20, snakeColor);

	SDL_Event event;

	std::vector<std::tuple<int, int>> tail;

	int snakePosHashed, snakePosHashedCopy;

	limpan::Snake::DIRECTION DIR = limpan::Snake::DIRECTION::STOP;
	food.move();
	while (!frame.isClosed())
	{

		// Check for events

		inputEvents(frame, event, DIR);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		snake.move(DIR);

		// moveSnake(Dir, snake.getPosition(), snake, size, speed);

		// Hash position current position
		snakePosHashed = hash(snake.getPosition());

		if (snakePosHashed != snakePosHashedCopy) // Check if snakepos, or food differ. otherwise dont update screen
		{

			// Set the background color to black
			frame.setWindowBGcolor(0, 0, 0, 255);

			food.render();
			snake.render();
		}

		// // Check if food and head of snake is on the same
		if (rectOverlap(snake.getPosition(), food.getPosition(), 20, 20))
		{

			food.move();

			// Add one to snake tail
			snake.grow();
		}

		// // BORDER CONTROL

		if (std::get<0>(snake.getPosition()) + snakeHeadWidth >= frame.getWindowWidth()) // RIGHT
		{
			snake.setPosition(frame.getWindowWidth() - snakeHeadWidth, std::get<1>(snake.getPosition()));
			// std::cout << "1\n";
			DIR = limpan::Snake::DIRECTION::LEFT;
			// frame.setClosed(true);
		}
		else if (std::get<0>(snake.getPosition()) <= 0) // LEFT
		{

			snake.setPosition(0, std::get<1>(snake.getPosition()));

			DIR = limpan::Snake::DIRECTION::RIGHT;
			// std::cout << "2\n";
			// frame.setClosed(true);
		}
		else if (std::get<1>(snake.getPosition()) + snakeHeadHeight >= frame.getWindowHeight()) // DOWN
		{
			snake.setPosition(std::get<0>(snake.getPosition()), frame.getWindowHeight() - snakeHeadHeight);
			DIR = limpan::Snake::DIRECTION::UP;
			// std::cout << "3\n";
			// frame.setClosed(true);
		}
		else if (std::get<1>(snake.getPosition()) <= 0) // UP
		{
			snake.setPosition(std::get<0>(snake.getPosition()), 0);
			DIR = limpan::Snake::DIRECTION::DOWN; // Sets the direction of the snake to its direction but reversed
												  // std::cout << "4\n";
												  // frame.setClosed(true);
		}

		// make copy of current hashed position
		snakePosHashedCopy = snakePosHashed;
	}
}