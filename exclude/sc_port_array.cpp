/*!
 * @file sc_port_array.cpp
 * @author Christian Amstutz
 * @date Feb 13, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include "sc_port_array.hpp"

//******************************************************************************
template<template<class > class port_type,
         typename data_type, std::size_t port_count>
sc_port_array<port_type, data_type, port_count>::sc_port_array()
{
    return;
}

//******************************************************************************
template<template<class > class port_type,
         typename data_type, std::size_t port_count>
sc_port_array<port_type, data_type, port_count>::sc_port_array(
        const char* name) :
        sc_com_array<port_type<data_type>, port_count>(name)
{
    return;
}

//******************************************************************************
template<template<class > class port_type,
         typename data_type, std::size_t port_count>
template<template<typename, sc_writer_policy> class channel_type>
void sc_port_array<port_type, data_type, port_count>::bind(
        sc_channel_array<channel_type, data_type, port_count> &signals)
{
    auto signal_iter = signals.begin();
    auto port_iter = this->begin();
    auto last_port = this->end();

    while (port_iter != last_port)
    {
        (*port_iter)->bind(**signal_iter);
        ++signal_iter;
        ++port_iter;
    }

    return;
}
