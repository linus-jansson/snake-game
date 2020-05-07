// #pragma once
#ifndef limpan_window_h
#define limpan_window_h

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <tuple>
#include <utility>
// #include <iostream>

#include <stdexcept>

namespace limpan
{
	class window {
	public:
		window(std::string title) : _title(title)
		{
			if (SDL_Init(SDL_INIT_VIDEO) != 0)
			{
				throw std::runtime_error("SDL failed to init\n");
			}

			SDL_DisplayMode DM;
			SDL_GetDesktopDisplayMode(0, &DM);	

			// Uint32 FLAGS = SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED;  

			
			_height = DM.h/2;
			// std::cout << _height << "\n";
			_width = DM.w/2;
			// std::cout << _width << "\n";

			// if ((_height == NULL || _height == 0) && (_width == NULL || _width == 0)) 
			// {
			// 	_height = 720;
			// 	_width = 1080;
			// }
			
			_window = SDL_CreateWindow(
				_title.c_str(),
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				_width, _height,
				0
			);

			if (_window == nullptr) {
				throw std::runtime_error("SDL failed to create window\n");
			}

			_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

			if (_renderer == nullptr) {
				throw std::runtime_error("SDL failed to create renderer\n");
			}

			
			
		}

		~window()
		{
			SDL_Delay(1);

			SDL_DestroyRenderer(_renderer);

			SDL_DestroyWindow(_window);

			SDL_Quit();
		}

		void setWindowBGcolor(int r, int g, int b, int a)
		{
			SDL_SetRenderDrawColor(_renderer, r, g, b, a);
			SDL_RenderClear(_renderer);
		}

		bool isClosed() const { return _closed; }
		void setClosed(bool closed) { _closed = closed;}

		int getImgHeight() const { return _imgHeight; }
		int getImgWidth() const { return _imgWidth; }
		int getWindowHeight() const { return _height; }
		int getWindowWidth() const { return _width; }

		// void setWinHeight(int & height)
		// {
		// 	_height = height;
		// }
		// void setWinWidth(int & width)
		// {
		// 	_width = width;
		// }

		SDL_Renderer* getRenderer() const
		{
			return _renderer;
		}

		SDL_Window* getWindow() {return _window; }



	private:

		std::string _title = "NOT SET";

		int _height;
		int _width;

		bool _closed = false;

		int _imgHeight = 76;
		int _imgWidth = 128;

		
		SDL_Window* _window = nullptr;

		SDL_Renderer* _renderer = nullptr;

	};
}

#endif