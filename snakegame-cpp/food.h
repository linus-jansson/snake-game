#include <tuple>
#include <iostream>

#include "rect.h"
#include "limpanLibs/lib/random.h"

namespace limpan
{
    class Food
    {
    public:
        Food(window *win)
            : _window(win),
              _maxWidth(win->getWindowWidth()),
              _maxHeight(win->getWindowHeight()),
              foodPiece(win, r.GetUniformInt<int>(0, win->getWindowWidth() - _w), r.GetUniformInt<int>(0, win->getWindowHeight() - _h), _w, _h, {0, 255, 0, 255})
        {}

        void move()
        {
            _xPos = r.GetUniformInt<int>(0, _window->getWindowWidth() - _w);
            _yPos = r.GetUniformInt<int>(0, _window->getWindowHeight() - _w);

            position = {_xPos, _yPos};

            foodPiece.changeRect(_xPos, _yPos, 20, 20);
        }

        void render()
        {   
            // std::cout << "rendering food..\n";
            foodPiece.renderRect({0, 255, 0, 255});
        }

        std::tuple<int, int> getPosition()
        {
            return position;
        }

    private:
        window *_window;

        rect foodPiece;
        random r;

        int _xPos;
        int _yPos;

        int _w = 20;
        int _h = 20;

        int _maxWidth;
        int _maxHeight;

        std::tuple<int, int> position = foodPiece.getPosition();
    };
} // namespace limpan