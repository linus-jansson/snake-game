#include <tuple>

namespace limpan
{
  class rect
  {
    public:
      std::tuple<int, int> getPosition();

      void renderSquare();


    private:  
      int xPos = 0;
      int yPos = 0;

      std::tuple<int, int> posistion(xPos, yPos);


      SDL_Rect square;
  };
}
