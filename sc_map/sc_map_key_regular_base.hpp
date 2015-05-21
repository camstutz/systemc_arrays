/*!
 * @file sc_map_key_regular_base.hpp
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

#include "sc_map_key_base.hpp"

//******************************************************************************
class sc_map_key_regular_base : public sc_map_key_base
{
public:
    typedef int index_type;

    static const index_type default_start_id;

    virtual ~sc_map_key_regular_base() {};

    virtual bool is_smaller(const sc_map_key_base& compare) const =0;
    virtual std::string get_string() const =0;
};
