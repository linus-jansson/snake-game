#include "window.h"

#include <chrono>
#include <thread>
// #include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <tuple>

#include "limpanLibs/lib/random.h"

#include <cmath>

#include <functional>

#include <vector>

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

std::size_t hash(std::tuple<int, int> &pos)
{
	std::size_t h1 = std::hash<int>{}(std::get<0>(pos));
	std::size_t h2 = std::hash<int>{}(std::get<1>(pos));
	return h1 ^ (h2 << 1); // or use boost::hash_combine
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

void moveSnake(char &dir, std::tuple<int, int> &pos, SDL_Rect &head, int size)
{

	/* Check Tail vector and move position back one spot*/
	switch (dir)
	{
	case 'r':
		head = {std::get<0>(pos)++, std::get<1>(pos), size, size};
		break;
	case 'l':
		head = {std::get<0>(pos)--, std::get<1>(pos), size, size};
		break;
	case 'u':
		head = {std::get<0>(pos), std::get<1>(pos)--, size, size};
		break;
	case 'd':
		head = {std::get<0>(pos), std::get<1>(pos)++, size, size};
		break;
	case 's':
		head = {std::get<0>(pos), std::get<1>(pos), 40, 40};
		break;
	default:
		break;
	}
}

void moveFood();

// If head touches food call this function and add one to the vector(tail)
void addToTail();  

void renderFood(SDL_Renderer *_renderer, SDL_Rect &food)
{

	SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(_renderer, &food);
	SDL_RenderPresent(_renderer);
}

void renderSnake(SDL_Renderer *_renderer, SDL_Rect &rect)
{

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(_renderer, &rect);
	SDL_RenderPresent(_renderer);
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

int main()
{
	limpan::random r;
	limpan::window frame("Snake game");

	SDL_Event event;

	int xPos = r.GetUniformInt<int>(0, frame.getWindowWidth());
	int yPos = r.GetUniformInt<int>(0, frame.getWindowHeight());

	int foodxPos = r.GetUniformInt<int>(0, frame.getWindowWidth());
	int foodyPos = r.GetUniformInt<int>(0, frame.getWindowHeight());

	const int size = 20;

	std::tuple<int, int> snakePosition(xPos, yPos);
	std::tuple<int, int> foodPosition(foodxPos, foodyPos);

	SDL_Rect head = {xPos, yPos, size, size};
	SDL_Rect food = {foodxPos, foodyPos, size, size};

	std::vector<std::tuple<int, int>> tail;

	int snakePosHashed, snakePosHashedCopy;

	// std::cout << PosHased << "\n" << PosHasedCopy << std::endl;
	char Dir;



	while (!frame.isClosed())
	{
		// Check for events

		inputEvents(frame, event, Dir);
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		renderSnake(frame.getRenderer(), head);
		renderFood(frame.getRenderer(), food);
		moveSnake(Dir, snakePosition, head, size);

		// Hash position current position
		snakePosHashed = hash(snakePosition);

		if (snakePosHashed != snakePosHashedCopy) // Check if hash differ, If they do update window
		{	

			// Set the background color to black
			frame.setWindowBGcolor(0, 0, 0, 255);
		}

		// Check if food and head of snake is on the same
		if (rectOverlap(snakePosition, foodPosition, size, size))
		{
			

			std::get<0>(foodPosition) = r.GetUniformInt<int>(0, frame.getWindowWidth());
			std::get<1>(foodPosition) = r.GetUniformInt<int>(0, frame.getWindowHeight());
			food = {std::get<0>(foodPosition), std::get<1>(foodPosition), size, size};
			
			// Debug
			std::cout << true << "\n";
			std::cout << std::get<0>(foodPosition) << " " << std::get<1>(foodPosition) << "\n";

			
			// Add one to snake
		}

		// BORDER CONTROL
		if (std::get<0>(snakePosition) + size >= frame.getWindowWidth())
		{
			std::get<0>(snakePosition) = frame.getWindowWidth() - size;
			frame.setClosed(true);
		}
		else if (std::get<0>(snakePosition) <= 0)
		{
			std::get<0>(snakePosition) = 0;
			frame.setClosed(true);
		}
		else if (std::get<1>(snakePosition) + size >= frame.getWindowHeight())
		{
			std::get<1>(snakePosition) = frame.getWindowHeight() - size;
			frame.setClosed(true);
		}
		else if (std::get<1>(snakePosition) <= 0)
		{
			std::get<1>(snakePosition) = 0;
			frame.setClosed(true);
		}

		// make copy of current hashed position
		snakePosHashedCopy = snakePosHashed;
	}
}