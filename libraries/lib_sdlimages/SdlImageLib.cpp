
#include "SdlImageLib.hpp"
#include "Player.hpp"
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

void SdlImageLib::printMap( TMap const & map )
{
	SDL_Surface		*surfacePtr;
	bool			print = false;

	// std::cout << "LA !!!!!!!!!" << std::endl;
	SDL_FillRect(this->m_windowsurface, NULL, SDL_MapRGB(this->m_windowsurface->format, 255, 255, 255));

	// SDL_Rect yop;
	// yop.x = 30 * BLOCK_SIZE;
	// yop.y = 30 * BLOCK_SIZE;
	// SDL_BlitSurface(this->rock, NULL, this->m_windowsurface, &yop);

	std::list<Vector2>::const_iterator		it;
	std::list<Vector2>::const_iterator		ite;

	std::vector<Player>::const_iterator		itP;
	std::vector<Player>::const_iterator		iteP;


	if (map.foods.size() > 0)
	{
		ite = map.foods.end();
		for (it = map.foods.begin(); it != ite; it++)
		{
			this->item_form.x = it->getX() * BLOCK_SIZE;
			this->item_form.y = it->getY() * BLOCK_SIZE;
			SDL_BlitSurface(this->food, NULL, this->m_windowsurface, &this->item_form);
		}
	}
	if (map.rocks.size() > 0)
	{
		ite = map.rocks.end();
		for (it = map.rocks.begin(); it != ite; it++)
		{
			this->item_form.x = it->getX() * BLOCK_SIZE;
			this->item_form.y = it->getY() * BLOCK_SIZE;
			SDL_BlitSurface(this->rock, NULL, this->m_windowsurface, &this->item_form);
		}
	}
	if (map.snakes.size() > 0)
	{
		bool		head;
		Vector2		dir;

		iteP = map.snakes.end();
		for (itP = map.snakes.begin(); itP != iteP; itP++)
		{
			head = true;
			dir = itP->getDir();
			// if (itP != map.snakes.begin())
			// {
			// 	headPrint = NC_YELLOW;
			// 	bodyPrint = NC_MAGENTA;
			// }
			ite = itP->getLinks().end();
			for (it = itP->getLinks().begin(); it != ite; it++)
			{
				this->item_form.x = it->getX() * BLOCK_SIZE;
				this->item_form.y = it->getY() * BLOCK_SIZE;
				if (head)
				{
					if (dir == UP)
						surfacePtr = this->head_u;
					else if (dir == DOWN)
						surfacePtr = this->head_d;
					else if (dir == LEFT)
						surfacePtr = this->head_l;
					else if (dir == RIGHT)
						surfacePtr = this->head_r;
					SDL_BlitSurface(surfacePtr, NULL, this->m_windowsurface, &this->item_form);
					head = false;
				}
				else
					SDL_BlitSurface(this->body, NULL, this->m_windowsurface, &this->item_form);
			}
		}
	}
	SDL_UpdateWindowSurface(this->m_fenetre);
}

void 	SdlImageLib::gameOver( std::string toPrint ) const {}

SdlImageLib		*createLib( void )
{
	return new SdlImageLib();
}

void			deleteLib(SdlImageLib * lib)
{
	delete lib;
}
