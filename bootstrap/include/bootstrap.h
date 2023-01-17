/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** bootstrap
*/

#ifndef BOOTSTRAP_H_
#define BOOTSTRAP_H_

#include <utility>
#include <cstddef>
#include <type_traits>
#include <typeindex>
#include <iostream>
#include <vector>
#include <map>
#include <any>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <optional>
#include <SFML/Graphics.hpp>

struct NoEntityFound : public std::exception
{
	const char * what () const throw ()
    {
    	return "Can't find an entity matching this index";
    }
};



struct A {
    A() : x(5) {}
    ~A() {}

    private:int x;
};

// class A {
    
//     template <typename Component>
//     friend class sparse_array;

//     private:
//         A(const int &i){ x = i + 1;};
//         A() = default;
//         // build_component()
//         public:
//         int x;
// };

template <typename Component>
class sparse_array
{
    // friend A::A();
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

    reference_type operator[](size_t idx)
    {
        return _data[idx];
    };

    const_reference_type operator[](size_t idx) const
    {
        return _data[idx];
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
        _data.erase(_data.begin() + pos);
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

    // friend std::ostream &operator<<( std::ostream &output, const sparse_array &D ) {
    //     for (size_t i = 0; i != D.size(); i++) {
    //         output << std::cout << D[i] << std::endl ;
    //     }
    //     return output;            
    // }


private:
    container_t _data;
};



struct NamedType
{
    explicit NamedType(size_t id) : id_(id) {}
    operator size_t() const { return id_; }
    size_t id_;
};

class registry
{
    public:
        template <class Component>
        sparse_array<Component> &register_component() {
            static sparse_array<Component> newElem;
            _components_arrays.emplace(std::type_index(typeid(Component)), newElem);
            auto lambda = []  (registry &regis, entity const &it) -> void {
                regis.remove_component<Component>(it);
            };
            _function_stored.push_back(lambda);
            return newElem;
        };

        template <class Component>
        sparse_array<Component> &get_components() {
            return std::any_cast<sparse_array<Component>&>(_components_arrays.find(std::type_index(typeid(Component)))->second);
        };

        template <class Component>
        sparse_array<Component> const &get_components() const {
            return std::any_cast<sparse_array<Component>&>(_components_arrays.find(std::type_index(typeid(Component)))->second);
        };


        entity spawn_entity() {
            size_t id_entity = 0;
            if (!_entities.empty())
                id_entity = _entities.at(_entities.size() - 1) + 1;
            entity new_entity(id_entity);
            _entities.emplace_back(new_entity);
            return new_entity;
        }

        //wtf does that mean ? ar we meant to store them ?
        entity entity_from_index(std::size_t idx) {
            if (idx > _entities.size() - 1)
                throw NoEntityFound();
            return (_entities.at(idx));
        }

        void kill_entity(entity const &e) {
            for(auto &element : _function_stored) {
                element(*this, e);
            };
        };

        // not sure about this one
        template <typename Component>
        typename sparse_array<Component>::reference_type add_component(entity const &to, Component &&c) {
            std::any_cast<sparse_array<Component>&>(_components_arrays.find(std::type_index(typeid(Component)))->second).insert_at(to, std::forward<Component>(c));
        };

        template <typename Component, typename... Params>
        typename sparse_array<Component>::reference_type emplace_component(entity const &to, Params &&... p) {
            get_components<Component>()[to].value().build_component(p...);
        };

        template <typename Component>
        void remove_component(entity const &from) {
            std::any_cast<sparse_array<Component>&>(_components_arrays.find(std::type_index(typeid(Component)))->second).erase(from);
        }

    private:
        std::unordered_map<std::type_index, std::any> _components_arrays;
        std::vector<std::function<void(registry &, entity const &)>> _function_stored;
        std::vector<entity> _entities;
};


typedef struct position {
    position() = default;
    void build_component(const int &x, const int &y) {
        _x = x;
        _y = y;
    }
    int _x;
    int _y;
} position_t;

typedef struct velocity {
    velocity() = default;
    // velocity(int speed) : _speed(speed) {}
    void build_component(const int &vx, const int& vy) {
        _vx = vx;
        _vy = vy;
    }
    int _vx;
    int _vy;
} velocity_t;

typedef struct drawable {
    drawable() = default;
    void build_component(int height, int width, std::string sprite) {
        _height = height;
        _width = width;
        _sprite = sprite;
    }
    void draw(sf::RenderWindow &win);

    std::string _sprite;
    int _height;
    int _width;
} drawable_t;

typedef struct controllable {
    controllable() = default;
    void build_component(position_t pos) {
        _position = pos;
    }
    position_t _position;
    int _current_action = -1;
} controllable_t;

#endif /* !BOOTSTRAP_H_ */
