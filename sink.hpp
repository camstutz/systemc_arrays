
#include <systemc.h>

#include "sc_map_square.hpp"

class sink : public sc_module {
public:
    sc_map_square<sc_in<bool>> input;

    void detect_signal();

    sink(sc_module_name _name);
    SC_HAS_PROCESS(sink);
};
