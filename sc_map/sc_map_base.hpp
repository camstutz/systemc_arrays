/*!
 * @file sc_map_base.hpp
 * @author Christian Amstutz
 * @date May 29, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_iterator.hpp"

#include "../modelsim_support/modelsim_support.hpp"

#include <systemc.h>

#include <vector>
#include <map>
#include <string>
#include <sstream>

//******************************************************************************
template <typename key_T, typename range_T, typename object_T>
class sc_map_base : public sc_object
{
    friend class sc_map_iterator<sc_map_base<key_T, range_T, object_T> >;

public:
    typedef key_T key_type;
    typedef range_T range_type;
    typedef object_T object_type;
    typedef std::map<key_type, object_type*, typename key_type::Comperator> map_type;
    typedef sc_map_iterator<sc_map_base<key_T, range_T, object_T> > iterator;
    typedef ptrdiff_t difference_type;
    typedef typename map_type::size_type size_type;
    typedef object_type* pointer;

    static const char key_separator;
    static const char key_sub_separator;

    sc_map_base(const sc_module_name name);
    virtual ~sc_map_base() {};

    iterator begin();
    iterator end();

    std::pair<bool, key_type> get_key(object_type& object) const;

    //* todo: const version needed?
    object_type& at(const key_type key);
    object_type& operator[] (const key_type key);
    iterator operator()(const key_type& start_key, const key_type& end_key);
    iterator operator()(const range_type& range);

    template <typename signal_type>
    void bind(sc_signal<signal_type>& signal);
    template <typename signal_type>
    void operator()(sc_signal<signal_type>& signal);
    template <typename signal_type>
    void bind(sc_map_base<key_type, range_type, signal_type>& signal_map);
    template <typename signal_type>
    void operator()(sc_map_base<key_type, range_type, signal_type>& signal_map);
    template <typename signal_type>
    void bind(sc_map_iterator<signal_type>& signal_it);
    template <typename signal_type>
    void operator()(sc_map_iterator<signal_type> signal_it);

    template<typename data_type>
    void write(const data_type& value);
// todo: allow operator assignment to multiple ports
//    template<typename data_type>
//    void operator=(const data_type& value);

public:
    map_type objects;
    range_type range;

    template <typename Creator>
    void init(std::vector<key_type> key_vector, Creator object_creator);
    template <typename Creator, typename config_type>
    void init(std::vector<key_type> key_vector, Creator object_creator, const config_type configurator);
    template <typename Creator, typename config_type>
    void init(std::vector<key_type> key_vector, Creator object_creator, std::map<key_type, config_type> configurations);

//* todo: add const to second argument of sc_trace
template <typename trace_key_T, typename trace_range_T, typename trace_object_T>
friend void sc_trace(sc_trace_file* tf, sc_map_base<trace_key_T, trace_range_T, trace_object_T>& sc_map, const std::string& name);

template <typename sens_key_T, typename sens_range_T, typename sens_object_T>
friend sc_sensitive& operator<< (sc_sensitive& sensitivity_list, sc_map_base<sens_key_T, sens_range_T, sens_object_T>& signal_map);

/** Function for tracing support in ModelSim */
#ifdef MODELSIM_COMPILER
    template <typename data_type>
    void register_signal_modelsim();
#endif

};

//******************************************************************************

//******************************************************************************

template <typename key_T, typename range_T, typename object_T>
const char sc_map_base<key_T, range_T, object_T>::key_separator = '_';

template <typename key_T, typename range_T, typename object_T>
const char sc_map_base<key_T, range_T, object_T>::key_sub_separator = '-';

//******************************************************************************

template <typename key_T, typename range_T, typename object_T>
sc_map_base<key_T, range_T, object_T>::sc_map_base(const sc_module_name name) :
        sc_object(name)
{}

//******************************************************************************
template <typename key_T, typename range_T, typename object_T>
template <typename Creator>
void sc_map_base<key_T, range_T, object_T>::init(std::vector<key_type> key_vector,
        Creator object_creator)
{
    for (typename std::vector<key_type>::iterator key_it = key_vector.begin();
         key_it != key_vector.end();
         ++key_it)
    {
        std::string name = basename();
        const char* cname = name.c_str();

        object_type* p = object_creator(cname, *key_it);
        objects.insert(typename map_type::value_type(*key_it, p));
    }

    return;
}

//******************************************************************************
template <typename key_T, typename range_T, typename object_T>
template <typename Creator, typename config_type>
void sc_map_base<key_T, range_T, object_T>::init(std::vector<key_type> key_vector,
        Creator object_creator, const config_type configurator)
{
    for (typename std::vector<key_type>::iterator key_it = key_vector.begin();
         key_it != key_vector.end();
         ++key_it)
    {
        std::string name = basename();
        const char* cname = name.c_str();

        object_type* p = object_creator(cname, *key_it, configurator);
        objects.insert(typename map_type::value_type(*key_it, p));
    }

    return;
}

//******************************************************************************
template <typename key_T, typename range_T, typename object_T>
template <typename Creator, typename config_type>
void sc_map_base<key_T, range_T, object_T>::init(std::vector<key_type> key_vector,
        Creator object_creator, std::map<key_type, config_type> configurations)
{
    for (typename std::vector<key_type>::iterator key_it = key_vector.begin();
         key_it != key_vector.end();
         ++key_it)
    {
        std::string name = basename();
        const char* cname = name.c_str();

        object_type* p = object_creator(cname, *key_it, configurations.at(*key_it));
        objects.push_back(map_type::value_type(*key_it, p));
    }

    return;
}

//******************************************************************************
template <typename key_T, typename range_T, typename object_T>
typename sc_map_base<key_T, range_T, object_T>::iterator
        sc_map_base<key_T, range_T, object_T>::begin()
{
    return iterator(*this);
}

//******************************************************************************
template <typename key_T, typename range_T, typename object_T>
typename sc_map_base<key_T, range_T, object_T>::iterator
        sc_map_base<key_T, range_T, object_T>::end()
{
    return iterator(*this, iterator::end);
}

//******************************************************************************
template <typename key_T, typename range_T, typename object_T>
std::pair<bool, typename sc_map_base<key_T, range_T, object_T>::key_type>
        sc_map_base<key_T, range_T, object_T>::get_key(object_type& object) const
{
    std::pair<bool, key_type> key_pair;
    key_pair.first = false;

    for (typename map_type::const_iterator object_it = objects.begin();
         object_it != objects.end();
         ++object_it)
    {
        if (object_it->second == &object)
        {
            key_pair.first = true;
            key_pair.second = object_it->first;
            break;
        }
    }

    return key_pair;
}

//******************************************************************************
template <typename key_T, typename range_T, typename object_T>
typename sc_map_base<key_T, range_T, object_T>::object_type&
        sc_map_base<key_T, range_T, object_T>::at(const key_type key)
{
    // todo: at exception handling for out range accesses
    object_type& ret_object = *(this->objects[key]);

    return ret_object;
}

//******************************************************************************
template <typename key_T, typename range_T, typename object_T>
typename sc_map_base<key_T, range_T, object_T>::object_type&
        sc_map_base<key_T, range_T, object_T>::operator[] (const key_type key)
{
    return at(key);
}

//******************************************************************************
template <typename key_T, typename range_T, typename object_T>
typename sc_map_base<key_T, range_T, object_T>::iterator
        sc_map_base<key_T, range_T, object_T>::operator()(
        const key_type& start_key, const key_type& end_key)
{
    sc_map_iterator<sc_map_base<key_T, range_T, object_T> > it(*this,
            start_key, end_key);

    return it;
}

//******************************************************************************
template <typename key_T, typename range_T, typename object_T>
typename sc_map_base<key_T, range_T, object_T>::iterator
    sc_map_base<key_T, range_T, object_T>::operator()(const range_type& range)
{
    sc_map_iterator<sc_map_base<key_T, range_T, object_T> > it(*this, range);

    return it;
}

//******************************************************************************
template <typename key_T, typename range_T, typename object_T>
template <typename signal_type>
void sc_map_base<key_T, range_T, object_T>::bind(sc_signal<signal_type>& signal)
{
    for (iterator port_it = begin(); port_it != end(); ++port_it)
    {
        port_it->bind(signal);
    }

    return;
}

//******************************************************************************
template <typename key_T, typename range_T, typename object_T>
template <typename signal_type>
void sc_map_base<key_T, range_T, object_T>::operator()(sc_signal<signal_type>& signal)
{
    bind(signal);

    return;
}

//******************************************************************************
template <typename key_T, typename range_T, typename object_T>
template <typename signal_type>
void sc_map_base<key_T, range_T, object_T>::bind(sc_map_base<key_type,
        range_type, signal_type>& signal_map)
{
    // todo: check range

    iterator port_it = begin();
    iterator port_end = end();
    typename sc_map_base<key_type, range_type, signal_type>::iterator signal_it = signal_map.begin();
    typename sc_map_base<key_type, range_type, signal_type>::iterator signal_end = signal_map.end();

    for (; port_it != port_end; ++port_it)
    {
        port_it->bind(*signal_it);
        ++signal_it;
    }

    return;
}

//******************************************************************************
template <typename key_T, typename range_T, typename object_T>
template <typename signal_type>
void sc_map_base<key_T, range_T, object_T>::operator()(
        sc_map_base<key_type, range_type, signal_type>& signal_map)
{
    bind(signal_map);

    return;
}

//******************************************************************************
template <typename key_T, typename range_T, typename object_T>
template <typename signal_type>
void sc_map_base<key_T, range_T, object_T>::bind(sc_map_iterator<signal_type>& signal_it)
{
    // todo: check for equal size
    // todo: check for same object
    // todo: check for compatibility of port and signal (pre-processor)

    for (sc_map_iterator<sc_map_base<key_T, range_T, object_T> > port_it = this->begin();
         port_it != this->end();
         ++port_it)
    {
        port_it->bind(*signal_it);

        ++signal_it;
    }

    return;
}

//******************************************************************************
template <typename key_T, typename range_T, typename object_T>
template <typename signal_type>
void sc_map_base<key_T, range_T, object_T>::operator()(
        sc_map_iterator<signal_type> signal_it)
{
    bind(signal_it);

    return;
}

//******************************************************************************
template <typename key_T, typename range_T, typename object_T>
template <typename data_type>
void sc_map_base<key_T, range_T, object_T>::write(const data_type& value)
{
    for (iterator object_it = begin(); object_it != end(); ++object_it)
    {
        (*object_it)->write(value);
    }

    return;
}

////******************************************************************************
//template <typename key_T, typename range_T, typename object_T>
//template<typename data_type>
//void sc_map_base<key_T, range_T, object_T>::operator= (const data_type value)
//{
//    write(value);
//
//    return;
//}

//******************************************************************************
template <typename trace_key_T, typename trace_range_T, typename trace_object_T>
void sc_trace(sc_trace_file* tf, sc_map_base<trace_key_T, trace_range_T,
        trace_object_T>& sc_map, const std::string& name)
{
    for (typename sc_map_base<trace_key_T, trace_range_T, trace_object_T>::iterator object_it = sc_map.begin();
         object_it != sc_map.end();
         ++object_it)
    {
        std::stringstream full_name;
        full_name << name
                  << sc_map_base<trace_key_T, trace_range_T, trace_object_T>::key_separator
                  << sc_map.key_string(*object_it);
        sc_trace(tf, *object_it, full_name.str().c_str());
    }

    return;
}

//******************************************************************************
template <typename sens_key_T, typename sens_range_T, typename sens_object_T>
sc_sensitive& operator<< (sc_sensitive& sensitivity_list,
        sc_map_base<sens_key_T, sens_range_T, sens_object_T>& signal_map)
{
    for (typename sc_map_base<sens_key_T, sens_range_T, sens_object_T>::iterator signal_it = signal_map.begin();
         signal_it != signal_map.end();
         ++signal_it)
    {
        sensitivity_list << *signal_it;
    }

    return sensitivity_list;
}

//// *****************************************************************************
//#ifdef MODELSIM_COMPILER
//
//template <typename key_T, typename range_T, typename object_T>
//template <typename data_type>
//void sc_map_base<key_T, range_T, object_T>::register_signal_modelsim()
//{
//    const_container_iterator object_it = objects.begin();
//    for (; object_it != objects.end(); ++object_it)
//    {
//        SC_MTI_REGISTER_CUSTOM_DEBUG(*object_it, data_type::get_max_value_length(), data_type::mti_debug_cb);
//    }
//
//    return;
//}
//
//#endif
