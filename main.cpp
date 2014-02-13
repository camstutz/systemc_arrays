
#include <iostream>
#include <chrono>

#include <systemc.h>

#include "sc_channel_array.hpp"
#include "source.hpp"
#include "sink.hpp"


int sc_main(int argc, char *agv[]) {

    std::chrono::time_point<std::chrono::system_clock> start, creation, end;
    std::chrono::duration<double> creation_time, simulation_time;

    start = std::chrono::high_resolution_clock::now();

    source src("source");
    sink snk("sink");

    sc_channel_array<sc_signal, bool, 3> signals("test_signal");

    std::cout << "Number of signals: " << signals.size() << std::endl;

    src.output.bind(signals);
    snk.input.bind(signals);

    // **** Setup Tracing
    sc_trace_file* fp;
    fp=sc_create_vcd_trace_file("wave");
    fp->set_time_unit(1, SC_NS);
    sc_trace(fp, signals, "signal");

    std::cout << "\n--- Simulation starts ---\n" << std::endl;

    creation = std::chrono::high_resolution_clock::now();
    sc_start(500, SC_NS);
    end = std::chrono::high_resolution_clock::now();

    std::cout << "\n--- Simulation ended ---\n" << std::endl;

    sc_close_vcd_trace_file(fp);

    creation_time = creation - start;
    simulation_time = end - creation;
    std::cout << "Time for model creation : " << creation_time.count()   << "s" << std::endl;
    std::cout << "Time for simulation     : " << simulation_time.count() << "s" << std::endl;
    std::cout << "Simulated Time          : " << sc_time_stamp() << std::endl;
    std::cout << "Delta Cycles            : " << sc_delta_count() << std::endl;

    return(0);
}
