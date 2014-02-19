
#pragma once

#include <systemc.h>

#include "sc_map_square.hpp"

class source : public sc_module
{
public:
    std::vector<int> test;
    sc_map_square<sc_out<bool> > output;

    void create_data();

    source(sc_module_name _name);
    SC_HAS_PROCESS(source);
};
