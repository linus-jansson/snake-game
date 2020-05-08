#include "window.h"

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

#include "rect.h"

/*
Controls: wasd or arrow keys to move snake arround. Space to make it stop if DEBUG option is on in inputEvents


TODO:
	- Get Eat food to work <-- done
		- Grow onto snake making it larger
	- Lägg till rörelse regler


	- Inherita nödvändiga grejer i rect classen

	- Gör spelbrädan mindre var 10 gång ormen äter mat

	- Lägg till så att rect classen centrerar objecten på rendern


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

void inputEvents(limpan::window &frame, SDL_Event &event, char &direction)
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

				direction = 'l';
				break;
			case SDLK_RIGHT:
			case SDLK_d:

				direction = 'r';
				break;
			case SDLK_UP:
			case SDLK_w:

				direction = 'u';
				break;
			case SDLK_DOWN:
			case SDLK_s:

				direction = 'd';
				break;

			// DEBUG
			case SDLK_SPACE:
				direction = 's';
				break;
			default:
				// frame.setClosed(true);
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

void moveSnake(char &dir, std::tuple<int, int> pos, limpan::rect &snake, int size, int speed)
{

	/* Check Tail vector and move position back one spot*/
	switch (dir)
	{
	case 'r':
		snake.changeRect(std::get<0>(pos) += speed, std::get<1>(pos), size, size);
		break;
	case 'l':
		snake.changeRect(std::get<0>(pos) -= speed, std::get<1>(pos), size, size);
		break;
	case 'u':
		snake.changeRect(std::get<0>(pos), std::get<1>(pos) -= speed, size, size);
		break;
	case 'd':
		snake.changeRect(std::get<0>(pos), std::get<1>(pos) += speed, size, size);
		break;
	case 's':
		snake.changeRect(std::get<0>(pos), std::get<1>(pos), 40, 40);
		break;
	default:
		break;
	}
}

// If head touches food call this function and add one to the vector(tail)
void addToTail();



int main()
{
	const int size = 20;
	const int speed = 2;

	limpan::random r;
	limpan::window frame("Snake game");

	limpan::rect snake(&frame, r.GetUniformInt<int>(0, frame.getWindowWidth() - size), r.GetUniformInt<int>(0, frame.getWindowHeight() - size), 20);
	limpan::rect food(&frame, r.GetUniformInt<int>(0, frame.getWindowWidth() - size), r.GetUniformInt<int>(0, frame.getWindowHeight() - size), 20);

	SDL_Event event;

	std::vector<std::tuple<int, int>> tail;

	int snakePosHashed, snakePosHashedCopy;

	// std::cout << PosHased << "\n" << PosHasedCopy << std::endl;
	char Dir;

	std::tuple<int, int, int, int> snakeColor(255, 255, 255, 255);
	std::tuple<int, int, int, int> foodColor(0, 255, 0, 255);

	int foodCount = 1;

	while (!frame.isClosed())
	{
		// Check for events

		inputEvents(frame, event, Dir);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		moveSnake(Dir, snake.getPosition(), snake, size, speed);

		// Hash position current position
		snakePosHashed = hash(snake.getPosition());

		if (snakePosHashed != snakePosHashedCopy) // Check if snakepos, or food differ. otherwise dont update screen
		{

			// Set the background color to black
			frame.setWindowBGcolor(0, 0, 0, 255);

			snake.renderRect(snakeColor);
			food.renderRect(foodColor);
		}

		// Check if food and head of snake is on the same
		if (rectOverlap(snake.getPosition(), food.getPosition(), size, size)) // NOT WORKING
		{

			food.changeRect(r.GetUniformInt<int>(0, frame.getWindowWidth() - size), r.GetUniformInt<int>(0, frame.getWindowHeight() - size), size, size);

			// Debug: Will return True if rectOverlap() is true. and will return the new position of the food
			// std::cout << true << "\n";
			// std::cout << std::get<0>(food.getPosition()) << " " << std::get<1>(food.getPosition()) << "\n";

			// Add one to snake tail
			std::cout << foodCount++ << "\n";
		}

		// BORDER CONTROL
		if (std::get<0>(snake.getPosition()) + size >= frame.getWindowWidth())
		{
			snake.setPosition(frame.getWindowWidth() - size, std::get<1>(snake.getPosition()));

			// frame.setClosed(true);
		}
		else if (std::get<0>(snake.getPosition()) <= 0)
		{

			snake.setPosition(0, std::get<1>(snake.getPosition()));

			// frame.setClosed(true);
		}
		else if (std::get<1>(snake.getPosition()) + size >= frame.getWindowHeight())
		{
			snake.setPosition(std::get<0>(snake.getPosition()), frame.getWindowHeight() - size);

			// frame.setClosed(true);
		}
		else if (std::get<1>(snake.getPosition()) <= 0)
		{
			snake.setPosition(std::get<0>(snake.getPosition()), 0);

			// frame.setClosed(true);
		}

		// make copy of current hashed position
		snakePosHashedCopy = snakePosHashed;
	}
}