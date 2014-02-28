/*!
 * @file sc_map_iter_sequential.hpp
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

#include "sc_map_base.hpp"
#include "sc_map_iterator.hpp"

//******************************************************************************
template<typename object_type>
class sc_map_iter_sequential : public sc_map_iterator<object_type>
{
public:
    bool operator==(const sc_map_iter_sequential& other) const;
    bool operator!=(const sc_map_iter_sequential& other) const;
    virtual sc_map_iter_sequential& operator++ ();
    virtual object_type& operator*();

private:
    sc_map_base<object_type>& sc_map;
    int pos;

    sc_map_iter_sequential(sc_map_base<object_type>& sc_map, unsigned int pos);

    friend class sc_map_base<object_type>;
};


//******************************************************************************
template<typename object_type>
bool sc_map_iter_sequential<object_type>::operator==(const sc_map_iter_sequential& other) const
{
    if (&other != this)
    {
        return false;
    }
    else
    {
        return (pos == other.pos);
    }
}

//******************************************************************************
template<typename object_type>
bool sc_map_iter_sequential<object_type>::operator!=(const sc_map_iter_sequential& other) const
{
    return ( !(*this == other));
}

//******************************************************************************
template<typename object_type>
sc_map_iter_sequential<object_type>&
        sc_map_iter_sequential<object_type>::operator++ ()
{
    ++pos;
    return (*this);
}

//******************************************************************************
template<typename object_type>
object_type& sc_map_iter_sequential<object_type>::operator*()
{
    return (sc_map.objects[pos]);
}

//******************************************************************************
template<typename object_type>
sc_map_iter_sequential<object_type>::sc_map_iter_sequential(
        sc_map_base<object_type>& sc_map, unsigned int pos) :
        sc_map(sc_map), pos(pos)
{}
