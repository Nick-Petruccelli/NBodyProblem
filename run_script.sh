#!/bin/sh
make
./bin/main file sim_input/solar.tsv 5000000 200.0 200 out/solar_5000000_200.tsv
./bin/main rand 10 10000 1.0 100 out/rand_10_10000_1.tsv
./bin/main rand 1000 10000 1.0 100 out/rand_1000_10000_1.tsv

