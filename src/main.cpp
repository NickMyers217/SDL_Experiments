#include <SDL2/SDL.h>
#include <stdio.h>

const int WIDTH = 800;
const int HEIGHT = 600;

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	bool running = true;
	SDL_Event e;
	SDL_Window *window = SDL_CreateWindow(
		"SDL2",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_SHOWN
	);

	SDL_Renderer * renderer = SDL_CreateRenderer(
		window,
		0,
		SDL_RENDERER_ACCELERATED
	);

	const int RECT = 30;
	const int CELL = 20;

	SDL_Rect rects[RECT * RECT];
	for(int y = 0; y < RECT; y++)
	{
		for(int x = 0; x < RECT; x++)
		{
			int thisRect = y * RECT + x;

			rects[thisRect].x = x * CELL;
			rects[thisRect].y = y * CELL;
			rects[thisRect].w = CELL - 2;
			rects[thisRect].h = CELL - 2;

			//printf("Rect initialized at index => %i\n", thisRect);
			//printf("==> Cordinates: (%i, %i)\n", rects[thisRect].x, rects[thisRect].y);
		}
	}

	while(running)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
			{
				running = false;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderFillRects(renderer, &rects[0], RECT * RECT);
			
		SDL_RenderPresent(renderer);

		for(int i = 0; i < RECT * RECT; i++)
		{
			if(i % 2 == 0)
			{
				rects[i].x++;
				rects[i].y++;
				if(rects[i].x > WIDTH)
					rects[i].x = 0;
				if(rects[i].y > HEIGHT)
					rects[i].y = 0;
			}
			else
			{
				rects[i].x++;
				rects[i].y--;
				if(rects[i].x > WIDTH)
					rects[i].x = 0;
				if(rects[i].y < HEIGHT)
					rects[i].y = 0;
			}
		}

		SDL_Delay(5);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
