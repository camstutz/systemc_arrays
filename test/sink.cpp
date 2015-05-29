
#include "sink.hpp"

//******************************************************************************
sink::sink(sc_module_name _name) :
        sc_module(_name),
        input(4, "in_port")
{
    SC_THREAD(detect_signal);
        sensitive << input;

    return;
}

//******************************************************************************
void sink::detect_signal()
{
    while (1) {
        wait();
        sc_map_linear<sc_in<bool> >::iterator in_it = input.begin();
        for (; in_it != input.end(); ++in_it)
        {
            if (in_it->read() == true) {
                std::cout << sc_time_stamp() << " - " << in_it->name() << " = 1" << std::endl;
            }
        }
    }

    return;
}
