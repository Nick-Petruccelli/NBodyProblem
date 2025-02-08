#include "../inc/n_body.hpp"

int main(){
	NBodySim sim;
	sim.three_body_init();
	sim.start(1.0, 1000, 1, "../out/test.tsv");
	sim.close();
}
