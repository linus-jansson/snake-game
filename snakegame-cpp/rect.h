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
    rect(limpan::window *win, int defaultxPos, int defaultyPos, int width, int height, std::tuple<int, int, int, int> _rectColor)
        : _renderer(win->getRenderer()),
          _xPos(defaultxPos),
          _yPos(defaultyPos),
          _width(width),
          _height(height),
          _RGBA(_rectColor) {}
    ~rect() {}

    void renderRect(std::tuple<int, int, int, int> _RGBA)
    {
      SDL_SetRenderDrawColor(_renderer, std::get<0>(_RGBA), std::get<1>(_RGBA), std::get<2>(_RGBA), std::get<3>(_RGBA));
      SDL_RenderFillRect(_renderer, &_rect);
      SDL_RenderPresent(_renderer);
    }

    /* This method is used to change the properties of the rectangle*/
    void changeRect(int x, int y, int w, int h)
    {
      _rect = {
          std::get<0>(_position) = x,
          std::get<1>(_position) = y,
          w, h
        };
    }

    /* Set the position of the rectangle */
    void setPosition(int xPos, int yPos)
    {
      std::get<0>(_position) = xPos;
      std::get<1>(_position) = yPos;
    }

    /* Return the current position of the rectangle */
    std::tuple<int, int> getPosition() { return _position; }

  protected:
  

  private:
    int _xPos = 0;
    int _yPos = 0;

    int _width = 20;
    int _height = 20;

    std::tuple<int, int, int, int> _RGBA;

    std::tuple<int, int> _position = {_xPos, _yPos};

    SDL_Renderer *_renderer;
    SDL_Rect _rect = {std::get<0>(_position), std::get<1>(_position), _width, _height};
  };
} // namespace limpan

#endif
