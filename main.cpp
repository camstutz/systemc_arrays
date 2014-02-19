
#include <iostream>
#include <chrono>

#include <systemc.h>

#include "sc_map_linear.hpp"
#include "sc_map_square.hpp"
#include "source.hpp"
#include "sink.hpp"


int sc_main(int argc, char *agv[])
{
    std::chrono::time_point<std::chrono::system_clock> start, creation, end;
    std::chrono::duration<double> creation_time, simulation_time;

    start = std::chrono::high_resolution_clock::now();

    sc_map_linear<sc_signal<bool> > test_sig(2);
    test_sig[0].name();
    test_sig[1].name();

    source src("source");
    sink snk("sink");

    sc_map_square<sc_signal<bool> > signals(3, 2, "test_signal");

    std::cout << "Number of signals: " << signals.size()
              << " (" << signals.size_Y() << "/" << signals.size_X() << ")" << std::endl;

    src.output.bind(signals);
    snk.input.bind(signals);

    // **** Setup Tracing
    sc_trace_file* fp;
    fp=sc_create_vcd_trace_file("wave");
    fp->set_time_unit(1, SC_NS);

    sc_trace(fp, signals, "signal");

    std::cout << "\n--- Simulation starts ---\n" << std::endl;

    creation = std::chrono::high_resolution_clock::now();
    sc_start(1000, SC_NS);
    end = std::chrono::high_resolution_clock::now();

    std::cout << "\n--- Simulation ended ---\n" << std::endl;

    sc_close_vcd_trace_file(fp);

    creation_time = creation - start;
    simulation_time = end - creation;
    std::cout << "Time to create model : " << creation_time.count()   << "s" << std::endl;
    std::cout << "Time to simulate     : " << simulation_time.count() << "s" << std::endl;
    std::cout << "Simulated Time       : " << sc_time_stamp() << std::endl;
    std::cout << "Delta Cycles         : " << sc_delta_count() << std::endl;

    return(0);
}
