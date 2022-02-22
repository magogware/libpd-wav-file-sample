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
    
    libpd_start_message(1); // one entry in list
    libpd_add_float(1.0f);
    libpd_finish_message("pd", "dsp");

    for (i = 0; i < 4 * WAVFILE_SAMPLES_PER_SECOND / 64; i++) {
        libpd_process_float(1, NULL, outbuf);
        printf("%f\n", outbuf[0]);
        wavfile_write(f,(short *) outbuf,128);
    }
    wavfile_close(f);
}