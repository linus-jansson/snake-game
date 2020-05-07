#include "random.h"

#include <iostream>


int main()
{
    limpan::random n;

    std::cout << n.GetUniformInt<int>(21, 69) << "\n";

    return 0;
}