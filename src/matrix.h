#ifndef MATRIX222220102019_H
#define MATRIX222220102019_H

#include <iostream>
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


#endif //MATRIX222220102019_H
