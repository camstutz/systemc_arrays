/*!
 * @file sc_map_linear.hpp
 * @author Christian Amstutz
 * @date May 19, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_base.hpp"
#include "sc_map_iter_linear.hpp"
#include "sc_map_linear_key.hpp"

#include <systemc.h>

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <utility>

//******************************************************************************

template <typename object_type>
class sc_map_linear : public sc_map_base<sc_map_linear_key, object_type>
{
    friend class sc_map_iter_linear<object_type>;

public:
    typedef sc_map_base<sc_map_linear_key, object_type> base;
    typedef sc_map_regular_base<sc_map_linear_key, object_type> regular_base;
    typedef sc_map_iter_linear<object_type> linear_iterator;
    typedef sc_map_linear_key key_type;
    typedef regular_base::index_type index_type
    typedef typename base::size_type size_type;
    typedef typename std::map<key_type, size_type, key_type::Comperator> map_type;

    static const regular_base::index_t default_start_id;

    using base::bind;
    using base::operator();

    sc_map_linear(const size_type element_cnt_X, const sc_module_name name = "", const key_type start_id_X = default_start_id);
    template <typename config_type>
    sc_map_linear(const size_type element_cnt_X, const sc_module_name name, const config_type configuration, const key_type start_id_X = default_start_id);
    virtual ~sc_map_linear() {};

    size_type size_X() const;

    //* todo: const version needed?
    object_type& at(const key_type key_X);
    object_type& operator[] (const key_type key_X);
    linear_iterator operator()(const key_type X_start, const key_type X_stop);

    virtual std::string key_string(object_type& map_element) const;

private:
    key_type start_id_X;

    map_type objects_map;

    size_type get_vect_pos(key_type pos_X);

    class creator
    {
    public:
        creator() {};
        object_type* operator() (const sc_module_name name,
                sc_map_linear<object_type>::key_type id);
        template <typename config_type>
        object_type* operator() (const sc_module_name name,
                sc_map_linear<object_type>::key_type id, const config_type& configuration);
    };
};

//******************************************************************************

//******************************************************************************

//template <typename object_type>
//const typename sc_map_key_regular_base::index_t
//        sc_map_linear<object_type>::default_start_id = def;

//******************************************************************************

template <typename object_type>
sc_map_linear<object_type>::sc_map_linear(const size_type element_cnt_X,
        const sc_module_name name, const key_type start_id_X) :
        sc_map_base<object_type>(name)
{
    this->start_id_X = start_id_X;
    this->init(element_cnt_X, creator());

    for (size_type x = 0; x<element_cnt_X; ++x)
    {
        size_type vector_id = x;
        objects_map[start_id_X+x] = vector_id;
    }

    return;
}

//******************************************************************************
template <typename object_type>
template <typename config_type>
sc_map_linear<object_type>::sc_map_linear(const size_type element_cnt_X,
        const sc_module_name name, const config_type configuration,
        const key_type start_id_X) :
        sc_map_base<object_type>(name)
{
    this->start_id_X = start_id_X;
    this->init(element_cnt_X, creator(), configuration);

    for (size_type x = 0; x<element_cnt_X; ++x)
    {
        size_type vector_id = x;
        objects_map[start_id_X+x] = vector_id;
    }

    return;
}

//******************************************************************************
template <typename object_type>
typename sc_map_linear<object_type>::size_type sc_map_linear<object_type>::size_X() const
{
    return objects_map.size();
}

//******************************************************************************
template <typename object_type>
object_type& sc_map_linear<object_type>::at(const key_type key_X)
{
    // todo: at exception handling for out range accesses
    object_type& ret_object = *(this->objects[key_X]);

    return ret_object;
}

//******************************************************************************
template <typename object_type>
object_type& sc_map_linear<object_type>::operator[] (const key_type key_X)
{
    return at(key_X);
}

//******************************************************************************
template <typename object_type>
typename sc_map_linear<object_type>::linear_iterator
        sc_map_linear<object_type>::operator()(const key_type X_start,
        const key_type X_stop)
{
    sc_map_iter_linear<object_type> it(*this, X_start, X_stop);

    return it;
}

//******************************************************************************
template <typename object_type>
std::string sc_map_linear<object_type>::key_string(object_type& map_element) const
{
    std::stringstream key_sstream;

    std::pair<bool, full_key_type> key_return = get_key(map_element);
    if (key_return.first)
    {
        full_key_type key = key_return.second;
        key_sstream << key.X_dim;
    }

    return key_sstream.str();
}

//******************************************************************************
template <typename object_type>
typename sc_map_linear<object_type>::size_type
        sc_map_linear<object_type>::get_vect_pos(key_type pos_X)
{
    size_type vector_pos = objects_map.at(pos_X);

    return vector_pos;
}

//******************************************************************************
template <typename object_type>
object_type* sc_map_linear<object_type>::creator::operator() (
        const sc_module_name name, sc_map_linear<object_type>::key_type id)
{
    std::stringstream full_name;
    
    full_name << name << sc_map_linear<object_type>::key_separator << id;

    return (new object_type(full_name.str().c_str()) );
}

//******************************************************************************
template <typename object_type>
template <typename config_type>
object_type* sc_map_linear<object_type>::creator::operator() (
        const sc_module_name name, sc_map_linear<object_type>::key_type id, const config_type& configuration)
{
    std::stringstream full_name;

    full_name << name << sc_map_linear<object_type>::key_separator << id;

    return (new object_type(full_name.str().c_str(), configuration));
}

