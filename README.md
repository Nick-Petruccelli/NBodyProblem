# N-Body Problem

Compile and Run:

make (this will compile the binary file)

make run(this will compile and run with defualt settings)

once compiles you can run:
- ./bin/main file <file_path> <iterations> <dt> <dump_rate> <out_file_path> (this will run the sim on a input file in tsv format)
- ./bin/main rand <n_particles> <iteration> <dt> <dump_rate> <out_file_path> (this will run the sim with n random particles)
- ./bin/main three_body <iterations> <dt> <dump_rate> <out_file_path> (this will run the 3 body problem)

Test Outputs:
- solar.tsv iters=5000000 dt=200.0, run_time=46160ms
- rand n_particles=100 iters=10000 dt=1.0, run_time=111ms
- rand n_particles=1000 iters=10000 dt=1.0, run_time=1179134ms
