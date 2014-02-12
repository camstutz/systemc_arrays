
#include <systemc.h>

#include "port_array.hpp"

class source : public sc_module {
public:
    port_array<sc_out, bool, 3> output;

    void create_data();

    source(sc_module_name _name);
    SC_HAS_PROCESS(source);
};
