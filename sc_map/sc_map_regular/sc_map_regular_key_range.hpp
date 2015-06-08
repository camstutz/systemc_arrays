/*!
 * @file sc_map_regular_key_range.hpp
 * @author Christian Amstutz
 * @date June 5, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../sc_map_key_range.hpp"

#include <vector>

//******************************************************************************
template <typename key_T>
class sc_map_regular_key_range : public sc_map_key_range<key_T>
{
public:
    typedef key_T key_type;

    sc_map_regular_key_range(key_type start_key, key_type end_key);
    virtual ~sc_map_regular_key_range() {};

    virtual sc_map_key_range<key_type>* clone() =0;

    virtual key_type first() const;
    virtual key_type last() const;

    virtual bool next_key(key_type& key) const =0;

    std::vector<key_type> get_key_vector() const;

public:
    key_type start_key;
    key_type end_key;
};

//******************************************************************************

//******************************************************************************
template <typename key_T>
sc_map_regular_key_range<key_T>::sc_map_regular_key_range(key_type start_key,
        key_type end_key) :
        start_key(start_key),
        end_key(end_key)
{}

//******************************************************************************
template <typename key_T>
typename sc_map_regular_key_range<key_T>::key_type
        sc_map_regular_key_range<key_T>::first() const
{
    return start_key;
}


//******************************************************************************
template <typename key_T>
typename sc_map_regular_key_range<key_T>::key_type
        sc_map_regular_key_range<key_T>::last() const
{
    return end_key;
}

//******************************************************************************
template <typename key_T>
std::vector<typename sc_map_regular_key_range<key_T>::key_type>
        sc_map_regular_key_range<key_T>::get_key_vector() const
{
    std::vector<key_type> key_vector;

    key_type key = first();
    do
    {
        key_vector.push_back(key);
    } while (next_key(key));

    return key_vector;
}
