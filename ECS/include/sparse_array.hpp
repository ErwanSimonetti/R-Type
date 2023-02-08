/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** sparse_array
*/

#pragma once

#include <optional>
#include <iostream>
#include <vector>
#include <array>
#include <exception>

/**
 * @class sparse_array
 * @brief A class for dynamic arrays.
 * 
 * sparse_array is used to represent dynamic array. This array is used to make a container with empty node.
 *
 * @tparam T The type of elements stored in the vector.
 */
template <typename Component>
class sparse_array
    {
    public:
        using value_type = std::optional<Component>; // optional component type
        using reference_type = value_type &;
        using const_reference_type = value_type const &;
        using container_t = std::vector<value_type>; // optionally add your allocator template here.
        using size_type = typename container_t::size_type;
        using iterator = typename container_t::iterator;
        using const_iterator = typename container_t::const_iterator;

    public:    
        /**
         * @brief Construct a new empty sparse array object
         * 
         */
        sparse_array() = default; // You can add more constructors .

        /**
         * @brief Construct a new sparse array object with the copy of another sparse array
         * 
         * @param other is the object copied
         */
        sparse_array(sparse_array const &other)
        {
            this->_data = other._data;
        }; // copy constructorn

        /**
         * @brief Construct a new sparse array object by moving the contents of another to that one
         * 
         * @param other is the object copied
         */
        sparse_array(sparse_array &&other) noexcept
        {
            this->_data = other._data;
            other._data.clear();
        }; // move constructor

        /**
         * @brief Destroy the sparse array object
         * 
         */
        ~sparse_array() = default;

        /**
         * @brief Overloaded operator = to copy the content of one sparse array to another
         * 
         * @param other The sparse array to copy
         * @return A sparse array with content of the copy
         */
        sparse_array &operator=(sparse_array const &other)
        {
            this->_data = other._data;
            return *this;
        }; // copy assignment operator

        /**
         * @brief Overloaded operator = to move the content of one sparse array to another
         * 
         * @param other The sparse array to move
         * @return A sparse array with content of the move
         */
        sparse_array &operator=(sparse_array &&other) noexcept
        {
            this->_data = other._data;
            return *this;
        } // move assignment operator

        /**
         * @brief Overloaded operator [] to get the content of a position of the vector
         * 
         * @param idx The index of the element to be accessed.
         * @return  A reference to the element at the specified index.
         */
        reference_type operator[](size_t idx)
        {
            return _data.at(idx);
        };

        /**
         * @brief Overloaded operator [] to get the content of a position of the vector
         * 
         * @param idx The index of the element to be accessed.
         * @return  A const reference to the element at the specified index.
         */
        const_reference_type operator[](size_t idx) const
        {
            return _data.at(idx);
        }

        /**
         * @brief Get a pointer on the first node of the vector.
         * 
         * @return iterator on the begin of the vector.
         */
        iterator begin() { return _data.begin(); };

        /**
         * @brief Get a pointer on the first node of the vector.
         * 
         * @return const iterator on the begin of the vector.
         */
        const_iterator begin() const { return *_data.begin(); };

        /**
         * @brief Get a pointer on the first node of the vector.
         * 
         * @return const iterator on the begin of the vector.
         */
        const_iterator cbegin() const { return *_data.begin(); };

        /**
         * @brief Get a pointer on the last node of the vector.
         * 
         * @return iterator on the end of the vector.
         */
        iterator end() { return _data.end(); };

        /**
         * @brief Get a pointer on the last node of the vector.
         * 
         * @return const iterator on the end of the vector.
         */
        const_iterator end() const { return *_data.end(); };

        /**
         * @brief Get a pointer on the last node of the vector.
         * 
         * @return const iterator on the end of the vector.
         */
        const_iterator cend() const { return *_data.end(); };

        /**
         * @brief Gets the size of the vector
         * 
         * @return the size using size method in std::vector
         */
        size_type size() const
        {
            return _data.size();
        };

        /**
         * @brief Insert a copy of a component at a pos in the vector.
         * 
         * @param pos the pos of the object.
         * @param it the object.
         * @return reference_type on the object.
         */
        reference_type insert_at(size_type pos, Component const &it)
        {
            if (_data.size() < pos + 1)
                _data.resize(pos + 1);
            _data[pos] = it;
            return _data[pos];
        };

       /**
         * @brief Move a component at a pos in the vector.
         * 
         * @param pos the pos of the object.
         * @param it the object.
         * @return reference_type on the object.
         */
        reference_type insert_at(size_type pos, Component &&it)
        {
            if (_data.size() < pos + 1)
                _data.resize(pos + 1);
            _data[pos] = it;
            return _data[pos];
        };

        template <class ... Params >
        reference_type emplace_at ( size_type pos , Params &&... par)
        {
            for (std::size_t x = 0; x < sizeof...(par); ++x)
                std::cout << std::array<typename std::common_type<Params...>::type,sizeof...(par)>{par...}[x] << std::endl;
        }

       /**
         * @brief Erase a component at a pos in the vector.
         * 
         * @param pos the pos of the object.
         */
        void erase(size_type pos)
        {
            if (_data.at(pos).has_value())
                _data.at(pos) = std::nullopt;
        };

        /**
         * @brief Get the index to an object in the array.
         * 
         * @param it the object wanted in the array.
         * @return the pos of the object (-1 if doesn't find). 
         */
        size_type get_index(value_type const &it) const
        {
            auto elem = find(_data.begin(), _data.end(), it);

            int index = -1;
            if (elem != _data.end())
            {
                index = elem - _data.begin();
            }
            return index;
        };

        /**
         * @brief Get the information if the vector is empty or not.
         * 
         * @return true, the vector is empty
         * @return false, the vector is not empty
         */
        bool empty() const
        {
            return _data.empty();
        };

        /**
         * @brief Overloaded operator << to fill output to print with content of vector.
         * 
         * @param output the output object to fill.
         * @param D, the sparse array that will be displayed.
         * @return std::ostream& the output.
         */
        friend std::ostream &operator<<(std::ostream &output, const sparse_array &D) {
            if (!D.empty()) {
                for (size_t i = 0; i != D.size(); i++) {
                    if (D[i].has_value()) {
                        output << i << ": " << D[i].value() << std::endl;
                    }
                }
                return output;            
            }
            return output;
        }


    private:
        /**
         * @brief is the std::vector encapsulated in sparse array.
         * 
         */
        container_t _data;
};
