/*!
 * @file port_array.hpp
 * @author Christian Amstutz
 * @date Feb 11, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <array>
#include <string>

#include <systemc.h>

#include "signal_array.hpp"

// Forward declarations
template<template<class _T> class port_class, class data_type, unsigned int port_count> class port_array;
template<template<class _T> class p_class, class d_type, unsigned int p_count> void sc_trace(sc_trace_file *tf, const port_array<p_class, d_type, p_count>& ports, const std::string& name );

template<template<class _T> class port_class, class data_type, unsigned int port_count>
class port_array {

public:
    typedef port_class<data_type> port_t;
    typedef std::array<port_t*, port_count> port_array_t;

    port_array();
    port_array(const char* name);
    ~port_array();

    void make_sensitive(sc_sensitive& module) const;
    void bind(signal_array<data_type, port_count> signals);
    //void bind(signal_array<data_type, port_count>::signal_t signal, unsigned int pos);
    //todo: void write_all(data_type value);

    typename port_array_t::size_type size() const;
    port_t* operator[](typename port_array_t::size_type pos);
    port_t** begin();
    port_t* const* begin() const;
    port_t** end();
    port_t* const* end() const;

    friend void sc_trace<>(sc_trace_file* tf, const port_array<port_class, data_type, port_count>& ports, const std::string& name );

private:
    port_array_t ports;
};

#include "port_array.cpp"
