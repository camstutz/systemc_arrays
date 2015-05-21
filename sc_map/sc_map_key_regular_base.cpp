/*!
 * @file sc_map_key_regular_base.cpp
 * @author Christian Amstutz
 * @date May 20, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "sc_map_key_base.hpp"

//******************************************************************************
std::ostream& operator<< (std::ostream &out, sc_map_key_base &key)
{
    out << key.get_string();

    return out;
}

