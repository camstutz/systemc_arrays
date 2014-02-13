
#include <systemc.h>

#include "sc_port_array.hpp"

class source : public sc_module {
public:
    sc_port_array<sc_out, sc_signal, bool, 3> output;

    void create_data();

    source(sc_module_name _name);
    SC_HAS_PROCESS(source);
};
