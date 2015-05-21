/*!
 * @file sc_map_base.hpp
 * @author Christian Amstutz
 * @date May 20, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_iterator.hpp"
#include "sc_map_iter_sequential.hpp"
//#include "sc_map_iter_linear.hpp"
//#include "sc_map_iter_square.hpp"
//#include "sc_map_iter_cube.hpp"
//#include "sc_map_iter_4d.hpp"

#include "../modelsim_support/modelsim_support.hpp"

#include <systemc.h>

#include <vector>
#include <map>
#include <cstddef>
#include <string>
#include <sstream>

//******************************************************************************
template <typename key_T, typename object_T>
class sc_map_base : public sc_object
{
    friend class sc_map_iterator<sc_map_base<key_T, object_T> >;

public:
    typedef key_T key_type;
    typedef object_T object_type;
    typedef std::map<key_type, object_type*> container_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::const_iterator const_container_iterator;
    typedef sc_map_iter_sequential<key_type, object_type> iterator;
    typedef ptrdiff_t difference_type;
    typedef typename container_type::size_type size_type;
    typedef object_type* pointer;
    typedef object_type& reference;

    static const char key_separator;
    static const char key_sub_separator;

    sc_map_base(const sc_module_name name);
    virtual ~sc_map_base() {};

    template <typename Creator>
    void init(std::vector<key_type> key_vector, Creator object_creator);
    template <typename Creator, typename config_type>
    void init(std::vector<key_type> key_vector, Creator object_creator, const config_type configurator);
    template <typename Creator, typename config_type>
    void init(std::vector<key_type> key_vector, Creator object_creator, std::map<key_type, config_type> configurations);

    size_type size();
    iterator begin();
    iterator end();

    std::pair<bool, key_type> get_key(object_type& object) const;
    virtual std::string key_string(object_type& map_element) const = 0;

    template <typename signal_type>
    void bind(sc_signal<signal_type>& signal);
    template <typename signal_type>
    void operator()(sc_signal<signal_type>& signal);
    template <typename signal_type>
    void bind(sc_map_base<key_type, signal_type>& signal_map);
    template <typename signal_type>
    void operator()(sc_map_base<key_type, signal_type>& signal_map);
    template <typename signal_type>
    void bind(sc_map_iterator<signal_type>& signal_it);
    template <typename signal_type>
    void operator()(sc_map_iterator<signal_type>& signal_it);

//    template <typename signal_type>
//    void bind(sc_map_iter_linear<signal_type> signal_it);
//    template <typename signal_type>
//    void operator()(sc_map_iter_linear<signal_type> signal_it);
//    template <typename signal_type>
//    void bind(sc_map_iter_square<signal_type> signal_it);
//    template <typename signal_type>
//    void operator()(sc_map_iter_square<signal_type> signal_it);
//    template <typename signal_type>
//    void bind(sc_map_iter_cube<signal_type> signal_it);
//    template <typename signal_type>
//    void operator()(sc_map_iter_cube<signal_type> signal_it);
//    template <typename signal_type>
//    void bind(sc_map_iter_4d<signal_type> signal_it);
//    template <typename signal_type>
//    void operator()(sc_map_iter_4d<signal_type> signal_it);

    template<typename data_type>
    void write(const data_type& value);
    template<typename data_type>
    void operator= (const data_type& value);

protected:
    container_type objects;

//* todo: add const to second argument of sc_trace
template <typename trace_key_T, typename trace_object_T>
friend void sc_trace(sc_trace_file* tf, sc_map_base<trace_key_T, trace_object_T>& sc_map, const std::string& name);

template <typename trace_key_T, typename trace_object_T>
friend sc_sensitive& operator<< (sc_sensitive& sensitivity_list, sc_map_base<trace_key_T, trace_object_T>& signal_map);

/** Function for tracing support in ModelSim */
#ifdef MODELSIM_COMPILER
    template <typename data_type>
    void register_signal_modelsim();
#endif

};

//******************************************************************************

//******************************************************************************

template <typename key_T, typename object_T>
const char sc_map_base<key_T, object_T>::key_separator = '_';

template <typename key_T, typename object_T>
const char sc_map_base<key_T, object_T>::key_sub_separator = '-';

//******************************************************************************

template <typename key_T, typename object_T>
sc_map_base<key_T, object_T>::sc_map_base(const sc_module_name name) :
        sc_object(name)
{}

//******************************************************************************
template <typename key_T, typename object_T>
template <typename Creator>
void sc_map_base<key_T, object_T>::init(std::vector<key_type> key_vector,
        Creator object_creator)
{
    for (std::vector<key_type>::iterator key_it = key_vector.begin();
         key_it != key_vector.end();
         ++key_it)
    {
        std::string name = basename();
        const char* cname = name.c_str();

        object_type* p = object_creator(cname, *key_it);
        objects.push_back(std::pair(*key_it, p));
    }

    return;
}

//******************************************************************************
template <typename key_T, typename object_T>
template <typename Creator, typename config_type>
void sc_map_base<key_T, object_T>::init(std::vector<key_type> key_vector,
        Creator object_creator, const config_type configurator)
{
    for (std::vector<key_type>::iterator key_it = key_vector.begin();
         key_it != key_vector.end();
         ++key_it)
    {
        std::string name = basename();
        const char* cname = name.c_str();

        object_type* p = object_creator(cname, *key_it, configurator);
        objects.push_back(std::pair(*key_it, p));
    }

    return;
}

//******************************************************************************
template <typename key_T, typename object_T>
template <typename Creator, typename config_type>
void sc_map_base<key_T, object_T>::init(std::vector<key_type> key_vector,
        Creator object_creator, std::map<key_type, config_type> configurations)
{
    for (std::vector<key_type>::iterator key_it = key_vector.begin();
         key_it != key_vector.end();
         ++key_it)
    {
        std::string name = basename();
        const char* cname = name.c_str();

        object_type* p = object_creator(cname, *key_it, configurations.at(*key_it));
        objects.push_back(std::pair(*key_it, p));
    }

    return;
}

//******************************************************************************
template <typename key_T, typename object_T>
typename sc_map_base<key_T, object_T>::size_type sc_map_base<key_T, object_T>::size()
{
    return (objects.size());
}

//******************************************************************************
template <typename key_T, typename object_T>
typename sc_map_base<key_T, object_T>::iterator sc_map_base<key_T, object_T>::begin()
{
    return iterator(*this, 0);
}

//******************************************************************************
template <typename key_T, typename object_T>
typename sc_map_base<key_T, object_T>::iterator sc_map_base<key_T, object_T>::end()
{
    return iterator(*this, objects.size());
}

//******************************************************************************
template <typename key_T, typename object_T>
std::pair<bool, typename sc_map_base<key_T, object_T>::key_type>
        sc_map_base<key_T, object_T>::get_key(object_type& object) const
{
    std::pair<bool, key_type> full_key;
    full_key.first = false;

    typename container_type::const_iterator object_it = objects.begin();
    for (; object_it != objects.end(); ++object_it)
    {
        const object_type* map_object = this->objects[object_it->second];
        if (map_object == &object)
        {
            full_key.first = true;
            full_key.second.X_dim = object_it->first;
            break;
        }
    }

    return full_key;
}

//******************************************************************************
template <typename key_T, typename object_T>
template <typename signal_type>
void sc_map_base<key_T, object_T>::bind(sc_signal<signal_type>& signal)
{
    for (iterator port_it = begin(); port_it != end(); ++port_it)
    {
        port_it->bind(signal);
    }

    return;
}

//******************************************************************************
template <typename key_T, typename object_T>
template <typename signal_type>
void sc_map_base<key_T, object_T>::operator()(sc_signal<signal_type>& signal)
{
    bind(signal);

    return;
}

//******************************************************************************
template <typename key_T, typename object_T>
template <typename signal_type>
void sc_map_base<key_T, object_T>::bind(sc_map_base<key_type,
        signal_type>& signal_map)
{
    // todo: check range

    iterator port_it = begin();
    iterator port_end = end();
    typename sc_map_base<key_type, signal_type>::iterator signal_it = signal_map.begin();
    typename sc_map_base<key_type, signal_type>::iterator signal_end = signal_map.end();

    for (; port_it != port_end; ++port_it)
    {
        port_it->bind(*signal_it);
        ++signal_it;
    }

    return;
}

//******************************************************************************
template <typename key_T, typename object_T>
template <typename signal_type>
void sc_map_base<key_T, object_T>::operator()(
        sc_map_base<key_type, signal_type>& signal_map)
{
    bind(signal_map);

    return;
}

////******************************************************************************
//template <typename key_T, typename object_T>
//template <typename signal_type>
//void sc_map_base<key_T, object_T>::bind(sc_map_iterator<signal_type>& signal_it)
//{
//    // todo: check for equal size
//    // todo: check for same object
//    // todo: check for compatibility of port and signal (pre-processor)
//
//    sc_map_iter_sequential<object_type> port_it = this->begin();
//    for (; port_it != this->end(); ++port_it)
//    {
//        port_it->bind(*signal_it);
//
//        ++signal_it;
//    }
//
//    return;
//}
//
////******************************************************************************
//template <typename key_T, typename object_T>
//template <typename signal_type>
//void sc_map_base<key_T, object_T>::operator()(sc_map_iterator<signal_type>&
//        signal_it)
//{
//    bind(signal_it);
//
//    return;
//}

////******************************************************************************
//template <typename key_T, typename object_T>
//template <typename signal_type>
//void sc_map_base<key_T, object_T>::bind(sc_map_iter_linear<signal_type>
//        signal_it)
//{
//    sc_map_iter_sequential<object_type> port_it = this->begin();
//    for (; port_it != this->end(); ++port_it)
//    {
//        port_it->bind(*signal_it);
//
//        ++signal_it;
//    }
//
//    return;
//}
//
////******************************************************************************
//template <typename key_T, typename object_T>
//template <typename signal_type>
//void sc_map_base<key_T, object_T>::operator() (sc_map_iter_linear<signal_type>
//        signal_it)
//{
//    bind(signal_it);
//
//    return;
//}

////******************************************************************************
//template <typename key_T, typename object_T>
//template <typename signal_type>
//void sc_map_base<key_T, object_T>::bind(sc_map_iter_square<signal_type> signal_it)
//{
//    sc_map_iter_sequential<object_type> port_it = this->begin();
//    for (; port_it != this->end(); ++port_it)
//    {
//        port_it->bind(*signal_it);
//
//        ++signal_it;
//    }
//
//    return;
//}
//
////******************************************************************************
//template <typename key_T, typename object_T>
//template <typename signal_type>
//void sc_map_base<key_T, object_T>::operator() (sc_map_iter_square<signal_type>
//        signal_it)
//{
//    bind(signal_it);
//
//    return;
//}
//
////******************************************************************************
//template <typename key_T, typename object_T>
//template <typename signal_type>
//void sc_map_base<key_T, object_T>::bind(sc_map_iter_cube<signal_type> signal_it)
//{
//    sc_map_iter_sequential<object_type> port_it = this->begin();
//    for (; port_it != this->end(); ++port_it)
//    {
//        port_it->bind(*signal_it);
//
//        ++signal_it;
//    }
//
//    return;
//}
//
////******************************************************************************
//template <typename key_T, typename object_T>
//template <typename signal_type>
//void sc_map_base<key_T, object_T>::operator() (sc_map_iter_cube<signal_type>
//        signal_it)
//{
//    bind(signal_it);
//
//    return;
//}
//
////******************************************************************************
//template <typename key_T, typename object_T>
//template <typename signal_type>
//void sc_map_base<key_T, object_T>::bind(sc_map_iter_4d<signal_type> signal_it)
//{
//    sc_map_iter_sequential<object_type> port_it = this->begin();
//    for (; port_it != this->end(); ++port_it)
//    {
//        port_it->bind(*signal_it);
//
//        ++signal_it;
//    }
//
//    return;
//}
//
////******************************************************************************
//template <typename key_T, typename object_T>
//template <typename signal_type>
//void sc_map_base<key_T, object_T>::operator() (sc_map_iter_4d<signal_type>
//        signal_it)
//{
//    bind(signal_it);
//
//    return;
//}

//******************************************************************************
template <typename key_T, typename object_T>
template <typename data_type>
void sc_map_base<key_T, object_T>::write(const data_type& value)
{
    container_iterator object_it = objects.begin();
    for(; object_it != objects.end(); ++object_it)
    {
        (*object_it)->write(value);
    }

    return;
}

//******************************************************************************
template <typename key_T, typename object_T>
template<typename data_type>
void sc_map_base<key_T, object_T>::operator= (const data_type& value)
{
    write(value);

    return;
}

//******************************************************************************
template <typename trace_key_T, typename trace_object_T>
void sc_trace(sc_trace_file* tf, sc_map_base<trace_key_T,
        trace_object_T>& sc_map, const std::string& name)
{
    typename sc_map_base<trace_key_T, trace_object_T>::iterator object_it = sc_map.begin();
    for (; object_it != sc_map.end(); ++object_it)
    {
        std::stringstream full_name;
        full_name << name
                  << sc_map_base<trace_key_T, trace_object_T>::key_separator
                  << sc_map.key_string(*object_it);
        sc_trace(tf, *object_it, full_name.str().c_str());
    }

    return;
}

//******************************************************************************
template <typename trace_key_T, typename trace_object_T>
sc_sensitive& operator<< (sc_sensitive& sensitivity_list,
        sc_map_base<trace_key_T, trace_object_T>& signal_map)
{
    for ( typename sc_map_base<trace_key_T, trace_object_T>::iterator signal_it = signal_map.begin();
          signal_it != signal_map.end();
          ++signal_it)
    {
        sensitivity_list << *signal_it;
    }

    return sensitivity_list;
}

// *****************************************************************************
#ifdef MODELSIM_COMPILER

template <typename key_T, typename object_T>
template <typename data_type>
void sc_map_base<key_T, object_T>::register_signal_modelsim()
{
    const_container_iterator object_it = objects.begin();
    for (; object_it != objects.end(); ++object_it)
    {
        SC_MTI_REGISTER_CUSTOM_DEBUG(*object_it, data_type::get_max_value_length(), data_type::mti_debug_cb);
    }
    
    return;
}

#endif
