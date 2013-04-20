#include "snd2.h"
#include <stdio.h>
#include <pthread.h>

int main(int argc, char *argv) {
    pthread_t *t = start_sound_thread();
    set_timestep(100);

    while(1) {
        printf("UNU\n");
        set_channel(0);
        usleep(2000 * 1000);

        printf("DOI\n");
        set_channel(1);
        usleep(2000 * 1000);

        printf("TREI\n");
        set_channel(-1);
        usleep(2000 * 1000);

        set_frequency(2000);
    }

    pthread_join(*t, NULL);

    return 0;
}
