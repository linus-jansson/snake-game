#include "window.h"

#include <chrono>
#include <thread>
// #include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "limpanLibs/lib/random.h"

#include <cmath>


void inputEvents(limpan::window & frame, SDL_Event & event)
{
	
	auto windowID = SDL_GetWindowID(frame.getWindow());
	if (SDL_PollEvent(&event)) {
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
					std::cout << "left\n"; 
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					std::cout << "right\n"; 
					break;
				case SDLK_UP:
				case SDLK_w:
					std::cout << "up\n"; 
					break;
				case SDLK_DOWN:
				case SDLK_s:
					std::cout << "down\n"; 
					break;
				default:
					// frame.setClosed(true);
					break;
			}
			break;

		case SDL_WINDOWEVENT:  
			// if (event.window.windowID == windowID)  {
			// 	switch (event.window.event)  
			// 	{
			// 		case SDL_WINDOWEVENT_RESIZED:
			// 		case SDL_WINDOWEVENT_SIZE_CHANGED:
			// 			// std::cout << "size changed to " << event.window.data1 << "x" << event.window.data2 << std::endl;
			// 			frame.setWinWidth(event.window.data1);
			// 			frame.setWinHeight(event.window.data2);
			// 			// SDL_SetWindowSize(_window, _width, _height);
			// 			break;
			// 	}
			// }
		break;
		default:
			break;
		}
	}
}

void updateSnake(SDL_Renderer* _renderer, SDL_Rect & rect)
{

	// auto r = std::get<0>(color);
	// auto g = std::get<1>(color);
	// auto b = std::get<2>(color);
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(_renderer, &rect);
	SDL_RenderPresent(_renderer);

}
int main()
{		
	limpan::random r;
	limpan::window frame("Snake game");

	SDL_Event event;

	int xPos = r.GetUniformInt<int>(0, frame.getWindowWidth());
	int yPos = r.GetUniformInt<int>(0, frame.getWindowHeight());

	SDL_Rect head = { xPos, yPos, 40, 40 };

	while (!frame.isClosed())
	{	

		head = { r.GetUniformInt<int>(0, frame.getWindowWidth()),  r.GetUniformInt<int>(0, frame.getWindowHeight()), 40, 40 };
		// Check for events
		inputEvents(frame, event);
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		updateSnake(frame.getRenderer(), head);

		// Set the background color to black
		frame.setWindowBGcolor(0, 0, 0, 255);	
	}


}