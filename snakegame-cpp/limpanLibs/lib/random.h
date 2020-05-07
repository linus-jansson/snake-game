#include <cmath>
#include <iterator> // advance, distance
#include <numeric> // inner_product
#include <random>

namespace limpan
{   
    
    class random
    {
    public:
        /// Get a random integer value, uniformly distributed on
        // the interval [a, b), where b must be larger than 1.
        template<class T = unsigned int> T GetUniformInt(T a, T b) const
        {
            static std::random_device rd;
            static std::mt19937_64 generator(rd());
            std::uniform_int_distribution< T > dis(a, b-1);
            return dis(generator);
        }  
    };
}