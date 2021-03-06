#pragma once
#include "SDL.h"
#include "time.h"

class player
{
public:
	void idle(SDL_Surface* clip);
	void walkf(SDL_Surface* clip);
	void walkb(SDL_Surface* clip);
	void punch(SDL_Surface* clip);
	void kick(SDL_Surface* clip);
	void block(SDL_Surface* clip);
	void punched(SDL_Surface* clip);
	void ko(SDL_Surface* clip);
	void knocked(SDL_Surface* clip);
	void player::back_to_idle(void);
	player(void);
	~player(void);

	SDL_Rect offset;
	bool b[8];
	int percent_perversa;
	int Life;
};

