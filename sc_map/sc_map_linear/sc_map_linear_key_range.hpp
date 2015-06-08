/*!
 * @file sc_map_linear_key_range.hpp
 * @author Christian Amstutz
 * @date June 8, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_linear_key.hpp"
#include "../sc_map_regular/sc_map_regular_key_range.hpp"

#include <vector>

//******************************************************************************
class sc_map_linear_key_range : public sc_map_regular_key_range<sc_map_linear_key>
{
public:
    typedef sc_map_regular_key_range<sc_map_linear_key> base;
    typedef sc_map_key_range::key_type key_type;

    sc_map_linear_key_range();
    sc_map_linear_key_range(key_type start_key, key_type end_key);
    sc_map_linear_key_range(sc_map_key_range<key_type>*, key_type start_key, key_type end_key);
    virtual ~sc_map_linear_key_range() {};

    virtual sc_map_linear_key_range* clone();

    virtual bool next_key(key_type& key) const;
};
