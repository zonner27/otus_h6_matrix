#include <iostream>

template<typename T, T value>
class Matrix
{

public:
    Matrix() {}

};

int main()
{
    try
    {
        std::cout << "example: " << std::endl;

    }
    catch (std::exception& e)
    {

        std::cout << e.what() << std::endl;
    }


    return 0;
}
