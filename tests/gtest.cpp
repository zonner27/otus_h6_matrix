#include <gtest/gtest.h>
#include "matrix.h"


TEST(TestMatrix, create_matrix)
{
    Matrix<int, -1> matrix;
    ASSERT_TRUE(matrix.size() == 0);
}

TEST(TestMatrix, value_matrix)
{
    Matrix<int, -1> matrix;
    auto a = matrix[0][0];
    ASSERT_TRUE(a == -1);
    ASSERT_TRUE(matrix.size() == 0);
}

TEST(TestMatrix, fill_matrix)
{
    Matrix<int, -1> matrix;
    matrix[100][100] = 314;
    ASSERT_TRUE(matrix[100][100] == 314);
    ASSERT_TRUE(matrix.size() == 1);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
