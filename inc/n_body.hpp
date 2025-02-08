#pragma once

#include <filesystem>
struct particles{
	double* mass;
	double* x;
	double* y;
	double* z;
	double* vx;
	double* vy;
	double* vz;
	double* fx;
	double* fy;
	double* fz;
};

class NBodySim{
public:
	void rand_init(unsigned int n_particles);
	void three_body_init();
	void file_init(std::filesystem::path path);
	void start(double dt, unsigned int iterations, unsigned int dump_rate, std::filesystem::path out);
	void close();
private:
	void step();
	void dump(std::filesystem::path dest);
	void set_gravitational_force(unsigned int i);
	void integrate_motion(unsigned int i);
private:
	double m_G = 6.674E-11;
	unsigned int m_particle_count;
	struct particles m_particles;
	double m_dt;
	unsigned int m_iterations;
	unsigned int m_dump_rate;
};
