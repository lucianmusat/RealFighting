#include "SDL.h"
#include "player.h"
#include "AIplayer.h"

using namespace std;

int _stdcall WinMain(int argc, char * args[])
//int main(int argc, char * args[])
{
	bool running = true;
	const int FPS = 60;
	bool just_once, just_once2 = false;
	int number=0;

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		running = false;

	SDL_Surface *screen;
	screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_GL_SwapBuffers();

	SDL_WM_SetCaption("Real Fighting Alfa 1.0", NULL);

	if (screen == NULL)
		running=false;

	SDL_Event occur;	
	player player1;
	AIplayer player2;

	Uint32 start;
	SDL_Rect stage_offset;
	stage_offset.x=0;
	stage_offset.y=0;	
	stage_offset.h=600;
	stage_offset.w=864;

	SDL_Surface *stage_image;
	stage_image = SDL_DisplayFormat(SDL_LoadBMP("resources\\stage1.bmp"));	

	SDL_Joystick *stick = NULL;
	bool joystick_present = false;

	//Check if there's any joysticks
	if( SDL_NumJoysticks() > 0 )
	{
		//fprintf(stdout, "Joystick found \n");
		joystick_present = true;
	}
	else
		fprintf(stdout, "No joysticks found \n"); 

	while (running)
	{
	start = SDL_GetTicks();

                while(SDL_PollEvent(&occur)) {
                        switch(occur.type) {
                                case SDL_QUIT:
                                        running = false;
                                        break;

                              case SDL_KEYDOWN:
                                        switch(occur.key.keysym.sym) {
                                                case SDLK_a:
														player1.b[0] = 1;
                                                        break;
                                                case SDLK_d:														
                                                        player1.b[1] = 1;
                                                        break;
                                                case SDLK_j:														
                                                        player1.b[2] = 1;
                                                        break;
                                                case SDLK_k:														
                                                        player1.b[3] = 1;
                                                        break;    
                                                case SDLK_l:														
                                                        player1.b[4] = 1;
                                                        break;    
                                                case SDLK_KP6:														
                                                        player2.AIb[0] = 1;
                                                        break;
                                                case SDLK_KP4:														
                                                        player2.AIb[1] = 1;
                                                        break;         
                                                case SDLK_u:														
                                                        player2.AIb[2] = 1;
                                                        break;
                                                case SDLK_i:														
                                                        player2.AIb[3] = 1;
                                                        break;
                                                case SDLK_o:														
                                                        player2.AIb[7] = 1;
                                                        break;
                                        }
                                        break;
                                case SDL_KEYUP:
                                        switch(occur.key.keysym.sym) {
                                                case SDLK_a:
                                                        player1.b[0] = 0;
                                                        break;
                                                case SDLK_d:
														player1.b[1] = 0;
                                                        break;                                    
                                                case SDLK_l:														
                                                        player1.b[4] = 0;
                                                        break;    
                                                case SDLK_KP6:
                                                        player2.AIb[0] = 0;
                                                        break;
                                                case SDLK_KP4:
														player2.AIb[1] = 0;
                                                        break;     
                                                case SDLK_o:														
                                                        player2.AIb[7] = 0;
                                                        break;
                                        }
                                        break;

							    case SDL_JOYBUTTONDOWN:  // Handle Joystick Button Presses 
										if ( occur.jbutton.button == 2 ) 
											player1.b[2] = 1;
										if ( occur.jbutton.button == 3 ) 
											player1.b[3] = 1;
										break;
							    case SDL_JOYBUTTONUP:  // Handle Joystick Button Releases
										if ( occur.jbutton.button == 2 ) //punch
											player1.b[2] = 0;
										if ( occur.jbutton.button == 3 ) //kick
											player1.b[3] = 0;
										break;

                        }
                }



		if (joystick_present)
		{
			stick = SDL_JoystickOpen( 0 );    
			//If there's a problem opening the joystick
			if( stick == NULL )
			{
				joystick_present = false;
				fprintf(stdout, "Stick = null \n");
			}

		   if( occur.type == SDL_JOYAXISMOTION )
			{
        //If joystick 0 has moved
        if( occur.jaxis.which == 0 )
			{
				//If the X axis changed
				if( occur.jaxis.axis == 0 )
				{
					//If the X axis is neutral
					if( ( occur.jaxis.value > -10000 ) && ( occur.jaxis.value < 10000 ) )
					{
						//fprintf(stdout, "Neutral zone \n");
						player1.b[0] = 0;
						player1.b[1] = 0;
						player1.b[2] = 0;
						player1.b[3] = 0;
						player1.b[4] = 0;
					}
					//If not
					else
					{
							if( occur.jaxis.value < 0 )
							{
								player1.b[0] = 1;
								//fprintf(stdout, "Moved to the left \n");
							}
							else
							{
								player1.b[1] = 1;
								//fprintf(stdout, "Moved to the right \n");
							}
					}    
				}

			}
			}

		}		

		SDL_BlitSurface(stage_image,  &stage_offset, screen, NULL);

		//player1 movements
		if(player1.b[0])
		{
			player1.walkb(screen);
			if ((player1.offset.x <= screen->w/2) && (stage_offset.x > 0)&&(player2.AIoffset.x < screen->w-190))
			{
				stage_offset.x--;
				if (player2.AIb[6])
					player2.AIoffset.x++;
				if ((!player2.AIb[0])&&(!player2.AIb[1]))
					player2.AIoffset.x++;

			}
		}
		else if(player1.b[1])
		{
			if (player1.offset.x < (player2.AIoffset.x - 184))
			{
				player1.walkf(screen);	
			}
			else
			{
				player1.offset.x-=3;
				player1.walkf(screen);
			}

			if ((player1.offset.x >= screen->w/3) && (stage_offset.x < stage_image->w - screen->w))
			{
				stage_offset.x+=1;			
				if (player2.AIb[6])
					player2.AIoffset.x--;
			}
		}
		else if(player1.b[2])		
		{
			player1.b[4]=0;
			player1.punch(screen);			//punch animation			
			if ((player1.offset.x > (player2.AIoffset.x - 185))&&(!just_once))  //if near AI
			{
				srand(time(NULL)+number);
				number = rand() % 2;
				player1.percent_perversa = number;
				fprintf(stdout, "Player 1 has %d%% chances to knock out oponent. \n", player1.percent_perversa);
				srand(time(NULL)+number);
				number = rand() % 100;
				fprintf(stdout, "Gods decided: %d \n", number);
				if (player2.AIb[7])
					fprintf(stdout, "But player2 parries!");

				if ((number < player1.percent_perversa)&&(!player2.AIb[7]))
				{
					player2.AILife=0;		//Knocked out of the park
					fprintf(stdout, "K-BOOM!! \n");
				}
				else 
				{
					if(!player2.AIb[7])
						player2.AILife-=2;			// Take life from AI
					else
						player2.AILife-=1;			// Take less life from AI if it blocks
				}
				if((player2.AILife <1)&&(!player2.AIb[6]))	//if no more life and not knocked out
					player2.AIb[5]=1;		//falling
				else if (!player2.AIb[6])
				{
					player2.AIb[4]=1;			//animate player2 as being punched

				}
				just_once = true;
			}
		}
		else if (player1.b[3])
		{
			player1.b[4]=0;
			player1.kick(screen);
			if ((player1.offset.x > (player2.AIoffset.x - 185))&&(!just_once))  //if near AI
			{
				srand(time(NULL)+number);
				number = rand() % 2;
				player1.percent_perversa = number;
				fprintf(stdout, "Player 1 has %d%% chances to knock out oponent. \n", player1.percent_perversa);
				srand(time(NULL)+number);
				number = rand() % 100;
				fprintf(stdout, "Gods decided: %d \n", number);
				if (player2.AIb[7])
					fprintf(stdout, "But player2 parries!");

				if (number < player1.percent_perversa)
				{
					player2.AILife=0;		//Knocked out of the park
					fprintf(stdout, "K-BOOM!! \n");
				}
				else 
				{
					if(!player2.AIb[7])
						player2.AILife-=2;			// Take life from AI
					else
						player2.AILife-=1;			// Take less life from AI if it blocks
				}
				if((player2.AILife <1)&&(!player2.AIb[6]))  //if no more life and not knocked out
					player2.AIb[5]=1;		//falling
				else if (!player2.AIb[6])
				{
					player2.AIb[4]=1;			//animate player2 as being punched
				}
				just_once = true;
			}
		}
		else if(player1.b[4])
		{
			player1.block(screen);
		}
		else if(player1.b[5])
		{
			player1.punched(screen);
		}
		else if (player1.b[6])
		{
			player1.ko(screen);
		}
		else if (player1.b[7])
		{
			player1.knocked(screen);
		}
		else
		{
			just_once = false;
			player1.back_to_idle();			
		}


		//player2 movements

		if(player2.AIb[0]) 
		{
				player2.walkb(screen);
		}
		else if(player2.AIb[1])
		{
			if (player2.AIoffset.x > (player1.offset.x + 184))
			{
				player2.walkf(screen);				
			}
		}
		else if (player2.AIb[2])
		{
			player2.punch(screen);			//punch animation			
			if ((player2.AIoffset.x < (player1.offset.x + 185))&&(!just_once2))  //if near AI
			{
				srand(time(NULL)+number);
				number = rand() % 2;
				player2.AIpercent_perversa = number;
				fprintf(stdout, "Player 2 has %d%% chances to knock out oponent. \n", player1.percent_perversa);
				srand(time(NULL)+number);
				number = rand() % 100;
				fprintf(stdout, "Gods decided: %d \n", number);
				if (player1.b[4])
					fprintf(stdout, "But player1 parries!");

				if ((number < player2.AIpercent_perversa)&&(!player1.b[4]))
				{
					player1.Life=0;		//Knocked out of the park
					fprintf(stdout, "K-BOOM!! \n");
				}
				else 
				{
					if(!player1.b[4])
						player1.Life-=2;			// Take life from AI
					else
						player1.Life-=1;			// Take less life from AI if it blocks
				}
				if((player1.Life <1)&&(!player1.b[7]))	//if no more life and knocked out
					player1.b[6]=1;		//falling
				else if (!player1.b[7])
				{
					player1.b[5]=1;			//animate player1 as being punched

				}
				just_once2 = true;
			}
		}
		else if (player2.AIb[3])
		{
			player2.kick(screen);			//punch animation			
			if ((player2.AIoffset.x < (player1.offset.x + 185))&&(!just_once2))  //if near AI
			{
				srand(time(NULL)+number);
				number = rand() % 2;
				player2.AIpercent_perversa = number;
				fprintf(stdout, "Player 2 has %d%% chances to knock out oponent. \n", player1.percent_perversa);
				srand(time(NULL)+number);
				number = rand() % 100;
				fprintf(stdout, "Gods decided: %d \n", number);
				if (player1.b[4])
					fprintf(stdout, "But player1 parries!");

				if ((number < player2.AIpercent_perversa)&&(!player1.b[4]))
				{
					player1.Life=0;		//Knocked out of the park
					fprintf(stdout, "K-BOOM!! \n");
				}
				else 
				{
					if(!player1.b[4])
						player1.Life-=2;			// Take life from AI
					else
						player1.Life-=1;			// Take less life from AI if it blocks
				}
				if((player1.Life <1)&&(!player1.b[7]))	//if no more life and knocked out
					player1.b[6]=1;		//falling
				else if (!player1.b[7])
				{
					player1.b[5]=1;			//animate player1 as being punched

				}
				just_once2 = true;
			}
		}
		else if (player2.AIb[4])
		{
			player2.punched(screen);
		}
		else if (player2.AIb[5])
		{
			player2.ko(screen);
		}
		else if (player2.AIb[6])
		{
			player2.knocked(screen);
		}
		else if (player2.AIb[7])
		{
			player2.block(screen);
		}
		else
		{
			just_once2 = false;
			player2.back_to_idle();			
		}

		player1.idle(screen);	
		player2.idle(screen); 
		
		SDL_Flip(screen);

		if(1000/FPS > SDL_GetTicks()-start) 
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start)); 

	}
	player1.~player();
	player2.~AIplayer();
	SDL_Quit();
	return 0;
}