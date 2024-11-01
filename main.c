#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


void draw_flappy(SDL_Renderer* renderer, SDL_Texture *texture, int x, int y) {
	SDL_Rect rect_src = {0, 0, 42, 31};
	SDL_Rect rect_dst = {x, y, 42, 31};
	SDL_RenderCopy(renderer, texture, &rect_src, &rect_dst);
}

int	main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Mon super programme", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_RENDERER_ACCELERATED);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);
	bool is_open = true;
	int	x = 0;
	int	y = 0;

	bool is_right  = false;

	SDL_Surface* flappy = SDL_LoadBMP("./flappy.bmp");

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, flappy); 

	while (is_open) {
		SDL_Event event;
		
		// FPS init (framelimits)
		Uint32 start = SDL_GetPerformanceCounter();
		// Boucle des events
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				int code = event.key.keysym.sym;
				if (code == SDLK_ESCAPE)
					is_open = false;
				if (code == SDLK_RIGHT)
					is_right = true;
			} 
			if (event.type == SDL_KEYUP) {
				int code = event.key.keysym.sym;
				if (code == SDLK_RIGHT)
					is_right = false;
			}
		}
		// dessin
		SDL_RenderClear (renderer);
		if (is_right)
			x += 3;
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_Rect rect = {x, y, 50, 50};
		SDL_RenderDrawRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		draw_flappy(renderer, texture, 50, 50);
		draw_flappy(renderer, texture, 100, 50);
		draw_flappy(renderer, texture, 200, 50);
		draw_flappy(renderer, texture, 300, 50);
		draw_flappy(renderer, texture, 300, 250);

		SDL_RenderPresent(renderer);

		// FPS (Framelimits)
		Uint32 end = SDL_GetPerformanceCounter();
		float Frame = (end - start) / (float) SDL_GetPerformanceFrequency() * 1000.0f;
		SDL_Delay(floor (16.666f - Frame));
	}



	SDL_FreeSurface(flappy);
	SDL_DestroyTexture(texture);

	SDL_DestroyWindow(window);


	SDL_Quit();
	return EXIT_SUCCESS;
}



// Surface =  image dans la ram
//
// Texture = image dans la VRAM (carte graphique)

