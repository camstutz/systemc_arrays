
#pragma once

#include <systemc.h>

#include "../sc_map/sc_map_linear.hpp"

class source : public sc_module
{
public:
    sc_map_linear<sc_out<bool> > output;

    void create_data();

    source(sc_module_name _name);
    SC_HAS_PROCESS(source);
};
