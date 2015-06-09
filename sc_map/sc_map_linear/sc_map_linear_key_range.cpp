/*!
 * @file sc_map_linear_key_range.cpp
 * @author Christian Amstutz
 * @date June 9, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "sc_map_linear_key_range.hpp"

//******************************************************************************
sc_map_linear_key_range::sc_map_linear_key_range() :
        sc_map_regular_key_range(0, 0)
{}
    // todo:: this is basically not correct!

//******************************************************************************
sc_map_linear_key_range::sc_map_linear_key_range(key_type start_key,
        key_type end_key) :
        sc_map_regular_key_range(start_key, end_key)
{}

//******************************************************************************
sc_map_linear_key_range::sc_map_linear_key_range(sc_map_key_range<key_type>*,
        key_type start_key, key_type end_key) :
        sc_map_regular_key_range(start_key, end_key)
{}

//******************************************************************************
sc_map_linear_key_range* sc_map_linear_key_range::clone() const
{
  return new sc_map_linear_key_range(*this);
}

//******************************************************************************
bool sc_map_linear_key_range::next_key(key_type& key) const
{
    sc_map_linear_key* key_linear = dynamic_cast<sc_map_linear_key*>(&key);
    sc_map_linear_key new_key;

    if (start_key <= end_key)
    {
        new_key.X = key_linear->X + 1;
        if (new_key <= end_key)
        {
            *key_linear = new_key;
            return true;
        }
    }
    else
    {
        new_key.X = key_linear->X - 1;
        if (new_key >= end_key)
        {
            *key_linear = new_key;
            return true;
        }
    }

    return false;
}
