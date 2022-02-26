// MarioGameBase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"

using namespace std;

//globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_texture = nullptr;

//function prototypes
bool InitSDL();
void CLoseSDL();
bool Update();
void render();
SDL_Texture* LoadTextureFromFile(string path);
void FreeTexture();

bool InitSDL()
{
	//setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//setup passed so create window
		g_window = SDL_CreateWindow("Game Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_renderer != nullptr)
		{
			//init PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not Initialise. Error: " << IMG_GetError();
				return false;
			}
			//load the background texture
			g_texture = LoadTextureFromFile("Images/test.bmp");
			if (g_texture == nullptr)
			{
				return false;
			}

		}
		else
		{
			cout << "Renderer could not Initialise. Error: " << SDL_GetError();
			return false;
		}
		//did window get created?
		if (g_window == nullptr)
		{
			//window failed
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
	}
}
void CLoseSDL()
{
	//release the window 
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	
	//clear the texture
	FreeTexture();
	//release the renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;
}
bool Update()
{
	//Event handler
	SDL_Event e;

	//get events
	SDL_PollEvent(&e);

	//handle the events
	switch (e.type)
	{
		//click the 'x' to quit
	case SDL_QUIT:
		return true;
		break;
	}
	return false;
}

void render()
{
	//Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	//set where to render the texture
	SDL_Rect renderLocation = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//render to screen
	SDL_RenderCopyEx(g_renderer, g_texture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);

	//update the screen
	SDL_RenderPresent(g_renderer);
}

SDL_Texture* LoadTextureFromFile(string path)
{
	//remove memory used for a previous texture 
	FreeTexture();

	SDL_Texture* p_texture = nullptr;

	//Load the image
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		//create the texture from the pixels on the surface
		p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
		if (p_texture == nullptr)
		{
			cout << "unable to create texture from surface. Error: " << SDL_GetError();
		}
		//remove loaded surface with texture
		SDL_FreeSurface(p_surface);
		
	}
	else
	{
		cout << "unable to create texture from surface. Error: " << IMG_GetError();
	}
	return p_texture;
}

void FreeTexture()
{
	//check if texture exists before removing it
	if (g_texture != nullptr)
	{
		SDL_DestroyTexture(g_texture);
		g_texture = nullptr;
	}
}
int main(int argc, char* args[])
{
	if (InitSDL())
	{
		//flag to check if we wish to quit
		bool quit = false;

		//game loop
		while (!quit)
		{
			render();
			quit = Update();
		}
	}
	CLoseSDL();
	
	return 0;
}
