#include "../sc_map/sc_map.hpp"
#include "../sc_analyzer/sc_analyzer.hpp"
#include "source.hpp"
#include "sink.hpp"
#include "bind_tester.hpp"

#include "sc_delay_tb.hpp"

#include <systemc.h>

#include <iostream>

int sc_main(int argc, char *agv[])
{
    source src1("source1");
    sc_map_linear<sc_signal<bool> > signals1(2, "signal1");
    sink snk1("sink1");

    sc_map_linear<sc_signal<bool> >::iterator signal_it = signals1.begin();
    //src1.output.bind(signal_it);
    src1.output(0,0).bind(signals1(0,0));
    src1.output(1,1)(signals1(1,1));

    snk1.input.bind(signals1);


    std::cout << "\n--- Simulation starts ---\n" << std::endl;

    sc_start(1000, SC_NS);

    std::cout << "\n--- Simulation ended ---\n" << std::endl;

    return(0);
}
