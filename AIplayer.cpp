#include "AIplayer.h"
#include "SDL.h"
#include "time.h"

 using namespace std;

	SDL_Surface *AIplayer_idle, *AIplayer_walkf, *AIplayer_walkb, *AIplayer_punch1, *AIplayer_punch2, *AIplayer_kick, *AIplayer_punched, *AIplayer_ko, *AIplayer_knocked;
	SDL_Rect AIoffset;
	int AIframe_idle, AIframe_walkf, AIframe_walkb, AIframe_punch1, AIframe_punch2, AIframe_kick, AIframe_punched1, AIframe_ko1;
	SDL_Rect AIframes_idle[10];
	SDL_Rect AIframes_walkf[11];
	SDL_Rect AIframes_walkb[11];
	SDL_Rect AIframes_punch1[12];
	SDL_Rect AIframes_punch2[8];
	SDL_Rect AIframes_kick[6];
	SDL_Rect AIframes_punched1[15];
	SDL_Rect AIframes_ko1[25];
	int AIaux = 0;
	bool AIother_action = false;
	bool AIpunching = false;
	bool AIfalling = false;
	int AInumber = 0;
	int AIslowtimes = 3;
	int AILife = 1000;
	int AIStrength = 1;
	int AIKoChance = 5;
	bool knockedout = false;
	bool AIb[7] = {0,0,0,0,0,0,0}; //Walkf, Walkb, punch, kick, punched, falling, knockedout
	//string player_folder = "aiplayer";

void AIsetrects_idle(SDL_Rect* clip)
{
        for(int i = 0; i < 10; i ++) {
                clip[i].x = 0 + i*224;
                clip[i].y = 0;
                clip[i].w = 224;
                clip[i].h = 226;
        }
}

void AIsetrects_walkf(SDL_Rect* clip)
{
        for(int i = 0; i < 11; i ++) {
                clip[i].x = 0 + i*224;
                clip[i].y = 0;
                clip[i].w = 224;
                clip[i].h = 226;
        }
}

void AIsetrects_walkb(SDL_Rect* clip)
{
        for(int i = 0; i < 11; i ++) {
                clip[i].x = 0 + i*224;
                clip[i].y = 0;
                clip[i].w = 224;
                clip[i].h = 226;
        }
}

void AIsetrects_punch1(SDL_Rect* clip)
{
        for(int i = 0; i < 12; i ++) {
                clip[i].x = 0 + i*260;
                clip[i].y = 0;
                clip[i].w = 260;
                clip[i].h = 226;
        }
}

void AIsetrects_punch2(SDL_Rect* clip)
{
        for(int i = 0; i < 8; i ++) {
                clip[i].x = 0 + i*260;
                clip[i].y = 0;
                clip[i].w = 260;
                clip[i].h = 226;
        }
}

void AIsetrects_kick(SDL_Rect* clip)
{
        for(int i = 0; i < 6; i ++) {
                clip[i].x = 0 + i*260;
                clip[i].y = 0;
                clip[i].w = 260;
                clip[i].h = 226;
        }
}

void AIsetrects_punched1(SDL_Rect* clip)
{
        for(int i = 0; i < 7; i ++) {
                clip[i].x = 0 + i*284;
                clip[i].y = 0;
                clip[i].w = 284;
                clip[i].h = 226;
        }
}

void AIsetrects_ko1(SDL_Rect* clip)
{
        for(int i = 0; i < 25; i ++) {
                clip[i].x = 0 + i*356;
                clip[i].y = 0;
                clip[i].w = 356;
                clip[i].h = 240;
        }
}

void AIplayer::idle(SDL_Surface* screen)
{	
	if ((!AIother_action)&&(AILife>0))
	{
		SDL_BlitSurface(AIplayer_idle, &AIframes_idle[static_cast<int>(AIframe_idle)], screen, &AIoffset);

		//SDL_Flip(screen);
		if(AIframe_idle > 8) 
		{
			AIframe_idle = 0;
		}
		else
		{
			AIaux++;
			if (AIaux == AIslowtimes)
			{
				AIframe_idle ++;
				AIaux=0;
			}
		}
	}
}

void AIplayer::walkf(SDL_Surface* screen)
{	
	AIother_action = true;
	if (AIoffset.x > 0)
		AIoffset.x-= 3;

	SDL_BlitSurface(AIplayer_walkf, &AIframes_walkf[static_cast<int>(AIframe_walkf)], screen, &AIoffset);

	//SDL_Flip(screen);

	if(AIframe_walkf > 9) 
	{
	    AIframe_walkf = 0;
		//AIb[1] = 0;
    }
	else
	{
		AIaux++;
		if (AIaux == AIslowtimes)
		{
			AIframe_walkf ++;
			AIaux=0;
		}
	}
}

void AIplayer::walkb(SDL_Surface* screen)
{	
	AIother_action = true;
	if (AIoffset.x < screen->w - 180)
		AIoffset.x+= 3;
	SDL_BlitSurface(AIplayer_walkb, &AIframes_walkb[static_cast<int>(AIframe_walkb)], screen, &AIoffset);

	//SDL_Flip(screen);

	if(AIframe_walkb > 9) 
	{
	    AIframe_walkb = 0;
		//AIb[0] = 0;
    }
	else
	{
		AIaux++;
		if (AIaux == AIslowtimes)
		{
			AIframe_walkb ++;
			AIaux=0;
		}
	}
}

void AIplayer::punch(SDL_Surface* screen)
{		

	if ((AIframe_punch1 == 0)&&(AIframe_punch2 == 0)&&(!AIpunching))
	{	
		srand( time(NULL) );
		AInumber = rand() % 2;
		//fprintf(stdout, "Random number: %d \n", number);
	}

	AIother_action = true;
	AIpunching = true;

	if (AInumber == 0)
	{
			SDL_BlitSurface(AIplayer_punch1, &AIframes_punch1[static_cast<int>(AIframe_punch1)], screen, &AIoffset);
			//SDL_Flip(screen);

			if(AIframe_punch1 > 10) 
			{
				AIframe_punch1 = 0;
				AIpunching = false;
				AIb[2]=0;
			}
			else
			{
				AIaux++;
				if (AIaux == AIslowtimes)
				{
					AIframe_punch1 ++;
					AIaux=0;
				}
			}
	}
	else
	{
			SDL_BlitSurface(AIplayer_punch2, &AIframes_punch2[static_cast<int>(AIframe_punch2)], screen, &AIoffset);
			//SDL_Flip(screen);

			if(AIframe_punch2 > 6) 
			{
				AIframe_punch2 = 0;
				AIpunching = false;
				AIb[2] = 0;
			}
			else
			{
				AIaux++;
				if (AIaux == AIslowtimes)
				{
					AIframe_punch2 ++;
					AIaux=0;
				}
			}
	}
}

void AIplayer::kick(SDL_Surface* screen)
{	
	AIother_action = true;

	SDL_BlitSurface(AIplayer_kick, &AIframes_kick[static_cast<int>(AIframe_kick)], screen, &AIoffset);

	//SDL_Flip(screen);

	if(AIframe_kick > 4) 
	{
	    AIframe_kick = 0;
		AIb[3]=0;
    }
	else
	{
		AIaux++;
		if (AIaux == AIslowtimes)
		{
			AIframe_kick ++;
			AIaux=0;
		}
	}
}

void AIplayer::punched(SDL_Surface* screen)
{	
	AIother_action = true;

	SDL_BlitSurface(AIplayer_punched, &AIframes_punched1[static_cast<int>(AIframe_punched1)], screen, &AIoffset);

	//SDL_Flip(screen);

	if(AIframe_punched1 > 5) 
	{
	    AIframe_punched1 = 0;
		AIb[4]=0;
    }
	else
	{
		AIaux++;
		if (AIaux == AIslowtimes)
		{
			AIframe_punched1 ++;
			AIaux=0;
		}
	}

}

void AIplayer::ko(SDL_Surface* screen)
{	
	AIother_action = true;
	AIfalling = true;

	SDL_BlitSurface(AIplayer_ko, &AIframes_ko1[static_cast<int>(AIframe_ko1)], screen, &AIoffset);

	//SDL_Flip(screen);

	if(AIframe_ko1 > 23) 
	{
	    AIframe_ko1 = 0;
		AIfalling = false;
		AIb[5]=0;
		AIb[6]=1;
    }
	else
	{
		AIaux++;
		if (AIaux == AIslowtimes)
		{
			AIframe_ko1 ++;
			AIaux=0;
		}
	}

}

void AIplayer::knocked(SDL_Surface* screen)
{	
	AIother_action = true;	

	if (!AIfalling)
		SDL_BlitSurface(AIplayer_knocked, NULL, screen, &AIoffset);
	else
		knockedout = true;

}


void AIplayer::back_to_idle(void)
{
		AIother_action = false;
		AIpunching = false;
}


AIplayer::AIplayer(void)
{
	
	AIplayer_idle = SDL_DisplayFormat(SDL_LoadBMP("resources\\aiplayer\\idle.bmp")); //TODO implement constant player_folder
	AIplayer_walkf = SDL_DisplayFormat(SDL_LoadBMP("resources\\aiplayer\\walkf.bmp"));
	AIplayer_walkb = SDL_DisplayFormat(SDL_LoadBMP("resources\\aiplayer\\walkb.bmp"));
	AIplayer_punch1 = SDL_DisplayFormat(SDL_LoadBMP("resources\\aiplayer\\punch1.bmp"));
	AIplayer_punch2 = SDL_DisplayFormat(SDL_LoadBMP("resources\\aiplayer\\punch2.bmp"));
	AIplayer_kick = SDL_DisplayFormat(SDL_LoadBMP("resources\\aiplayer\\kick.bmp"));
	AIplayer_punched = SDL_DisplayFormat(SDL_LoadBMP("resources\\aiplayer\\punched1.bmp"));
	AIplayer_ko = SDL_DisplayFormat(SDL_LoadBMP("resources\\aiplayer\\ko1.bmp"));
	AIplayer_knocked = SDL_DisplayFormat(SDL_LoadBMP("resources\\aiplayer\\knocked.bmp"));

	AIoffset.x = 500;
	AIoffset.y = 300;

	Uint32 colorkey_knocked = SDL_MapRGB(AIplayer_knocked->format, 112, 136, 136);
	SDL_SetColorKey(AIplayer_knocked, SDL_SRCCOLORKEY, colorkey_knocked);

	Uint32 colorkey_idle = SDL_MapRGB(AIplayer_idle->format, 112, 136, 136);
	SDL_SetColorKey(AIplayer_idle, SDL_SRCCOLORKEY, colorkey_idle);

	Uint32 colorkey_walkf = SDL_MapRGB(AIplayer_walkf->format, 112, 136, 136);
	SDL_SetColorKey(AIplayer_walkf, SDL_SRCCOLORKEY, colorkey_walkf);
	
	Uint32 colorkey_walkb = SDL_MapRGB(AIplayer_walkb->format, 112, 136, 136);
	SDL_SetColorKey(AIplayer_walkb, SDL_SRCCOLORKEY, colorkey_walkb);
	
	Uint32 colorkey_punch1 = SDL_MapRGB(AIplayer_punch1->format, 112, 136, 136);
	SDL_SetColorKey(AIplayer_punch1, SDL_SRCCOLORKEY, colorkey_punch1);

	Uint32 colorkey_punch2 = SDL_MapRGB(AIplayer_punch2->format, 112, 136, 136);
	SDL_SetColorKey(AIplayer_punch2, SDL_SRCCOLORKEY, colorkey_punch2);

	Uint32 colorkey_kick = SDL_MapRGB(AIplayer_kick->format, 112, 136, 136);
	SDL_SetColorKey(AIplayer_kick, SDL_SRCCOLORKEY, colorkey_kick);

	Uint32 colorkey_punched = SDL_MapRGB(AIplayer_punched->format, 112, 136, 136);
	SDL_SetColorKey(AIplayer_punched, SDL_SRCCOLORKEY, colorkey_punched); 

	Uint32 colorkey_ko = SDL_MapRGB(AIplayer_ko->format, 112, 136, 136);
	SDL_SetColorKey(AIplayer_ko, SDL_SRCCOLORKEY, colorkey_ko);
	
	AIsetrects_idle(AIframes_idle);
	AIsetrects_walkf(AIframes_walkf);
	AIsetrects_walkb(AIframes_walkb);
	AIsetrects_punch1(AIframes_punch1);
	AIsetrects_punch2(AIframes_punch2);
	AIsetrects_kick(AIframes_kick);
	AIsetrects_punched1(AIframes_punched1);
	AIsetrects_ko1(AIframes_ko1);

	AIframe_idle = 0;
	AIframe_walkf=0;
	AIframe_walkb=0;
	AIframe_punch1=0;
	AIframe_punch2=0;
	AIframe_kick=0;
	AIframe_punched1=0;
	AIframe_ko1=0;

	AIb[0] = 0;
	AIb[1] = 0;
	AIb[2] = 0;
	AIb[3] = 0;
	AIb[4] = 0;
	AIb[5] = 0;
	AIb[6] = 0;
	

	AILife = 5;
}


AIplayer::~AIplayer(void)
{
	SDL_FreeSurface(AIplayer_idle);
	SDL_FreeSurface(AIplayer_walkf);
	SDL_FreeSurface(AIplayer_walkb);
	SDL_FreeSurface(AIplayer_punch1);
	SDL_FreeSurface(AIplayer_punch2);
	SDL_FreeSurface(AIplayer_kick);
	SDL_FreeSurface(AIplayer_punched);
	SDL_FreeSurface(AIplayer_ko);
	SDL_FreeSurface(AIplayer_knocked);
}
