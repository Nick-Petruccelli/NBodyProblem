#include "../inc/n_body.hpp"

int main(){
	NBodySim sim;
	sim.three_body_init();
	//sim.rand_init(5);
	sim.start(1.0, 100000, 100, "./out/sim_data.tsv");
	sim.close();
}
