/*!
 * @file port_array.cpp
 * @author Christian Amstutz
 * @date Feb 11, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include "port_array.hpp"

//******************************************************************************
template<template<class _T> class port_class,
        class data_type,
        unsigned int port_count>
port_array<port_class, data_type, port_count>::port_array() {

    for(port_t*& port : ports) {
        port = new port_t();
    }

    return;
}

//******************************************************************************
template<template<class _T> class port_class,
        class data_type,
        unsigned int port_count>
port_array<port_class, data_type, port_count>::port_array(const char* name) {

    unsigned int id = 0;
    for(port_t*& port : ports) {
        std::string full_name = name + std::to_string(id);
        port = new port_t(full_name.c_str());
        ++id;
    }

    return;
}

//******************************************************************************
template<template<class _T> class port_class,
        class data_type,
        unsigned int port_count>
port_array<port_class, data_type, port_count>::~port_array() {

    // todo: is deletion of ports necessary?

    return;
}

//******************************************************************************
template<template<class _T> class port_class,
        class data_type,
        unsigned int port_count>
void port_array<port_class, data_type, port_count>::make_sensitive(
        sc_sensitive& sensitive_list) const {

    // todo: change it to a traditional way of sensitivity lists
    for (port_t* port : ports) {
        sensitive_list << port->pos();
    }

    return;
}


//******************************************************************************
template<template<class _T> class port_class,
        class data_type,
        unsigned int port_count>
void port_array<port_class, data_type, port_count>::bind(
        signal_array<data_type,
        port_count> signals) {

    auto signal_iter = signals.begin();
    auto port_iter = ports.begin();

    while ( (signal_iter != signals.end()) | (port_iter != ports.end()) ) {
        (*port_iter)->bind(**signal_iter);
        ++signal_iter;
        ++port_iter;
    }

    return;
}

//******************************************************************************
template<template<class _T> class port_class,
        class data_type,
        unsigned int port_count>
typename port_array<port_class, data_type, port_count>::port_array_t::size_type
        port_array<port_class, data_type, port_count>::size() const {

    return(ports.size());
}

//******************************************************************************
template<template<class _T> class port_class,
        class data_type,
        unsigned int port_count>
typename port_array<port_class, data_type, port_count>::port_t*
        port_array<port_class, data_type, port_count>::operator[](
        typename port_array_t::size_type pos) {

    return(ports[pos]);
}

//******************************************************************************
template<template<class _T> class port_class,
        class data_type,
        unsigned int port_count>
typename port_array<port_class, data_type, port_count>::port_t**
        port_array<port_class, data_type, port_count>::begin() {

    return(ports.size()>0 ? ports.begin() : nullptr);
}

//******************************************************************************
template<template<class _T> class port_class,
        class data_type,
        unsigned int port_count>
typename port_array<port_class, data_type, port_count>::port_t* const *
        port_array<port_class, data_type, port_count>::begin() const {

    return(ports.size()>0 ? ports.begin() : nullptr);
}

//******************************************************************************
template<template<class _T> class port_class,
        class data_type,
        unsigned int port_count>
typename port_array<port_class, data_type, port_count>::port_t**
        port_array<port_class, data_type, port_count>::end() {

    return(ports.size()>0 ? ports.end() : nullptr);
}

//******************************************************************************
template<template<class _T> class port_class,
        class data_type,
        unsigned int port_count>
typename port_array<port_class, data_type, port_count>::port_t* const *
        port_array<port_class, data_type, port_count>::end() const {

    return(ports.size()>0 ? ports.end() : nullptr);
}

//******************************************************************************
template<template<class _T> class p_class, class d_type, unsigned int p_count>
void sc_trace(
        sc_trace_file *tf,
        const port_array<p_class, d_type, p_count>& ports,
        const std::string& name ) {

    // todo: test sc_trace in signal_array
    unsigned int id = 0;
    for (typename port_array<p_class, d_type, p_count>::sig_type* signal : ports) {
        sc_trace(tf, *signal, name + std::to_string(id));
        ++id;
    }

    return;
}
