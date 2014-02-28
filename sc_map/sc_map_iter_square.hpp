/*!
 * @file sc_map_iter_square.hpp
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

#include "sc_map_square.hpp"
#include "sc_map_iterator.hpp"

//******************************************************************************
template<typename object_type>
class sc_map_iter_square : public sc_map_iterator<object_type>
{
public:
    sc_map_iter_square& operator++ ();

private:
    sc_map_iter_square(sc_map_square<object_type>& sc_map_square, unsigned int pos);

    bool iterate_Y;
    sc_map_square<object_type>::key_type Y_pos;
    bool iterate_X;
    sc_map_square<object_type>::key_type X_pos;

    friend class sc_map_square<object_type>;
};

//******************************************************************************
template<typename object_type>
sc_map_iter_square<object_type>&
        sc_map_iter_square<object_type>::operator++ ()
{
    if(iterate_X)
    {
        ++X_pos;
    }
    if(X_pos > sc_map.)

    return (*this);
}

//******************************************************************************
template<typename object_type>
sc_map_iter_square<object_type>::sc_map_iter_square(
        sc_map_base<object_type>& sc_map, unsigned int pos) :
        sc_map_iterator<object_type>(sc_map_square, pos)
{}
