#ifndef LIMPAN_RECT_H
#define LIMPAN_RECT_H

#include "window.h"
#include <tuple>
namespace limpan
{
  class rect
  {
    public:
      /* Include window when creating object so you can fetch rendrer*/
      rect(limpan::window* win) 
          : _renderer(win->getRenderer())
      {

      }
      ~rect()
      {

      }


      void renderRect(std::tuple<int, int, int, int> & RGBA)
      {
        	SDL_SetRenderDrawColor(_renderer, std::get<0>(RGBA), std::get<1>(RGBA), std::get<2>(RGBA), std::get<3>(RGBA));
          SDL_RenderFillRect(_renderer, &_rect);
          SDL_RenderPresent(_renderer);
      }
    
      /* This method is used to change the properties of the rectangle*/
      void changeRect(int x, int y, int w, int h) { _rect = {x, y, w, h}; }
      
      std::tuple<int, int> getPosition() { return _position; }


    private:  
      int _xPos = 0;
      int _yPos = 0;

      int _width = 20;
      int _height = 20;

      std::tuple<int, int> _position = {_xPos, _yPos};

      SDL_Renderer * _renderer;
      SDL_Rect _rect = {std::get<0>(_position), std::get<1>(_position), _width, _height};
  };
}

#endif
