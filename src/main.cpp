#include <iostream>
#include <cassert>
#include <map>

using Index = std::pair<size_t, size_t>;

template<class T, T value>
class Matrix;

template<class T, T value>
class Row
{
public:
    T& operator[](size_t m)
    {
        m_index.second = m;
        auto it = (*m_map).find(m_index);
        if (it == (*m_map).end())
            m_map->emplace(m_index, value);
        return (*m_map)[m_index];
    }
    ~Row()
    {
        if ((*m_map)[m_index] == value)
            m_map->erase(m_index);
    }

private:
    friend class Matrix<T, value>;
    Row(std::map<Index, T>* m_map_, size_t n) :
        m_map(m_map_)
    {
        m_index.first = n;
    }
    Row() = delete;
    std::map<Index, T> *m_map;
    Index m_index;
};


template<class T, T value>
class Matrix
{
public:
    auto begin()
    {
        return Matrix_Iterator{*this, 0};
    }
    auto end()
    {
        return Matrix_Iterator{*this, m_map.size()};
    }

    size_t size()
    {
        return m_map.size();
    }

    Row<T, value> operator[](size_t n)
    {
        return Row<T, value>(&m_map, n);
    }

private:
    std::map<Index, T> m_map;
    class Matrix_Iterator
    {
    public:
        Matrix_Iterator(Matrix& m_matrix_, std::size_t m_index_ = 0)
            :m_matrix{m_matrix_}, m_index{m_index_}, m_itetator(m_matrix.m_map.begin()) {}

        bool operator !=(const Matrix_Iterator& it)
        {
            return m_index != it.m_index;
        }

        bool operator ==(const Matrix_Iterator& it)
        {
            return m_index == it.m_index;
        }

        Matrix_Iterator operator++()
        {
            ++m_index;
            ++m_itetator;
            return *this;
        }

        std::tuple<size_t, size_t, T> operator*()
        {
            Index index = m_itetator->first;
            T val = m_itetator->second;
            return std::make_tuple(index.first, index.second, val);
        }

    private:
        Matrix& m_matrix;
        size_t m_index;
        typename std::map<Index, T>::iterator m_itetator;
    };
};


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
