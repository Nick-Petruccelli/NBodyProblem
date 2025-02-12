#include "../inc/n_body.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <chrono>

void NBodySim::rand_init(unsigned int n_particles) {
  m_particle_count = n_particles;
  m_particles.mass = (double *)malloc(n_particles * sizeof(double));
  m_particles.x = (double *)malloc(n_particles * sizeof(double));
  m_particles.y = (double *)malloc(n_particles * sizeof(double));
  m_particles.z = (double *)malloc(n_particles * sizeof(double));
  m_particles.vx = (double *)malloc(n_particles * sizeof(double));
  m_particles.vy = (double *)malloc(n_particles * sizeof(double));
  m_particles.vz = (double *)malloc(n_particles * sizeof(double));
  m_particles.fx = (double *)malloc(n_particles * sizeof(double));
  m_particles.fy = (double *)malloc(n_particles * sizeof(double));
  m_particles.fz = (double *)malloc(n_particles * sizeof(double));

  std::uniform_real_distribution<double> unif(0, 10000000000);
  std::default_random_engine re;
  for (unsigned int i = 0; i < n_particles; i++) {
    m_particles.mass[i] = unif(re);
    m_particles.x[i] = unif(re);
    m_particles.y[i] = unif(re);
    m_particles.z[i] = unif(re);
    m_particles.vx[i] = unif(re);
    m_particles.vy[i] = unif(re);
    m_particles.vz[i] = unif(re);
    m_particles.fx[i] = unif(re);
    m_particles.fy[i] = unif(re);
    m_particles.fz[i] = unif(re);
  }
}

void NBodySim::three_body_init() {
  m_particle_count = 3;
  m_particles.mass = (double *)malloc(3 * sizeof(double));
  m_particles.x = (double *)malloc(3 * sizeof(double));
  m_particles.y = (double *)malloc(3 * sizeof(double));
  m_particles.z = (double *)malloc(3 * sizeof(double));
  m_particles.vx = (double *)malloc(3 * sizeof(double));
  m_particles.vy = (double *)malloc(3 * sizeof(double));
  m_particles.vz = (double *)malloc(3 * sizeof(double));
  m_particles.fx = (double *)malloc(3 * sizeof(double));
  m_particles.fy = (double *)malloc(3 * sizeof(double));
  m_particles.fz = (double *)malloc(3 * sizeof(double));

  m_particles.mass[0] = 1.989E27;
  m_particles.x[0] = 0;
  m_particles.y[0] = 0;
  m_particles.z[0] = 0;
  m_particles.vx[0] = 0;
  m_particles.vy[0] = 0;
  m_particles.vz[0] = 0;
  m_particles.fx[0] = 0;
  m_particles.fy[0] = 0;
  m_particles.fz[0] = 0;

  m_particles.mass[1] = 5.972E24;
  m_particles.x[1] = 147.69E6;
  m_particles.y[1] = 0;
  m_particles.z[1] = 0;
  m_particles.vx[1] = 0;
  m_particles.vy[1] = 4.78;
  m_particles.vz[1] = 0;
  m_particles.fx[1] = 0;
  m_particles.fy[1] = 0;
  m_particles.fz[1] = 0;

  m_particles.mass[2] = 7.34767309E22;
  m_particles.x[2] = 147.69E6 + 384400;
  m_particles.y[2] = 0;
  m_particles.z[2] = 0;
  m_particles.vx[2] = 0;
  m_particles.vy[2] = 4.78 + .522;
  m_particles.vz[2] = 0;
  m_particles.fx[2] = 0;
  m_particles.fy[2] = 0;
  m_particles.fz[2] = 0;
}

void NBodySim::file_init(std::filesystem::path path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    std::cerr << "Failed to open input file" << std::endl;
  }

  std::string text;
  std::getline(file, text);
  std::stringstream ss(text);
  std::string data;

  std::getline(ss, data, '\t');
  m_particle_count = std::stod(data);
  m_particles.mass = (double *)malloc(m_particle_count * sizeof(double));
  m_particles.x = (double *)malloc(m_particle_count * sizeof(double));
  m_particles.y = (double *)malloc(m_particle_count * sizeof(double));
  m_particles.z = (double *)malloc(m_particle_count * sizeof(double));
  m_particles.vx = (double *)malloc(m_particle_count * sizeof(double));
  m_particles.vy = (double *)malloc(m_particle_count * sizeof(double));
  m_particles.vz = (double *)malloc(m_particle_count * sizeof(double));
  m_particles.fx = (double *)malloc(m_particle_count * sizeof(double));
  m_particles.fy = (double *)malloc(m_particle_count * sizeof(double));
  m_particles.fz = (double *)malloc(m_particle_count * sizeof(double));
  for (int i = 0; i < m_particle_count; i++) {
    std::getline(ss, data, '\t');
    m_particles.mass[i] = std::stod(data);
    std::getline(ss, data, '\t');
    m_particles.x[i] = std::stod(data);
    std::getline(ss, data, '\t');
    m_particles.y[i] = std::stod(data);
    std::getline(ss, data, '\t');
    m_particles.z[i] = std::stod(data);
    std::getline(ss, data, '\t');
    m_particles.vx[i] = std::stod(data);
    std::getline(ss, data, '\t');
    m_particles.vy[i] = std::stod(data);
    std::getline(ss, data, '\t');
    m_particles.vz[i] = std::stod(data);
    std::getline(ss, data, '\t');
    m_particles.fx[i] = std::stod(data);
    std::getline(ss, data, '\t');
    m_particles.fy[i] = std::stod(data);
    std::getline(ss, data, '\t');
    m_particles.fz[i] = std::stod(data);
  }
}

void NBodySim::start(double dt, unsigned int iterations, unsigned int dump_rate,
                     std::filesystem::path out) {
  m_dt = dt;
  m_iterations = iterations;
  m_dump_rate = dump_rate;

  std::ofstream out_file;
  out_file.open(out, std::ofstream::out | std::ofstream::trunc);
  if (!out_file.is_open()) {
    std::cerr << "Error: Unable to open output file" << std::endl;
    return;
  }

  std::cout << "Starting Simulation" << std::endl;
  auto start = std::chrono::high_resolution_clock::now();
  for (unsigned int i = 0; i < m_iterations; i++) {
    step();
    if (i % m_dump_rate == 0) {
      dump_data(out_file);
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Simulation Time: " << duration.count() << std::endl;
}

void NBodySim::step() {
  for (unsigned int i = 0; i < m_particle_count; i++) {
    set_gravitational_force(i);
    integrate_motion(i);
  }
}

void NBodySim::set_gravitational_force(unsigned int idx) {
  m_particles.fx[idx] = 0;
  m_particles.fy[idx] = 0;
  m_particles.fz[idx] = 0;
  for (unsigned int i = 0; i < m_particle_count; i++) {
    if (i == idx)
      continue;
    double dist = sqrt(pow((m_particles.x[i] - m_particles.x[idx]), 2) +
                       pow((m_particles.y[i] - m_particles.y[idx]), 2) +
                       pow((m_particles.z[i] - m_particles.z[idx]), 2)) +
                  .1;
    double force =
        m_G * (m_particles.mass[i] * m_particles.mass[idx]) / pow(dist, 2);
    m_particles.fx[idx] +=
        force * (m_particles.x[i] - m_particles.x[idx]) / dist;
    m_particles.fy[idx] +=
        force * (m_particles.y[i] - m_particles.y[idx]) / dist;
    m_particles.fz[idx] +=
        force * (m_particles.z[i] - m_particles.z[idx]) / dist;
  }
}

void NBodySim::integrate_motion(unsigned int i) {
  double mass = m_particles.mass[i];
  double ax = m_particles.fx[i] / mass;
  double ay = m_particles.fy[i] / mass;
  double az = m_particles.fz[i] / mass;
  m_particles.vx[i] += ax * m_dt;
  m_particles.vy[i] += ay * m_dt;
  m_particles.vz[i] += az * m_dt;
  m_particles.x[i] += m_particles.vx[i] * m_dt;
  m_particles.y[i] += m_particles.vy[i] * m_dt;
  m_particles.z[i] += m_particles.vz[i] * m_dt;
}

void NBodySim::dump_data(std::ofstream &out_file) {
  out_file << m_particle_count << "\t";
  for (unsigned int i = 0; i < m_particle_count; i++) {
    out_file << m_particles.mass[i] << "\t" << m_particles.x[i] << "\t"
             << m_particles.y[i] << "\t" << m_particles.z[i] << "\t";
    out_file << m_particles.vx[i] << "\t" << m_particles.vy[i] << "\t"
             << m_particles.vz[i] << "\t";
    out_file << m_particles.fx[i] << "\t" << m_particles.fy[i] << "\t"
             << m_particles.fz[i] << "\t";
  }
  out_file << std::endl;
}

void NBodySim::close() {
  free(m_particles.mass);
  free(m_particles.x);
  free(m_particles.y);
  free(m_particles.z);
  free(m_particles.vx);
  free(m_particles.vy);
  free(m_particles.vz);
  free(m_particles.fx);
  free(m_particles.fy);
  free(m_particles.fz);
  std::cout << "Simulation closed." << std::endl;
}
