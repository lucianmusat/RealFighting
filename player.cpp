#include "player.h"
#include "SDL.h"
#include "time.h"

	SDL_Surface *player1_idle, *player1_walkf, *player1_walkb, *player1_punch1, *player1_punch2, *player1_punch3, *player1_shut, *player1_shut2, *player1_block;
	SDL_Rect offset;
	int frame_idle, frame_walkf, frame_walkb, frame_punch1, frame_punch2, frame_punch3, frame_kick, frame_shut2, frame_block;
	SDL_Rect frames_idle[10];
	SDL_Rect frames_walkf[11];
	SDL_Rect frames_walkb[11];
	SDL_Rect frames_punch1[12];
	SDL_Rect frames_punch2[8];
	SDL_Rect frames_punch3[11];
	SDL_Rect frames_kick[6];
	SDL_Rect frames_shut2[9];
	SDL_Rect frames_block[4];
	int aux, aux1 = 0;
	bool other_action = false;
	bool punching = false;
	bool shpitzing = false;
	int number = 0;
	int slowtimes = 3;
	int percent_perversa;
	bool b[5] = {0,0,0,0,0};

void setrects_idle(SDL_Rect* clip)
{
        for(int i = 0; i < 12; i ++) {
                clip[i].x = 0 + i*224;
                clip[i].y = 0;
                clip[i].w = 224;
                clip[i].h = 226;
        }
}

void setrects_walkf(SDL_Rect* clip)
{
        for(int i = 0; i < 11; i ++) {
                clip[i].x = 0 + i*224;
                clip[i].y = 0;
                clip[i].w = 224;
                clip[i].h = 226;
        }
}

void setrects_walkb(SDL_Rect* clip)
{
        for(int i = 0; i < 11; i ++) {
                clip[i].x = 0 + i*224;
                clip[i].y = 0;
                clip[i].w = 224;
                clip[i].h = 226;
        }
}

void setrects_punch1(SDL_Rect* clip)
{
        for(int i = 0; i < 12; i ++) {
                clip[i].x = 0 + i*260;
                clip[i].y = 0;
                clip[i].w = 260;
                clip[i].h = 226;
        }
}

void setrects_punch2(SDL_Rect* clip)
{
        for(int i = 0; i < 8; i ++) {
                clip[i].x = 0 + i*260;
                clip[i].y = 0;
                clip[i].w = 260;
                clip[i].h = 226;
        }
}

void setrects_punch3(SDL_Rect* clip)
{
        for(int i = 0; i < 11; i ++) {
                clip[i].x = 0 + i*260;
                clip[i].y = 0;
                clip[i].w = 260;
                clip[i].h = 226;
        }
}

void setrects_kick(SDL_Rect* clip)
{
        for(int i = 0; i < 6; i ++) {
                clip[i].x = 0 + i*260;
                clip[i].y = 0;
                clip[i].w = 260;
                clip[i].h = 226;
        }
}

void setrects_shut2(SDL_Rect* clip)
{
        for(int i = 0; i < 9; i ++) {
                clip[i].x = 0 + i*226;
                clip[i].y = 0;
                clip[i].w = 226;
                clip[i].h = 226;
        }
}

void setrects_block(SDL_Rect* clip)
{
        for(int i = 0; i < 4; i ++) {
                clip[i].x = 0 + i*156;
                clip[i].y = 0;
                clip[i].w = 156;
                clip[i].h = 226;
        }
}

void player::idle(SDL_Surface* screen)
{	
	if (!other_action)
	{
		SDL_BlitSurface(player1_idle, &frames_idle[static_cast<int>(frame_idle)], screen, &offset);

		if(frame_idle > 8) 
		{
			frame_idle = 0;
		}
		else
		{
			aux++;
			if (aux == slowtimes)
			{
				frame_idle ++;
				aux=0;
			}
		} 

	}
}

void player::walkf(SDL_Surface* screen)
{	
	other_action = true;
	if (offset.x < screen->w - 226)
		offset.x+= 3;

	SDL_BlitSurface(player1_walkf, &frames_walkf[static_cast<int>(frame_walkf)], screen, &offset);

	//SDL_Flip(screen);

	if(frame_walkf > 9) 
	{
	    frame_walkf = 0;
    }
	else
	{
		aux++;
		if (aux == slowtimes)
		{
			frame_walkf ++;
			aux=0;
		}
	}
}

void player::walkb(SDL_Surface* screen)
{	
	other_action = true;
	offset.x-= 3;
	SDL_BlitSurface(player1_walkb, &frames_walkb[static_cast<int>(frame_walkb)], screen, &offset);

	//SDL_Flip(screen);

	if(frame_walkb > 9) 
	{
	    frame_walkb = 0;
    }
	else
	{
		aux++;
		if (aux == slowtimes)
		{
			frame_walkb ++;
			aux=0;
		}
	}
}

void player::punch(SDL_Surface* screen)
{		

	if ((frame_punch1 == 0)&&(frame_punch2 == 0)&&(frame_punch3 == 0)&&(!punching))
	{	
		srand(time(NULL)+number);
		number = rand() % 3;
		//fprintf(stdout, "Random number: %d \n", number);
	}

	other_action = true;
	punching = true;

	if (number == 0)
	{
			SDL_BlitSurface(player1_punch1, &frames_punch1[static_cast<int>(frame_punch1)], screen, &offset);

			if(frame_punch1 > 10) 
			{
				frame_punch1 = 0;
				punching = false;
				b[2]=0;
			}
			else
			{
				aux++;
				if (aux == slowtimes)
				{
					frame_punch1 ++;
					aux=0;
				}
			}
			
	}
	else
	if (number == 1)
	{
			SDL_BlitSurface(player1_punch2, &frames_punch2[static_cast<int>(frame_punch2)], screen, &offset);

			if(frame_punch2 > 6) 
			{
				frame_punch2 = 0;
				punching = false;
				b[2] = 0;
			}
			else
			{
				aux++;
				if (aux == slowtimes)
				{
					frame_punch2 ++;
					aux=0;
				}
			}
	}
	else
	{
			SDL_BlitSurface(player1_punch3, &frames_punch3[static_cast<int>(frame_punch3)], screen, &offset);

			if(frame_punch3 > 9) 
			{
				frame_punch3 = 0;
				punching = false;
				b[2] = 0;
			}
			else
			{
				aux++;
				if (aux == slowtimes)
				{
					frame_punch3 ++;
					aux=0;
				}
			}

	}
}

void player::kick(SDL_Surface* screen)
{	
	if ((frame_kick == 0)&&(frame_shut2 == 0)&&(!shpitzing))
	{	
		srand( time(NULL) );
		number = rand() % 2;
		//fprintf(stdout, "Random number: %d \n", number);
	}

	other_action = true;
	shpitzing = true;

	if (number == 0)
	{
		SDL_BlitSurface(player1_shut, &frames_kick[static_cast<int>(frame_kick)], screen, &offset);

		if(frame_kick > 4) 
		{
			frame_kick = 0;
			shpitzing = false;
			b[3]=0;
		}
		else
		{
			aux++;
			if (aux == slowtimes)
			{
				frame_kick ++;
				aux=0;
			}
		} 
	}
	else
	{
		SDL_BlitSurface(player1_shut2, &frames_shut2[static_cast<int>(frame_shut2)], screen, &offset);

		if(frame_shut2 > 7) 
		{
			frame_shut2 = 0;
			shpitzing = false;
			b[3]=0;
		}
		else
		{
			aux++;
			if (aux == slowtimes)
			{
				frame_shut2 ++;
				aux=0;
			}
		}
	}

}

void player::block(SDL_Surface* screen)
{	
	other_action = true;
	
	SDL_BlitSurface(player1_block, &frames_block[static_cast<int>(frame_block)], screen, &offset);

	//SDL_Flip(screen);

	if(frame_block > 2) 
	{
	    frame_block = 0;
    }
	else
	{
		aux1++;
		if (aux1 == slowtimes * 2)
		{
			frame_block ++;
			aux1=0;
		}
	}
}

void player::back_to_idle(void)
{
		other_action = false;
		punching = false;
}


player::player(void)
{
		
	player1_idle = SDL_DisplayFormat(SDL_LoadBMP("resources\\player\\idle.bmp"));
	player1_walkf = SDL_DisplayFormat(SDL_LoadBMP("resources\\player\\walkf.bmp"));
	player1_walkb = SDL_DisplayFormat(SDL_LoadBMP("resources\\player\\walkb.bmp"));
	player1_punch1 = SDL_DisplayFormat(SDL_LoadBMP("resources\\player\\punch1.bmp"));
	player1_punch2 = SDL_DisplayFormat(SDL_LoadBMP("resources\\player\\punch2.bmp"));
	player1_punch3 = SDL_DisplayFormat(SDL_LoadBMP("resources\\player\\punch3.bmp"));
	player1_shut = SDL_DisplayFormat(SDL_LoadBMP("resources\\player\\kick.bmp"));
	player1_shut2 = SDL_DisplayFormat(SDL_LoadBMP("resources\\player\\kick2.bmp"));
	player1_block = SDL_DisplayFormat(SDL_LoadBMP("resources\\player\\block.bmp"));

	offset.x = 50;
	offset.y = 300;
	
	Uint32 colorkey_idle = SDL_MapRGB(player1_idle->format, 112, 136, 136);
	SDL_SetColorKey(player1_idle, SDL_SRCCOLORKEY, colorkey_idle);

	Uint32 colorkey_walkf = SDL_MapRGB(player1_walkf->format, 112, 136, 136);
	SDL_SetColorKey(player1_walkf, SDL_SRCCOLORKEY, colorkey_walkf);
	
	Uint32 colorkey_walkb = SDL_MapRGB(player1_walkb->format, 112, 136, 136);
	SDL_SetColorKey(player1_walkb, SDL_SRCCOLORKEY, colorkey_walkb);
	
	Uint32 colorkey_punch1 = SDL_MapRGB(player1_punch1->format, 112, 136, 136);
	SDL_SetColorKey(player1_punch1, SDL_SRCCOLORKEY, colorkey_punch1);

	Uint32 colorkey_punch2 = SDL_MapRGB(player1_punch2->format, 112, 136, 136);
	SDL_SetColorKey(player1_punch2, SDL_SRCCOLORKEY, colorkey_punch2);

	Uint32 colorkey_punch3 = SDL_MapRGB(player1_punch3->format, 112, 136, 136);
	SDL_SetColorKey(player1_punch3, SDL_SRCCOLORKEY, colorkey_punch3);

	Uint32 colorkey_shut = SDL_MapRGB(player1_shut->format, 112, 136, 136);
	SDL_SetColorKey(player1_shut, SDL_SRCCOLORKEY, colorkey_shut);

	Uint32 colorkey_shut2 = SDL_MapRGB(player1_shut2->format, 112, 136, 136);
	SDL_SetColorKey(player1_shut2, SDL_SRCCOLORKEY, colorkey_shut2);

	Uint32 colorkey_block = SDL_MapRGB(player1_block->format, 112, 136, 136);
	SDL_SetColorKey(player1_block, SDL_SRCCOLORKEY, colorkey_block);

	
	setrects_idle(frames_idle);
	setrects_walkf(frames_walkf);
	setrects_walkb(frames_walkb);
	setrects_punch1(frames_punch1);
	setrects_punch2(frames_punch2);
	setrects_punch3(frames_punch3);
	setrects_kick(frames_kick);
	setrects_shut2(frames_shut2);
	setrects_block(frames_block);

	frame_idle = 0;
	frame_walkf = 0;
	frame_walkb = 0;
	frame_punch1 = 0;
	frame_punch2 = 0;
	frame_punch3 = 0;
	frame_kick = 0;
	frame_shut2 = 0;
	frame_block = 0;

	b[0] = 0;
	b[1] = 0;
	b[2] = 0;
	b[3] = 0;
	b[4] = 0;	
}


player::~player(void)
{
	SDL_FreeSurface(player1_idle);
	SDL_FreeSurface(player1_walkf);
	SDL_FreeSurface(player1_walkb);
	SDL_FreeSurface(player1_punch1);
	SDL_FreeSurface(player1_punch2);
	SDL_FreeSurface(player1_punch3);
	SDL_FreeSurface(player1_shut);
	SDL_FreeSurface(player1_shut2);
	SDL_FreeSurface(player1_block);
}
