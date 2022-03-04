#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>
using namespace std;
Texture2D::Texture2D(SDL_Renderer* renderer)
{
	//free up memory
	Free();

	m_renderer = nullptr;
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}

bool Texture2D::LoadFromFile(std::string path)
{

}
void Texture2D::Free()
{

}
void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, double angle)
{

}
int Texture2D::GetWidth() { return m_width; }
int Texture2D::GetHeight() { return m_height; }