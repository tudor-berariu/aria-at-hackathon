#include 'ParticleFilter.h'

ParticleFilter::ParticleFilter(unsigned int number_of_particles = 100)
{
  this->number_of_particles = number_of_particles;
  std::vector<Particle> particles;
}

unsigned int getNumberOfParticles
{
  return this->number_of_particles;
}
