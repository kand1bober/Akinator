#include "../Headers/akr_music.h"

void StartMusic( SDL_AudioSpec wav_spec, Uint32 wav_length, Uint8 **wav_buffer, SDL_AudioDeviceID* device )
{
    SDL_LoadWAV("../music1.wav", &wav_spec, wav_buffer, &wav_length);
    *device = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);

    SDL_QueueAudio(*device, *wav_buffer, wav_length);
    SDL_PauseAudioDevice(*device, 0); // Запускаем аудио

    SDL_Delay(1830); // Ожидание (здесь 3 секунды) для завершения воспроизведения
}

void StopMusic( SDL_AudioDeviceID* device, Uint8 **wav_buffer )
{
    SDL_CloseAudioDevice(*device);
    SDL_FreeWAV(*wav_buffer);
    SDL_Quit(); 
}