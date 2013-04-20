#ifndef SND2_H_
#define SND2_H_

#include <pthread.h>

pthread_t *start_sound_thread();
void set_frequency(int frequency);
void set_timestep(int tstep);
void set_channel(int channel);

#endif
