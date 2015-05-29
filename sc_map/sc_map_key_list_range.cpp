/*!
 * @file ssc_map_key_list_range.cpp
 * @author Christian Amstutz
 * @date May 29, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "sc_map_key_list_range.hpp"

//******************************************************************************
template <typename key_T>
sc_map_key_list_range<key_T>::sc_map_key_list_range()
{}

//******************************************************************************
template <typename key_T>
sc_map_key_list_range<key_T>::sc_map_key_list_range(
        const std::vector<key_type> keys) :
        keys(keys)
{}

//******************************************************************************
template <typename key_T>
void sc_map_key_list_range<key_T>::add_key(const key_type& new_key)
{
    keys.push_back(new_key);

    return;
}

//******************************************************************************
template <typename key_T>
void sc_map_key_list_range<key_T>::add_key(const std::vector<key_type>& new_keys)
{
    keys.insert(keys.end(), new_keys.begin(), new_keys.end());

    return;
}

//******************************************************************************
template <typename key_T>
typename sc_map_key_list_range<key_T>::key_type
        sc_map_key_list_range<key_T>::first() const
{
    return keys[0];
}

//******************************************************************************
template <typename key_T>
typename sc_map_key_list_range<key_T>::key_type
        sc_map_key_list_range<key_T>::last() const
{
    return keys[keys.size()-1];
}

//******************************************************************************
template <typename key_T>
bool sc_map_key_list_range<key_T>::next_key(key_type& key) const
{
    bool found = false;

    for (typename std::vector<key_type>::iterator key_it = keys.begin();
         key_it != keys.end();
         ++key_it)
    {
        if (*key_it == key)
        {
            ++key_it;
            if (key_it != keys.end())
            {
                key = *key_it;
                return true;
            }
        }
    }

    return false;
}

//******************************************************************************
template <typename key_T>
bool sc_map_key_list_range<key_T>::key_in_range(const key_type& key) const
{
    for (typename std::vector<key_type>::iterator key_it = keys.begin();
         key_it != keys.end();
         ++key_it)
    {
        if (*key_it == key)
        {
            return true;
        }
    }

    return false;
}

//******************************************************************************
template <typename key_T>
std::vector<typename sc_map_key_list_range<key_T>::key_type>
        sc_map_key_list_range<key_T>::get_key_vector() const
{
    return keys;
}
