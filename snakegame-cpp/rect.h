#include <tuple>

namespace limpan
{
  class rect
  {
    public:
      rect()
      {

      }
      ~rect()
      {

      }

      std::tuple<int, int> getPosition() { return _position; }

      void renderSquare(std::tuple<int, int, int, int> & RGBA)
      {
        	SDL_SetRenderDrawColor(_renderer, std::get<0>(RGBA), std::get<1>(RGBA), std::get<2>(RGBA), std::get<3>(RGBA));
          SDL_RenderFillRect(_renderer, &_rect);
          SDL_RenderPresent(_renderer);
      }


    private:  
      int _xPos = 0;
      int _yPos = 0;

      int _width = 20;
      int _height = 20;

      std::tuple<int, int> _position = {_xPos, _yPos};

      SDL_Renderer *_renderer;
      SDL_Rect _rect;
  };
}
