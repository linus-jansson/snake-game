#include <tuple>
#include <iostream>

#include "rect.h"

#include "limpanLibs/lib/random.h"
/*

Klassen orm kommer ärva från rektangel.
och snake kommer bara ha ett object.

*/
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
            head(win, r.GetUniformInt<int>(0, win->getWindowWidth() - w), r.GetUniformInt<int>(0, win->getWindowHeight() - h), 20, 20, {255, 255, 255, 255})
        {
        }

        void move(DIRECTION dir = DIRECTION::STOP)
        {
            switch (dir)
            {
            case RIGHT:
                head.changeRect(std::get<0>(position) += speed, std::get<1>(position), w, h);
                break;
            case LEFT:
                head.changeRect(std::get<0>(position) -= speed, std::get<1>(position), w, h);
                break;
            case UP:
                head.changeRect(std::get<0>(position), std::get<1>(position) -= speed, w, h);
                break;
            case DOWN:
                head.changeRect(std::get<0>(position), std::get<1>(position) += speed, w, h);
                break;
            case STOP:
                head.changeRect(std::get<0>(position), std::get<1>(position), w * 2, h * 2);
                break;
            default:
                break;
            }
            
        }

        void grow()
        {
            std::cout << ++size << "\n";
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
            return w;
        }

        int getHeadHeight()
        {
            return h;
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
        // void addToTail(std::vector<std::tuple<int, int>> & tail,limpan::rect & snake, char & dir, int size)
        // {

        //     std::tuple<int, int> position;
        //     // Hämta "direcvtion" --> Lägg till Den positionen + directionen (Så den hamnar rätt) till vectorn
        //     switch (dir)
        //     {
        //     case 'r':
        //         position = {std::get<0>(snake.getPosition()) - size, std::get<1>(snake.getPosition())};
        //         tail.push_back(position);
        //         break;
        //     case 'l':
        //         position = {std::get<0>(snake.getPosition()) + size, std::get<1>(snake.getPosition())};
        //         tail.push_back(position);
        //         break;
        //     case 'u':
        //         position = {std::get<0>(snake.getPosition()), std::get<1>(snake.getPosition()) + size};
        //         tail.push_back(position);
        //         break;
        //     case 'd':
        //         position = {std::get<0>(snake.getPosition()), std::get<1>(snake.getPosition()) - size};
        //         tail.push_back(position);
        //         break;
        //     default:
        //         break;
        //     }
        // }

    private:
        // std::tuple<int, int, int, int> headColor = ;

        random r;

        const int w = 20;
        const int h = 20;
        const int speed = 1;

        int size = 0;

        window *_window;

        rect head;
        std::vector<rect> body;

        int _maxWidth;
        int _maxHeight;

        std::tuple<int, int> position = head.getPosition();
    };
} // namespace limpan
