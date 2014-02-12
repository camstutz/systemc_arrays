
#include "source.hpp"

//******************************************************************************
source::source(sc_module_name _name) :
        sc_module(_name),
        output("out_port") {

    SC_THREAD(create_data);

    return;
}


//******************************************************************************
void source::create_data() {

    wait(15, SC_NS);

    output[0]->write(true);
    output[1]->write(false);
    output[2]->write(true);

    wait(85, SC_NS);

    output[0]->write(false);
    output[1]->write(true);
    output[2]->write(false);

    wait(100, SC_NS);

    output[0]->write(true);
    output[1]->write(false);
    output[2]->write(true);

    wait(100, SC_NS);

    output[0]->write(false);
    output[1]->write(true);
    output[2]->write(false);

    wait(100, SC_NS);

    return;
}
