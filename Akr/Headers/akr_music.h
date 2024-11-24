#include <SDL2/SDL.h>

#ifndef AKINATOR_MUSIC_HEADER
#define AKINATOR MUSIC_HEADER

void StartMusic( SDL_AudioSpec wav_spec, Uint32 wav_length, Uint8 **wav_buffer, SDL_AudioDeviceID* device );
void StopMusic( SDL_AudioDeviceID* device, Uint8 **wav_buffer );

#endif