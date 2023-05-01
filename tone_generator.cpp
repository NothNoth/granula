#include "tone_generator.h"
#include "setup.h"
#include "ntm.h"

void extrapolate(unsigned char *src, int src_size, unsigned char *dest, int dest_size);


unsigned int tone_generate_square(unsigned char*buffer, unsigned short frequency) {
  int i;

  //Since we're playing at given sample rate, we will be using sample_size space on the buffer
  unsigned int sample_size = SAMPLE_RATE / frequency;
  if (sample_size > MAX_SAMPLE_SIZE) {
    debug_print("sample buffer seems to small");
    return 0;
  }

  memset(buffer, 0x00, sample_size/2);
  memset(buffer+sample_size/2, 0xFF, sample_size/2);
  return sample_size;
}


unsigned int tone_generate_saw(unsigned char*buffer, unsigned short frequency) {
  int i;

  //Since we're playing at given sample rate, we will be using sample_size space on the buffer
  unsigned int sample_size = SAMPLE_RATE / frequency;
  if (sample_size > MAX_SAMPLE_SIZE) {
    debug_print("sample buffer seems to small");
    return 0;
  }

  memset(buffer, 0x00, sample_size);
  float increment = 255.0/(float)sample_size;
  for (i = 0; i < sample_size; i++) {
    buffer[i] = (unsigned char)((float)(i)*increment);
  }

  return sample_size;
}


unsigned int tone_generate_triangle(unsigned char*buffer, unsigned short frequency) {
  int i;

  //Since we're playing at given sample rate, we will be using sample_size space on the buffer
  unsigned int sample_size = SAMPLE_RATE / frequency;
  if (sample_size > MAX_SAMPLE_SIZE) {
    debug_print("sample buffer seems to small");
    return 0;
  }

  memset(buffer, 0x00, sample_size);
  float increment = 2*255.0/(float)sample_size;
  for (i = 0; i < sample_size/2; i++) {
    buffer[i] = (unsigned char)((float)(i)*increment);
  }
  for (i = 0; i < sample_size/2; i++) {
    buffer[i + sample_size/2] = (unsigned char)(255.0 - (float)(i)*increment);
  }
  return sample_size;
}

unsigned int tone_generate_sin(unsigned char*buffer, unsigned short frequency) {
  int i;

  //Since we're playing at given sample rate, we will be using sample_size space on the buffer
  unsigned int sample_size = SAMPLE_RATE / frequency;
  if (sample_size > MAX_SAMPLE_SIZE) {
    debug_print("sample buffer seems to small");
    return 0;
  }

  memset(buffer, 0x00, sample_size);
  for (i = 0; i < sample_size; i++) {
    buffer[i] = sin(i*2*3.1416/sample_size) * 128 + 128;//scale and center
  }

  return sample_size;
}

unsigned int tone_generate_custom(unsigned char*buffer, unsigned char*custom_wave, unsigned int custom_wave_size, unsigned short frequency) {
  int i;

  //Since we're playing at given sample rate, we will be using sample_size space on the buffer
  unsigned int sample_size = SAMPLE_RATE / frequency;
  if (sample_size > MAX_SAMPLE_SIZE) {
    debug_print("sample buffer seems to small");
    return 0;
  }

  memset(buffer, 0x00, sample_size);

  //Now map custom_wave of size custom_wave_size
  // to buffer of size sample_size

  extrapolate(custom_wave, custom_wave_size, buffer, sample_size);

  return sample_size;
}

void extrapolate(unsigned char *src, int src_size, unsigned char *dest, int dest_size) {
  int i;

  memset(dest, 0x00, dest_size);

  if (dest_size > src_size) {
    float scale = dest_size/src_size;

    for (int i = 0; i < src_size; i++) {
      int idx = i*scale;
      for (int j = 0; j < scale; j++) {
        dest[idx+j] = src[i];
      }
    }
  } else {
    float scale = (float)src_size/(float)dest_size;
    for (i = 0; i < dest_size; i++) {
      int idx = (int)(scale * (float)(i));
      dest[i] = src[idx];
    }
/*
    float scale = (float)src_size/(float)dest_size;
    for (i = 0; i < dest_size; i++) {
      int start_idx = (int)(scale * (float)(i));
      int end_idx = (int)(scale * (float)(i+1));
      int tot = 0;
      for (int j = start_idx; j < end_idx; j++) {
        tot += src[j];
      }
      char plop[64];
      sprintf(plop, "%d: %d->%d / tot %d value: %d\n", i, start_idx, end_idx, tot, (int)((float)(tot)/(float)(end_idx - start_idx)));
      debug_print(plop);
      dest[i] = (int)((float)(tot)/(float)(end_idx - start_idx));
    }
    */
  }
}