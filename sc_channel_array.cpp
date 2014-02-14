/*!
 * @file sc_channel_array.cpp
 * @author Christian Amstutz
 * @date Feb 13, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include "sc_channel_array.hpp"

//******************************************************************************
template<template<class, sc_writer_policy> class channel_type,
        typename data_type, std::size_t channel_count>
sc_channel_array<channel_type, data_type, channel_count>::sc_channel_array()
{
    return;
}

//******************************************************************************
template<template<class, sc_writer_policy> class channel_type,
        typename data_type, std::size_t channel_count>
sc_channel_array<channel_type, data_type, channel_count>::sc_channel_array(
        const char* name) :
        sc_com_array<channel_type<data_type, SC_ONE_WRITER>, channel_count>(
        name)
{
    return;
}
