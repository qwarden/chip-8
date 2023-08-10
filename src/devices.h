#ifndef _DEVICES_H_
#define _DEVICES_H_

#include "cpu_t.h"

typedef struct {
  SDL_Window* w;
  SDL_Renderer* r;
  SDL_Texture* t;
  uint16_t pix_buff[(SCREEN_HEIGHT * SCREEN_WIDTH) * sizeof(uint16_t)];
  uint8_t* sound_buff;
  uint32_t sound_len;
  SDL_AudioDeviceID sound_device;
  SDL_TimerID timer;
} Devices;

void create_devices(CPU* c, Devices* d);
void destroy_devices(Devices* d);

void create_screen(Devices* d);
void buffer_graphics(CPU* c, Devices* d);
void draw_graphics(Devices* d);
void destroy_screen(Devices* d);

void create_sound(Devices* d, char* filename);
void update_sound(CPU* c, Devices* d);
void destroy_sound(Devices* d);

void create_timer(CPU* c, Devices* d);
uint32_t update_timer(uint32_t interval, void* param);
void destroy_timer(Devices* );

#endif // _DEVICES_H_
