/*!
 * @file sc_map_key_base.hpp
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

#include <string>
#include <functional>
#include <ostream>

//******************************************************************************
class sc_map_key_base
{
public:
    class Comperator : public std::binary_function<sc_map_key_base&, sc_map_key_base&, bool>
    {
        bool operator()(const sc_map_key_base& lhs, const sc_map_key_base& rhs) const;
    };

    virtual ~sc_map_key_base() {};

    virtual bool is_smaller(const sc_map_key_base& compare) const =0;
    virtual std::string get_string() const =0;
};

std::ostream& operator<< (std::ostream& out, const sc_map_key_base& key);
