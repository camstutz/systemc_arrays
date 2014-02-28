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
    sc_map_iterator();
    virtual ~sc_map_iterator() {};

    virtual sc_map_iterator& operator++ () = 0;

    virtual object_type& operator*() =0;
};


//******************************************************************************
template<typename object_type>
sc_map_iterator<object_type>::sc_map_iterator()
{}



