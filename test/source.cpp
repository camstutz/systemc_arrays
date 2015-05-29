
#include "source.hpp"

//******************************************************************************
source::source(sc_module_name _name) :
        sc_module(_name),
        output(4, "out_port") {

    SC_THREAD(create_data);

    return;
}

//******************************************************************************
void source::create_data() {

    wait(15, SC_NS);

    //output.write(true);
    sc_map_linear<sc_out<bool> >::iterator out_it = output.begin();
    out_it = true;

    wait(85, SC_NS);

    output[0].write(false);

    wait(100, SC_NS);

    output.at(0).write(true);
    output.at(1).write(false);

    wait(100, SC_NS);

    output.at(0).write(false);

    return;
}
