/*!
 * @file sc_map_key_list_range.hpp
 * @author Christian Amstutz
 * @date May 29, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_key_range.hpp"

#include <vector>

//******************************************************************************
template <typename key_T>
class sc_map_key_list_range : public sc_map_key_range<key_T>
{
public:
    typedef typename sc_map_key_range<key_T>::key_type key_type;

    sc_map_key_list_range();
    sc_map_key_list_range(const std::vector<key_type> keys);
    virtual ~sc_map_key_list_range() {};

    void add_key(const key_type& new_key);
    void add_key(const std::vector<key_type>& new_keys);

    virtual key_type first() const;
    virtual key_type last() const;
    virtual bool next_key(key_type& key) const;
    virtual bool key_in_range(const key_type& key) const;

    std::vector<key_type> get_key_vector() const;

private:
    std::vector<key_type> keys;
};
