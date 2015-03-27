
#include "SdlImageLib.hpp"

// Constructeur de Destucteur

SdlImageLib::SdlImageLib( void )
	: m_titreFenetre("SNAKE"), m_largeurFenetre(1200), m_hauteurFenetre(800), m_fenetre(0)
{

}

void 	SdlImageLib::initLibrary( TMap & map )
{
	this->m_largeurFenetre = map.size.getX();
	this->m_hauteurFenetre = map.size.getY();

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
		SDL_Quit();
		std::exit(-1);
		// return false;
	}

	this->m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->m_largeurFenetre * BLOCK_SIZE, this->m_hauteurFenetre * BLOCK_SIZE, SDL_WINDOW_SHOWN);

	if (this->m_fenetre == NULL)
	{
		std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
		SDL_Quit();

		std::exit(-1);
		// return false;
	}
	this->m_windowsurface = SDL_GetWindowSurface(this->m_fenetre);

	this->body = SDL_LoadBMP("libraries/lib_sdlimages/img/body.bmp");
	this->head_d = SDL_LoadBMP("libraries/lib_sdlimages/img/head_d.bmp");
	this->head_u = SDL_LoadBMP("libraries/lib_sdlimages/img/head_u.bmp");
	this->head_l = SDL_LoadBMP("libraries/lib_sdlimages/img/head_l.bmp");
	this->head_r = SDL_LoadBMP("libraries/lib_sdlimages/img/head_r.bmp");
	this->food = SDL_LoadBMP("libraries/lib_sdlimages/img/food.bmp");
	this->rock = SDL_LoadBMP("libraries/lib_sdlimages/img/rock.bmp");

}

SdlImageLib::~SdlImageLib() {}

void	SdlImageLib::closeLibrary( void )
{
	// SDL_GL_DeleteContext(m_contexteOpenGL);
	SDL_DestroyWindow(m_fenetre);
	SDL_Quit();
}

// Methodes

int		SdlImageLib::getInput( void )
{
		// Gestion des evenements

	SDL_PollEvent(&m_evenements);

	if (m_evenements.window.event == SDL_WINDOWEVENT_CLOSE || m_evenements.window.event == SDLK_q)
		return STD_EXIT;
	if (m_evenements.window.event == SDLK_SPACE)
		return STD_SPACE;
	if (m_evenements.key.keysym.sym == SDLK_RIGHT)
		return STD_RIGHT;
	if (m_evenements.key.keysym.sym == SDLK_LEFT)
		return STD_LEFT;
	if (m_evenements.key.keysym.sym == SDLK_UP)
		return STD_UP;
	if (m_evenements.key.keysym.sym == SDLK_DOWN)
		return STD_DOWN;
	return 0;
}

void SdlImageLib::printMap( TMap & map )
{
	SDL_Surface		*surfacePtr;
	bool			print = false;

	SDL_FillRect(this->m_windowsurface, NULL, SDL_MapRGB(this->m_windowsurface->format, 255, 255, 255));

	SDL_Rect yop;
	yop.x = 30 * BLOCK_SIZE;
	yop.y = 30 * BLOCK_SIZE;
	SDL_BlitSurface(this->rock, NULL, this->m_windowsurface, &yop);

	for (int y = 0; y < map.size.getY(); y++)
	{
		for (int x = 0; x < map.size.getX(); x++)
		{
			if (map.map[y][x] == 'F')
			{
				this->item_form.x = x * BLOCK_SIZE;
				this->item_form.y = y * BLOCK_SIZE;
				surfacePtr = this->food;
				print = true;
			}
			else if (map.map[y][x] == '1')
			{
				this->item_form.x = x * BLOCK_SIZE;
				this->item_form.y = y * BLOCK_SIZE;
				surfacePtr = this->body;
				print = true;
			}
			else if (map.map[y][x] == '*')
			{
				this->item_form.x = x * BLOCK_SIZE;
				this->item_form.y = y * BLOCK_SIZE;
				surfacePtr = this->head_u;
				print = true;
			}
			if (print)
				SDL_BlitSurface(surfacePtr, NULL, this->m_windowsurface, &this->item_form);
			print = false;
		}
	}

	SDL_UpdateWindowSurface(this->m_fenetre);


	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// glEnable (GL_BLEND);
	// glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// int sY = static_cast<int>(round((map.size.getY() + 2) / 2));
	// int sX = static_cast<int>(round((map.size.getX() + 2) / 2));

	// this->drawFace(Vector2(-sX, -sY), Vector2(-sX, sY-1), Vector2(sX-1, sY-1), Vector2(sX-1, -sY));

	// for(int y = -sY; y<sY; y++)
	// {
	// 	for(int x = -sX; x<sX; x++)
	// 	{
	// 		if((y == -sY || x == -sX) || (y == sY-1 || x == sX-1))
	// 			this->drawVox(Vector3(x, y, 1), 2);
	// 	}
	// }

	// for(int y = 0; y<map.size.getY(); y++)
	// {
	// 	for(int x = 0; x<map.size.getX(); x++)
	// 	{
	// 		if (map.map[y][x] == 'F')
	// 			this->drawVox(Vector3(x-sX, y-sY, 1), 1);
	// 		if (map.map[y][x] == '1')
	// 			this->drawVox(Vector3(x-sX, y-sY, 1), 3);
	// 		if (map.map[y][x] == '*')
	// 			this->drawVox(Vector3(x-sX, y-sY, 1), 4);
	// 	}
	// }

	// // Actualisation de la fenetre
	// glFlush();
	// SDL_GL_SwapWindow(m_fenetre);
}

void 	SdlImageLib::gameOver( std::string toPrint ) const {}

SdlImageLib		*createLib() {return new SdlImageLib();}

void			deleteLib(SdlImageLib * lib) {delete lib;}
