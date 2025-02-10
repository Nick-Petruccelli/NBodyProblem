#include "../inc/n_body.hpp"

int main() {
  NBodySim sim;
  // sim.three_body_init();
  //  sim.rand_init(5);
  sim.file_init("./sim_input/solar.tsv");
  sim.start(200.0, 100000, 200, "./out/sim_data.tsv");
  sim.close();
}
