#include <tuple>
#include <iostream>

#include "rect.h"

#include "limpanLibs/lib/random.h"

namespace limpan
{
    class Snake //: rect
    {
    public:
        enum DIRECTION
        {
            UP,
            DOWN,
            LEFT,
            RIGHT,
            STOP
        };

        Snake(window *win)
            : _window(win),
              _maxWidth(win->getWindowWidth()),
              _maxHeight(win->getWindowHeight()),
              head(win, r.GetUniformInt<int>(0, win->getWindowWidth() - _w), r.GetUniformInt<int>(0, win->getWindowHeight() - _h), 20, 20, {0, 0, 255, 255}),
              body()
        {
        }

        void move(DIRECTION dir = DIRECTION::STOP)
        {
            switch (dir)
            {
            case RIGHT:
                head.changeRect(std::get<0>(position) += _speed, std::get<1>(position), _w, _h);
                break;
            case LEFT:
                head.changeRect(std::get<0>(position) -= _speed, std::get<1>(position), _w, _h);
                break;
            case UP:
                head.changeRect(std::get<0>(position), std::get<1>(position) -= _speed, _w, _h);
                break;
            case DOWN:
                head.changeRect(std::get<0>(position), std::get<1>(position) += _speed, _w, _h);
                break;
            case STOP:
                head.changeRect(std::get<0>(position), std::get<1>(position), _w * 2, _h * 2);
                break;
            default:
                break;
            }
        }

        void grow()
        {
            std::cout << ++_size << "\n";

            DIRECTION dir;
            addToTail(dir); 
        }

        void render()
        {
            head.renderRect({255, 255, 255, 255});
        }

        std::tuple<int, int> getPosition()
        {
            return position;
        }

        void setPosition(int xPos, int yPos)
        {
            head.setPosition(xPos, yPos);
            position = {xPos, yPos};
        }

        int getHeadWidth()
        {
            return _w;
        }

        int getHeadHeight()
        {
            return _h;
        }
        // void renderTail(std::vector<std::tuple<int, int>> & tail, limpan::window & frame)
        // {
        // 	std::tuple<int, int, int, int> tailColor(255, 255, 255, 255);

        // 	for (auto t : tail)
        // 	{
        // 		limpan::rect tail(&frame, std::get<0>(t), std::get<1>(t), 20);
        // 		tail.renderRect(tailColor);
        // 	}

        // }

        // void moveTail(std::vector<std::tuple<int, int>> & tail, limpan::rect & snake)
        // {

        // 	std::tuple<int, int> headCurrent = snake.getPosition();

        // 	tail[0] = headCurrent;

        // 	for (int i = 1; i < tail.size(); i++)
        // 	{
        // 		tail[i] = tail[i++];
        // 	}
        // 	// Get the current position of the snake
        // 	// Move index back one place
        // }

        // If head touches food call this function and add one to the vector(tail)


    private:
        // std::tuple<int, int, int, int> headColor = ;

        void addToTail(DIRECTION & dir)
        {
            // Hämta "direcvtion" --> Lägg till Den positionen + directionen (Så den hamnar rätt) till vectorn
            switch (dir)
            {
            case RIGHT:
                // position = {std::get<0>(getPosition()) - _w, std::get<1>(getPosition())};
                
                body.push_back(rect(_window, std::get<0>(getPosition()) - _w, std::get<1>(getPosition()), 20, 20, {255, 255, 255, 255}));
                break;
            case LEFT:
                // position = {std::get<0>(getPosition()) + _w, std::get<1>(getPosition())};
                // body.push_back(position);
                break;
            case UP:
                // position = {std::get<0>(getPosition()), std::get<1>(getPosition()) + _h};
                // body.push_back(position);
                break;
            case DOWN:
                // position = {std::get<0>(getPosition()), std::get<1>(getPosition()) - _h};
                // body.push_back(position);
                break;
            default:
                break;
            }
        }

        random r;

        const int _w = 20;
        const int _h = 20;
        int _speed = 2;

        int _size = 0;

        window *_window;

        rect head;

        std::vector<rect> body;

        int _maxWidth;
        int _maxHeight;

        std::tuple<int, int> position = head.getPosition();
    };
} // namespace limpan
