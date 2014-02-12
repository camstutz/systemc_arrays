/*!
 * @file signal_array.cpp
 * @author Christian Amstutz
 * @date Feb 11, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include "signal_array.hpp"

//******************************************************************************
template<class data_type, unsigned int signal_count>
signal_array<data_type, signal_count>::signal_array() {

    for(signal_t*& signal : signals) {
        signal = new signal_t();
    }

    return;
}

//******************************************************************************
template<class data_type, unsigned int signal_count>
signal_array<data_type, signal_count>::signal_array(const char* name) {

    unsigned int id = 0;
    for(signal_t*& signal : signals) {
        std::string full_name = name + std::to_string(id);
        signal = new signal_t(full_name.c_str());
        ++id;
    }

    return;
}

//******************************************************************************
template<class data_type, unsigned int signal_count>
signal_array<data_type, signal_count>::~signal_array() {

    // todo: is deletion of signals necessary?

    return;
}

//******************************************************************************
template<class data_type, unsigned int signal_count>
        void signal_array<data_type, signal_count>::make_sensitive(
        sc_sensitive sensitive_list) const {

    // todo: change it to a traditional way
    for (signal_t* signal : signals) {
        sensitive_list << signal->pos();
    }

    return;
}

//******************************************************************************
template<class data_type, unsigned int signal_count>
typename signal_array<data_type, signal_count>::signal_array_t::size_type
        signal_array<data_type, signal_count>::size() const {

    return(signals.size());
}

//******************************************************************************
template<class data_type, unsigned int signal_count>
typename signal_array<data_type, signal_count>::signal_t*
        signal_array<data_type, signal_count>::operator[](unsigned int i) {

    return(signals[i]);
}

//******************************************************************************
template<class data_type, unsigned int signal_count>
typename signal_array<data_type, signal_count>::signal_t**
        signal_array<data_type, signal_count>::begin() {

    return(signals.size()>0 ? signals.begin() : nullptr);
}

//******************************************************************************
template<class data_type, unsigned int signal_count>
typename signal_array<data_type, signal_count>::signal_t* const *
        signal_array<data_type, signal_count>::begin() const {

    return(signals.size()>0 ? signals.begin() : nullptr);
}

//******************************************************************************
template<class data_type, unsigned int signal_count>
typename signal_array<data_type, signal_count>::signal_t**
        signal_array<data_type, signal_count>::end() {

    return(signals.size()>0 ? signals.end() : nullptr);
}

//******************************************************************************
template<class data_type, unsigned int signal_count>
typename signal_array<data_type, signal_count>::signal_t* const *
        signal_array<data_type, signal_count>::end() const {

    return(signals.size()>0 ? signals.end() : nullptr);
}

//******************************************************************************
template<class d_type, unsigned int s_count>
void sc_trace(
        sc_trace_file *tf,
        const signal_array<d_type, s_count>& signals,
        const std::string& name ) {

    // todo: test sc_trace in signal_array
    unsigned int id = 0;
    for (typename signal_array<d_type, s_count>::signal_t* signal : signals) {
        sc_trace(tf, *signal, name + std::to_string(id));
        ++id;
    }

    return;
}
