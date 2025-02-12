#include "../inc/n_body.hpp"
#include <cstring>
#include <cassert>
#include <string>
#include <iostream>


int main(int argc, char* argv[]) {
  NBodySim sim;
  unsigned int n_iters;
  unsigned int dump_rate;
  double dt;
  bool initialized = false;
  char* out_file;
  if(argc == 1){
    sim.file_init("./sim_input/solar.tsv");
    n_iters = 100000;
    dt = 200.0;
    dump_rate = 200;
    initialized = true;
    out_file = (char*)"./out/sim_data.tsv";
  }else{
    char* type = argv[1];
    if(strncmp(type, "rand", 4) == 0){
      assert(argc == 7);
      sim.rand_init(atoi(argv[2]));
      n_iters = atoi(argv[3]);
      dt = std::stod(argv[4]);
      dump_rate = atoi(argv[5]);
      out_file = argv[6];
      initialized = true;
    }else if(strncmp(type, "file", 4) == 0){
      assert(argc == 7);
      sim.file_init(argv[2]);
      n_iters = atoi(argv[3]);
      dt = std::stod(argv[4]);
      dump_rate = atoi(argv[5]);
      out_file = argv[6];
      initialized = true;
    }else if(strncmp(type, "three_body", 4) == 0){
      assert(argc == 6);
      sim.three_body_init();
      n_iters = atoi(argv[2]);
      dt = std::stod(argv[3]);
      dump_rate = atoi(argv[4]);
      out_file = argv[5];
      initialized = true;
    }
  }

  assert(initialized);
  sim.start(dt, n_iters, dump_rate, out_file);
  sim.close();
}
