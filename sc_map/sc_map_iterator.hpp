/*!
 * @file sc_map_iterator.hpp
 * @author Christian Amstutz
 * @date Feb 28, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <iterator>

//#include "sc_map_base.hpp"

template<typename object_type>
class sc_map_base;

//******************************************************************************
template<typename object_type>
class sc_map_iterator :
        public std::iterator<std::forward_iterator_tag, object_type>
{
public:
    sc_map_iterator(sc_map_base<object_type>& sc_map, unsigned int pos);
    virtual ~sc_map_iterator() {};

    bool operator==(const sc_map_iterator& other) const;
    bool operator!=(const sc_map_iterator& other) const;

    virtual sc_map_iterator& operator++ () = 0;

    object_type& operator*();

protected:
    sc_map_base<object_type>& sc_map;
    int pos;
};


//******************************************************************************
template<typename object_type>
sc_map_iterator<object_type>::sc_map_iterator(sc_map_base<object_type>& sc_map,
        unsigned int pos) :
        sc_map(sc_map), pos(pos)
{}

//******************************************************************************
template<typename object_type>
bool sc_map_iterator<object_type>::operator==(const sc_map_iterator& other) const
{
    return (pos == other.pos);
}

//******************************************************************************
template<typename object_type>
bool sc_map_iterator<object_type>::operator!=(const sc_map_iterator& other) const
{
    return ( !(*this == other));
}

//******************************************************************************
template<typename object_type>
object_type& sc_map_iterator<object_type>::operator*()
{
    return (sc_map.objects[pos]);
}

