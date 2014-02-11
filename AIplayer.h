#pragma once
#include "SDL.h"
#include "time.h"
#include <cstdlib>

class AIplayer
{
public:
	void idle(SDL_Surface* clip);
	void walkf(SDL_Surface* clip);
	void walkb(SDL_Surface* clip);
	void punch(SDL_Surface* clip);
	void kick(SDL_Surface* clip);
	void punched(SDL_Surface* clip);
	void AIplayer::back_to_idle(void);
	AIplayer(void);
	~AIplayer(void);

	SDL_Rect AIoffset;
	bool AIb[5];
	int AILife;
};

