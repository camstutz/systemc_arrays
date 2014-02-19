
#include "source.hpp"

//******************************************************************************
source::source(sc_module_name _name) :
        sc_module(_name),
        output(3, 2, "out_port") {

    SC_THREAD(create_data);

    return;
}

//******************************************************************************
void source::create_data() {

    wait(15, SC_NS);

    output.at(0,0).write(true);
    output.at(0,1).write(true);
    output.at(1,0).write(true);

    wait(85, SC_NS);

    output.at(1,1).write(true);
    output.at(2,0).write(true);
    output.at(2,1).write(true);

    wait(100, SC_NS);

    output.at(0,0).write(false);
    output.at(0,1).write(false);
    output.at(1,0).write(false);

    wait(100, SC_NS);

    output.at(1,1).write(false);
    output.at(2,0).write(false);
    output.at(2,1).write(false);

    wait(100, SC_NS);

    output.at(0,1).write(true);
    output.at(1,1).write(false);
    output.at(0,0).write(true);

    wait(100, SC_NS);

    output.at(0,0).write(false);
    output.at(1,1).write(true);
    output.at(2,1).write(true);

    wait(100, SC_NS);

    output.at(1,1).write(true);
    output.at(1,0).write(true);
    output.at(2,0).write(true);

    wait(100, SC_NS);

    return;
}
