/*!
 * @file signal_array.hpp
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

// Forward declarations
template<class data_type, unsigned int signal_count> class signal_array;
template<class d_type, unsigned int s_count> void sc_trace(sc_trace_file *tf, const signal_array<d_type, s_count>& signals, const std::string& name );

template<class data_type, unsigned int signal_count>
class signal_array {

public:
    typedef sc_signal<data_type> signal_t;
    typedef std::array<signal_t*, signal_count> signal_array_t;

    signal_array();
    signal_array(const char* name);
    ~signal_array();

    void make_sensitive(sc_sensitive module) const;
    //todo: void write_all(data_type value);

    typename signal_array_t::size_type size() const;
    signal_t* operator[](unsigned int i);
    signal_t** begin();
    signal_t* const* begin() const;
    signal_t** end();
    signal_t* const* end() const;

    friend void sc_trace<>(sc_trace_file* tf, const signal_array<data_type, signal_count>& signals, const std::string& name );

private:
    signal_array_t signals;
};

#include "signal_array.cpp"
