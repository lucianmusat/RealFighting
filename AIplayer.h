#pragma once
#include "SDL.h"
#include "time.h"

class AIplayer
{
public:
	void idle(SDL_Surface* clip);
	void walkf(SDL_Surface* clip);
	void walkb(SDL_Surface* clip);
	void punch(SDL_Surface* clip);
	void kick(SDL_Surface* clip);
	void punched(SDL_Surface* clip);
	void ko(SDL_Surface* clip);
	void knocked(SDL_Surface* clip);
	void block(SDL_Surface* clip);
	void AIplayer::back_to_idle(void);
	AIplayer(void);
	~AIplayer(void);

	SDL_Rect AIoffset;
	bool AIb[8];
	int AILife;
	//bool knockedout;
	int AIpercent_perversa;
};

