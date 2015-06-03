#include "../sc_map/sc_map.hpp"
#include "../sc_map/sc_map_linear/sc_map_linear_key.hpp"
#include "source.hpp"
#include "sink.hpp"

#include <systemc.h>

#include <iostream>
#include "../sc_map/sc_map_list/sc_map_list_key_range.hpp"

int sc_main(int argc, char *agv[])
{
    source src1("source1");

    sink snk1("sink1");

    sc_map_linear<sc_signal<bool> > signals1(4, "signal1");


    src1.output.bind(signals1);
//    src1.output.at(1).bind(signals1[1]);
//    snk1.input[0].bind(signals1[0]);
//    snk1.input[1].bind(signals1[1]);

    std::vector<sc_map_linear_key> key_vector;
    //key_vector.push_back(0);
    key_vector.push_back(1);
    key_vector.push_back(3);
//    sc_map_list_key_range<sc_map_linear_key> list_range(key_vector);
//    snk1.input[0](signals1[0]);
//    snk1.input[2](signals1[2]);
//    snk1.input(list_range).bind(signals1(list_range));
    //snk1.input(1,2).bind(signals1(1,2));
    //snk1.input.bind(sig2_it);
    //snk1.input[3](signals1[3]);

    std::vector<char> keys;
    keys.push_back('A');
    keys.push_back('&');
    keys.push_back('B');
    keys.push_back('C');
    sc_map_list<char, sc_signal<bool> > char_sigs(keys, "char_sig");
    src1.output.bind(char_sigs);
    snk1.input[0].bind(char_sigs['A']);
    sc_map_linear_key start(1);
    sc_map_linear_key end(3);
    sc_map_list_key<char> start1('&');
    sc_map_list_key<char> end1('C');
    snk1.input(start, end).bind(char_sigs(start1,end1));

    for (typename sc_map_list<char, sc_signal<bool> >::iterator csig_it = char_sigs.begin();
         csig_it != char_sigs.end();
         ++csig_it)
    {
        std::cerr << csig_it->name() << std::endl;
    }

    sc_start(1000, SC_NS);

    std::cout << "\n--- Simulation ended ---\n" << std::endl;

    return(0);
}
