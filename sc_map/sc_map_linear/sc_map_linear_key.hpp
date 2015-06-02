/*!
 * @file sc_map_linear_key.hpp
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

#include "../sc_map_key_regular.hpp"

#include <string>
#include <sstream>

//******************************************************************************

class sc_map_linear_key : public sc_map_key_regular
{
public:
    typedef sc_map_key_regular::index_type index_type;

    index_type X;

    sc_map_linear_key(index_type X = 0);
    virtual ~sc_map_linear_key() {};

    virtual std::string get_string() const;

    virtual bool operator==(const sc_map_key& other_key) const;
    virtual bool operator<(const sc_map_key& other_key) const;
};
