#include "devices.h"
#include "cpu_t.h"

void create_devices(CPU* c, Devices* d) {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    fprintf(stderr, "ERROR: failed to initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }

  create_screen(d);
  create_sound(d, "../assets/boing_x.wav");
  create_timer(c, d);
}

void destroy_devices(Devices* d) {
  destroy_screen(d);
  destroy_sound(d);
  destroy_timer(d);
}

void create_screen(Devices* d) {
  d->w = SDL_CreateWindow("chip-8", 
                        SDL_WINDOWPOS_CENTERED, 
                        SDL_WINDOWPOS_CENTERED,
                        WINDOW_WIDTH,
                        WINDOW_HEIGHT,
                        SDL_WINDOW_OPENGL |
                        SDL_WINDOW_RESIZABLE |
                        SDL_WINDOW_SHOWN);

  if (d->w == NULL)  {
    fprintf(stderr, "ERROR: failed to create window: %s\n", SDL_GetError());
    exit(1);
  }

  d->r = SDL_CreateRenderer(d->w, -1, 0);

  if (d->r == NULL) {
    fprintf(stderr, "ERROR: failed to create renderer: %s\n", SDL_GetError());
    exit(1);
  }

  d->t = SDL_CreateTexture(d->r,
                         SDL_PIXELFORMAT_RGB444,
                         SDL_TEXTUREACCESS_STREAMING,
                         SCREEN_WIDTH,
                         SCREEN_HEIGHT);
    
  if (d->t == NULL) {
    fprintf(stderr, "ERROR: failed to create texture: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_SetRenderDrawColor(d->r, 0, 0, 0, 0);
  SDL_RenderClear(d->r);
  SDL_RenderPresent(d->r);   
}

void buffer_graphics(CPU* c, Devices* d) {
  for (int y = 0; y < SCREEN_HEIGHT; y++) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
      uint8_t pixel = c->screen[y][x];
      d->pix_buff[(y * SCREEN_WIDTH) + x] = 0xFFF * pixel;
    }
  }  
}

void draw_graphics(Devices* d) {
  SDL_UpdateTexture(d->t, NULL, d->pix_buff, SCREEN_WIDTH * sizeof(uint16_t));
  SDL_RenderClear(d->r);
  SDL_RenderCopy(d->r, d->t, NULL, NULL);
  SDL_RenderPresent(d->r); 
}

void destroy_screen(Devices* d) {
  SDL_DestroyWindow(d->w);
  SDL_DestroyRenderer(d->r);
  SDL_DestroyTexture(d->t);
  SDL_Quit();
}

void create_sound(Devices* d, char* filename) {
  SDL_AudioSpec sound_spec;
  
  if (SDL_LoadWAV(filename, &sound_spec, &d->sound_buff, &d->sound_len) == NULL) {
    fprintf(stderr, "ERROR: failed to open boing_x.wav: %s\n", SDL_GetError());
    exit(1);
  }

  d->sound_device = SDL_OpenAudioDevice(NULL, 0, &sound_spec, NULL, 0);
  
  if (d->sound_device < 1) {
    fprintf(stderr, "ERROR: failed to open audio device: %s\n", SDL_GetError());
    exit(1);
  }
 
  if (SDL_QueueAudio(d->sound_device, d->sound_buff, d->sound_len) < 0) {
    fprintf(stderr, "ERROR: failed to queue audio: %s\n", SDL_GetError());
  }
}

void update_sound(CPU* c, Devices* d) {
  if (SDL_GetQueuedAudioSize(d->sound_device) < 10) {
    if (SDL_QueueAudio(d->sound_device, d->sound_buff, d->sound_len) < 0) {
      fprintf(stderr, "ERROR: failed to queue audio: %s\n", SDL_GetError());
    }
  }

  if (c->st > 0) {
    SDL_PauseAudioDevice(d->sound_device, 0);
  } else {
    SDL_PauseAudioDevice(d->sound_device, 1);
  }
}

void destroy_sound(Devices* d) {
  SDL_CloseAudioDevice(d->sound_device);
  SDL_FreeWAV(d->sound_buff);
}

void create_timer(CPU* c, Devices* d) {
  d->timer = SDL_AddTimer(1000 / 60, update_timer, c);
}

uint32_t update_timer(uint32_t interval, void* param) {
  CPU* c = (CPU*) param;
  
  if (c->st > 0) {
    c->st -= 1;
  }
  
  if (c->dt > 0) {
    c->dt -= 1;
  }
  
  return interval;
}

void destroy_timer(Devices* d) {
  SDL_RemoveTimer(d->timer);
}
