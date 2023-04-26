#ifndef _SETUP_H_
#define _SETUP_H_

//CPU frequency (used for timers)
#define CPU_FREQ 16000000

//Granula will read the output buffer at this sample rate
//and write to the DAC output accordingly.
#define SAMPLE_RATE 21978

//Audio output pin
#define AUDIO_PIN DAC1

//If playing a 20Hz tone at given SAMPLE RATE we would need a buffer of that size
#define MAX_SAMPLE_SIZE (SAMPLE_RATE/20)


#define CONTROLS_POT A0
#define CONTROLS_BT1 A1
#define CONTROLS_BT2 A2
#endif