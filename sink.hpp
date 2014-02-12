
#include <systemc.h>

#include "port_array.hpp"

class sink : public sc_module {
public:
    port_array<sc_in, bool, 3> input;

    void detect_signal();

    sink(sc_module_name _name);
    SC_HAS_PROCESS(sink);
};
