
#include <systemc.h>

#include "sc_port_array.hpp"

class sink : public sc_module {
public:
    sc_port_array<sc_in, sc_signal, bool, 3> input;

    void detect_signal();

    sink(sc_module_name _name);
    SC_HAS_PROCESS(sink);
};
