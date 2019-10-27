#include <iostream>
#include <cassert>
#include <map>
#include "matrix.h"

int main()
{
    try
    {
        Matrix<int, -1> matrix;
        assert(matrix.size() == 0);

        auto a = matrix[0][0];
        assert(a == -1);
        assert(matrix.size() == 0);

        matrix[100][100] = 314;
        assert(matrix[100][100] == 314);
        assert(matrix.size() == 1);

        for (int i = 0; i < 10; ++i)
            matrix[i][i] = i;
        for (int i = 0; i < 10; ++i)
            matrix[9-i][i] = i;


        for (int i = 1; i < 9; i++)
        {
            for (int j = 1; j < 9; j++)
                std::cout << matrix[i][j] << " ";
            std::cout << std::endl;
        }

        std::cout << matrix.size() << std::endl;

        for(auto c : matrix)
        {
            size_t x;
            size_t y;
            int v;
            std::tie(x, y, v) = c;
            std::cout << x << y << v << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
