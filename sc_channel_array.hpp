/*!
 * @file sc_channel_array.hpp
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

#include <systemc.h>

#include "sc_com_array.hpp"

// Forward declarations
//template<class data_type, unsigned int signal_count> class signal_array;
//template<class d_type, unsigned int s_count> void sc_trace(sc_trace_file *tf, const signal_array<d_type, s_count>& signals, const std::string& name );

// todo: change to size_type
template<template<class, sc_writer_policy> class channel_type,
        typename data_type,
        unsigned int channel_count>
class sc_channel_array : public sc_com_array<channel_type<data_type, SC_ONE_WRITER>, channel_count> {

public:

    sc_channel_array();
    sc_channel_array(const char* name);
//    ~sc_object_array();

//    friend void sc_trace<>(sc_trace_file* tf, const signal_array<data_type, signal_count>& signals, const std::string& name );

private:

};

#include "sc_channel_array.cpp"
