#include <z_libpd.h>
#include <wavfile.h>

int main(int argc, char **argv) {

    short inbuf[128], outbuf[128];
    FILE * f;
    int i;

    //libpd_add_to_search_path("../sound/externals");
    
    libpd_init();
    libpd_add_to_search_path("./");
    
    libpd_init_audio(2, 2, WAVFILE_SAMPLES_PER_SECOND);
    libpd_set_verbose(1);
    
    if(!libpd_openfile("sawtooth2.pd", "./"))
        return -1;
    f = wavfile_open("./sound.wav");
    
    libpd_start_message(1); // one entry in list
    libpd_add_float(1.0f);
    libpd_finish_message("pd", "dsp");
    
    // short x = 1;
    // unsigned char* p = (unsigned char*)&x;
    // printf("short size: %lu", sizeof(short));
    // printf("first byte: %x", p[0]);
    // printf("second byte: %x", p[1]);

    for (i = 0; i < 4 * WAVFILE_SAMPLES_PER_SECOND / 64; i++) {
        libpd_process_short(1, inbuf, outbuf);
        //printf("%hd\n", outbuf[0]);
        wavfile_write(f,(short *) outbuf,128);
    }
    wavfile_close(f);
}