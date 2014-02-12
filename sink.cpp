
#include "sink.hpp"

//******************************************************************************
sink::sink(sc_module_name _name) :
        sc_module(_name),
        input("in_port") {

    SC_THREAD(detect_signal);
        input.make_sensitive(this->sensitive);

    return;
}

//******************************************************************************
void sink::detect_signal() {

    while (1) {
        wait();

        for (auto& in : input) {
            if (in->read() == false) {
                std::cout << sc_time_stamp() << " - " << in->name() << " = 1" << std::endl;
            }
        }
    }

    return;
}
