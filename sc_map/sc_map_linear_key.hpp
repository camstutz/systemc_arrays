/*!
 * @file sc_map_linear_key.hpp
 * @author Christian Amstutz
 * @date May 20, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_key_regular_base.hpp"

#include <string>
#include <sstream>

//******************************************************************************

class sc_map_linear_key : public sc_map_key_regular_base
{
public:
    typedef sc_map_key_regular_base::index_type index_type;

    index_type X;

    virtual ~sc_map_linear_key() {};

    virtual bool is_smaller(const sc_map_key_base& compare) const;
    virtual std::string get_string() const;
};
