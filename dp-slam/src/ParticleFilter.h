#include <vector>
#include 'Particle.h'

class ParticleFilter
{
 public:
  ParticleFilter(unsigned int number_of_particles);
  unsigned int getNumberOfParticles();
  
 private:
  unsigned int number_of_particles;
  std::vector<Particle> particles;
  
}
