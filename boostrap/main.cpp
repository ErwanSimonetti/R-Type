/*
** EPITECH PROJECT, 2023
** boostrap
** File description:
** main
*/

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

class entity {
    friend class registry;
    public:
        explicit entity(size_t id) : _id(id) {}
        template <typename T, typename = std::enable_if_t<std::is_convertible_v<T, size_t>>>
        explicit entity(T t) : _id(static_cast<size_t>(t)) {}
        operator size_t() const { return _id; }
    
    private:
        size_t _id;
};

struct A {
    A() : x(5) {}
    ~A() {}

    private: int x;
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


        entity spawn_entity();

        //wtf does that mean ? ar we meant to store them ?
        template <class Component>
        entity entity_from_index(std::size_t idx) {
            // return _components_arrays.find(std::type_index(typeid(Component)))->second[idx];x    
        };

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
    // velocity(int speed) : _speed(speed) {}
    void build_component(const int &speed) {
        _speed = speed;
    }
    int _speed;
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
} controllable_t;

int main(void)
{
    
    entity j(5);
    // Entity n(NamedType(8));
    // Entity e(NamedType(5));
    // Entity g(NamedType(5));

    // sparse_array<char> a;
    // a.insert_at(0, 'a');

    registry reg;
    // reg.register_component<char>();
    reg.register_component<position_t>();
    reg.register_component<velocity_t>();
    reg.register_component<drawable_t>();
    // reg.register_component<position_t>();
    // reg.register_component<int>();
    // reg.get_components<char>().insert_at(0, 'J');
    // reg.get_components<char>().insert_at(1, 'a');
    // reg.get_components<int>().insert_at(1, 1);
    // reg.get_components<int>().insert_at(0, 2);

    // std::cout << "function stored size = " << reg._function_stored.size() << '\n';
    // printf("chars: \n");
    // std::cout << reg.get_components<char>();
    // printf("___________________\nint: \n");
    // std::cout << reg.get_components<int>();

    // reg.remove_component<char>(reg.get_components<char>()[0]);
    // reg.unregister_component<char>(reg, entity(1));
    // reg.(entity(1));
    // printf("__________________\nchars: \n");
    // reg.kill_entity(entity(0));
    position pos;
    velocity_t vel;
    reg.add_component<position_t>(j, std::move(pos));
    reg.add_component<velocity_t>(j, std::move(vel));
    // std::cout << reg.get_components<position_t>();
    // std::cout << std::any_cast<sparse_array<position_t>&>(reg.get_components<position_t>())[5]._x << "\n";
    reg.emplace_component<position_t>(j, 1, 2);
    reg.emplace_component<velocity_t>(j, 7);

    std::cout << reg.get_components<position_t>()[j].value()._x << " ";
    std::cout << reg.get_components<position_t>()[j].value()._y << "\n";
    std::cout << reg.get_components<velocity_t>()[j].value()._speed << "\n";


    // printf("chars: \n"); 
    // std::cout << reg.get_components<A>();
    // printf("___________________\nint: \n");
    // std::cout << reg.get_components<int>();

    // reg.remove_component()
    // req.register_component<>()

    // printf("____________\n");
    // reg.insert_at(0, 'b');
    // printf("____________\n");
    // a.insert_at(1, 'c');
    // printf("____________lol\n");
    // a.insert_at(10, 'z');
    // printf("____________lol\n");
    // a.erase(1);
    // // std::cout << '|' << a._data[1] << "|\n";

    // // a.insert_at(9, 'Y');
    // std::cout << a.get_index('z') << '\n';
    // // a.insert_at(10, 'Z');
    // printf("trop marrant\n");
    // sparse_array<char> ok;
    // ok = a;
    // std::cout << a[1] << std::endl;
    // std::cout << ok[1] << std::endl;
}