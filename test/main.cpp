#include "../sc_map/sc_map.hpp"
#include "source.hpp"
#include "sink.hpp"

#include <systemc.h>

#include <iostream>

int sc_main(int argc, char *agv[])
{
    source src1("source1");

    sink snk1("sink1");

    sc_map_linear<sc_signal<bool> > signals1(4, "signal1");

    src1.output.bind(signals1);
//    src1.output.at(1).bind(signals1[1]);
//    snk1.input[0].bind(signals1[0]);
//    snk1.input[1].bind(signals1[1]);

    snk1.input[0](signals1[0]);
    sc_map_linear_key_range lin_range(1,2);
    sc_map_linear<sc_signal<bool> >::iterator sig2_it = signals1(lin_range);
    snk1.input(1,2).bind(signals1(1,2));
    snk1.input[3](signals1[3]);

    sc_start(1000, SC_NS);

    std::cout << "\n--- Simulation ended ---\n" << std::endl;

    return(0);
}
