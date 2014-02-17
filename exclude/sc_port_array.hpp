/*!
 * @file sc_port_array.hpp
 * @author Christian Amstutz
 * @date Feb 13, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <cstddef>

#include <systemc.h>

#include "sc_com_array.hpp"
#include "sc_channel_array.hpp"

template<template<class > class port_type,
         typename data_type, std::size_t port_count>
class sc_port_array : public sc_com_array<port_type<data_type>, port_count>
{

public:
    sc_port_array();
    sc_port_array(const char* name);

    // todo: get channel_type from port_type
    template<template<typename, sc_writer_policy> class channel_type>
    void bind(sc_channel_array<channel_type, data_type, port_count> &signals);

private:

};

#include "sc_port_array.cpp"
