#include "Drawing_GameFunc.h"
#include <windows.h>
#include "SDL_image.h"

int g_input;
int m_input;
int g_elapsed_time_ms;
int m_max;

SDL_Rect g_bg_source_rect;
SDL_Rect g_bg_destination_rect;
SDL_Texture* g_bg_texture;

SDL_Texture* g_ryu_sheet_texture;
SDL_Rect g_source_rect;
SDL_Rect g_destination_rect;

SDL_Texture* g_char_texture;
SDL_Rect g_char_pos;
SDL_Rect g_destination_pos;


void InitGame() {
	g_input = 0;
	m_input = 0;
	g_flag_running = true;
	m_max = 0;

	// BG
	SDL_Surface* bg_surface = IMG_Load("../../Resources/Sky.jpeg");
	g_bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);

	g_bg_source_rect.x = 0;
	g_bg_source_rect.y = 0;
	g_bg_source_rect.w = 600;
	g_bg_source_rect.h = 800;

	g_bg_destination_rect.x = 0;
	g_bg_destination_rect.y = 0;
	g_bg_destination_rect.w = 600;
	g_bg_destination_rect.h = 800;


	// Plane
	SDL_Surface* ryu_sheet_surface = IMG_Load("../../Resources/FighterPlane.png");
	g_ryu_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, ryu_sheet_surface);
	SDL_FreeSurface(ryu_sheet_surface);

	g_source_rect.x = 0;
	g_source_rect.y = 0;
	g_source_rect.w = 1430;
	g_source_rect.h = 1584;

	g_destination_rect.x = 240;
	g_destination_rect.y = 500;
	g_destination_rect.w = 120;
	g_destination_rect.h = 120;

	//char
	SDL_Surface* g_char_surface = IMG_Load("../../Resources/Missile.png");
	g_char_texture = SDL_CreateTextureFromSurface(g_renderer, g_char_surface);
	SDL_FreeSurface(g_char_surface);

	g_char_pos.x = 0;
	g_char_pos.y = 0;
	g_char_pos.w = 640;
	g_char_pos.h = 1280;

	g_destination_pos.x = g_destination_rect.x - 45;
	g_destination_pos.y = g_destination_rect.y;
	g_destination_pos.w = 32;
	g_destination_pos.h = 64;


	g_elapsed_time_ms = 0;

	
}

void HandleEvents() {
	// Handle Events
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			g_flag_running = false;
		}
		else if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_LEFT) {
				g_input = 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				g_input = 2;
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				g_input = 3;
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				g_input = 4;
			}
			else if (event.key.keysym.sym == SDLK_SPACE) {
				if (m_input == 0) {
					g_destination_pos.x = g_destination_rect.x + 45;
					g_destination_pos.y = g_destination_rect.y;
					m_input = 1;
				}
			}
		}
		else if (event.type == SDL_KEYUP) {
			g_input = 0;
		}
	}
}

void Update() {
	// Update
	if (g_input == 1) {
		g_destination_rect.x -= 10;
	}
	else if (g_input == 2) {
		g_destination_rect.x += 10;
	}
	else if (g_input == 3) {
		g_destination_rect.y -= 10;
	}
	else if (g_input == 4) {
		g_destination_rect.y += 10;
	}


	if (g_destination_rect.x > 480) {
		g_destination_rect.x -= 10;
	}
	else if (g_destination_rect.x < 0) {
		g_destination_rect.x += 10;
	}
	else if (g_destination_rect.y > 680) {
		g_destination_rect.y -= 10;
	}
	else if (g_destination_rect.y < 0) {
		g_destination_rect.y += 10;
	}


	if (m_input == 1) {
		g_destination_pos.y -= 10;
		if (g_destination_pos.y < 0) {
			m_input = 0;
			m_max--;
		}
	}


	g_elapsed_time_ms += 33;
}

void Render() {

	// Background
	SDL_RenderCopy(g_renderer, g_bg_texture, &g_bg_source_rect, &g_bg_destination_rect);

	// Character(미사일)
	if (m_input == 0) {

	}
	else {
		SDL_Rect r = g_destination_pos;
		SDL_RenderCopy(g_renderer, g_char_texture, &g_char_pos, &r);
	
	}

	// g_ryu_sheet_texture(비행기)
	SDL_RenderCopy(g_renderer, g_ryu_sheet_texture, &g_source_rect, &g_destination_rect);


	SDL_RenderPresent(g_renderer);
}

void ClearGame() {
	SDL_DestroyTexture(g_ryu_sheet_texture);
	SDL_DestroyTexture(g_char_texture);
}