#include <z_libpd.h>
#include <wavfile.h>

int main(int argc, char **argv) {

    float outbuf[128];
    FILE * f;
    int i;

    libpd_init();
    libpd_init_audio(0, 2, WAVFILE_SAMPLES_PER_SECOND);
    
    if(!libpd_openfile("sawtooth.pd", "./"))
        return -1;
    f = wavfile_open("sound.wav");

    for (i = 0; i < 4 * WAVFILE_SAMPLES_PER_SECOND / 64; i++) {
        libpd_process_float(1, NULL, outbuf);
        wavfile_write(f,(short *) outbuf,128);
    }
    wavfile_close(f);
}