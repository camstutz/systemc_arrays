/*!
 * @file sc_map_linear_key.cpp
 * @author Christian Amstutz
 * @date May 20, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "sc_map_linear_key.hpp"

//******************************************************************************
bool sc_map_linear_key::is_smaller(const sc_map_key_base& other_key)
        const
{
    sc_map_linear_key* other_key_linear = dynamic_cast<sc_map_linear_key>(other_key);
    if (other_key_linear)
    {
        if (X < other_key_linear->X)
        {
            return true;
        }
    }

    return false;
}

//******************************************************************************
std::string sc_map_linear_key::get_string() const
{
    std::stringstream collection_stream = "";
    collection_stream << X;

    return collection_stream;
}
