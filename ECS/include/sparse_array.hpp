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
        sparse_array() = default; // You can add more constructors .
        sparse_array(sparse_array const &other)
        {
            this->_data = other._data;
        }; // copy constructorn

        sparse_array(sparse_array &&other) noexcept
        {
            this->_data = other._data;
            other._data.clear();
        }; // move constructor

        ~sparse_array() = default;

        sparse_array &operator=(sparse_array const &other)
        {
            this->_data = other._data;
            return *this;
        }; // copy assignment operator
        sparse_array &operator=(sparse_array &&other) noexcept
        {
            this->_data = other._data;
            return *this;
        } // move assignment operator

        value_type operator[](size_t idx)
        {
            if (idx <= _data.size())
                return _data[idx];
            else
                throw std::out_of_range("Index " + std::to_string(idx) + " is out of range for vector of size " + std::to_string(_data.size()));
        };

        const_reference_type operator[](size_t idx) const
        {
            if (idx <= _data.size())
                return _data[idx];
            else
                throw std::out_of_range("Index " + std::to_string(idx) + " is out of range for vector of size " + std::to_string(_data.size()));
        }

        iterator begin() { return _data.begin(); };
        const_iterator begin() const { return *_data.begin(); };
        const_iterator cbegin() const { return *_data.begin(); };
        iterator end() { return _data.end(); };
        const_iterator end() const { return *_data.end(); };
        const_iterator cend() const { return *_data.end(); };

        size_type size() const
        {
            return _data.size();
        };

        reference_type insert_at(size_type pos, Component const &it)
        {
            if (_data.size() < pos + 1)
                _data.resize(pos + 1);
            _data[pos] = it;
            return _data[pos];
        };

        reference_type insert_at(size_type pos, Component &&it)
        {
            if (_data.size() < pos + 1)
                _data.resize(pos + 1);
            _data[pos] = it;
            return _data[pos];
        };


        // template <class Component, class ... Params>
        // reference_type recurs_emplace_at(size_type pos , Component &&c, Params &&...p) {
        //     insert_at(pos, c);
        //     recurs_emplace_at<Params>(pos, p...);
        // }; // optional

        // template <class ... Params>
        // reference_type emplace_at (size_type pos , Params &&...p); // optional
        template <class ... Params >
        reference_type emplace_at ( size_type pos , Params &&... par)
        {
            // for (int x = 0; x< sizeof...(par) ;x++)
            //     std::cout << par << std::endl;
            //     // _data.emplace(params, pos);
            for (std::size_t x = 0; x < sizeof...(par); ++x)
                std::cout << std::array<typename std::common_type<Params...>::type,sizeof...(par)>{par...}[x] << std::endl;
        }

        void erase(size_type pos)
        {
            try
            {
                if (_data[pos].has_value())
                    _data[pos] = std::nullopt;
                else
                    throw std::out_of_range(std::string("You can't erase an empty position."));
            } catch (std::out_of_range &e) {
                std::cerr << "Invalid position: " << pos << std::endl;
            }
        };

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

        bool  empty() const
        {
            return _data.empty();
        };

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
        container_t _data;
};
