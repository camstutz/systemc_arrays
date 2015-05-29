/*!
 * @file sc_map_linear_key_range.cpp
 * @author Christian Amstutz
 * @date May 28, 2015
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
        start_key(0),
        end_key(0)
{
    // todo:: this is basically not correct!
}

//******************************************************************************
sc_map_linear_key_range::sc_map_linear_key_range(key_type start_key,
        key_type end_key) :
        start_key(start_key),
        end_key(end_key)
{}

//******************************************************************************
sc_map_linear_key_range::key_type sc_map_linear_key_range::first() const
{
    return start_key;
}


//******************************************************************************
sc_map_linear_key_range::key_type sc_map_linear_key_range::last() const
{
    return end_key;
}

//******************************************************************************
bool sc_map_linear_key_range::key_in_range(const key_type& key) const
{
    const sc_map_linear_key* key_linear =
            dynamic_cast<const sc_map_linear_key*>(&key);

    if ((*key_linear >= start_key) & (*key_linear <= end_key))
    {
        return true;
    }

    return false;
}

//******************************************************************************
bool sc_map_linear_key_range::next_key(key_type& key) const
{
    sc_map_linear_key* key_linear = dynamic_cast<sc_map_linear_key*>(&key);

    sc_map_linear_key new_key;
    new_key.X = key_linear->X + 1;

    if (key_in_range(new_key))
    {
        *key_linear = new_key;
        return true;
    }

    return false;
}

//******************************************************************************
std::vector<sc_map_linear_key_range::key_type>
        sc_map_linear_key_range::get_key_vector() const
{
    std::vector<key_type> key_vector;

    for (key_type::index_type key = start_key.X; key <= end_key.X; ++key)
    {
        key_vector.push_back(key);
    }

    return key_vector;
}
