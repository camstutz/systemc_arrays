/*!
 * @file sc_map_linear_key_range.hpp
 * @author Christian Amstutz
 * @date June 2, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_linear_key.hpp"
#include "../sc_map_key_range.hpp"

#include <vector>

//******************************************************************************
class sc_map_linear_key_range : public sc_map_key_range<sc_map_linear_key>
{
public:
    typedef sc_map_key_range::key_type key_type;

    sc_map_linear_key_range();
    sc_map_linear_key_range(sc_map_key_range<key_type>*, key_type start_key, key_type end_key);
    virtual ~sc_map_linear_key_range() {};

    virtual sc_map_linear_key_range* clone();

    virtual key_type first() const;
    virtual key_type last() const;

    virtual bool key_in_range(const key_type& key) const;
    virtual bool next_key(key_type& key) const;

    std::vector<key_type> get_key_vector() const;

public:
    key_type start_key;
    key_type end_key;
};
