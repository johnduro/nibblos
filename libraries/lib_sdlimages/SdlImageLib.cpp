#include "SdlImageLib.hpp"
#include "Player.hpp"
// Constructeur de Destucteur

SdlImageLib::SdlImageLib( void )
	: m_titreFenetre("SNAKE"), m_largeurFenetre(1200), m_hauteurFenetre(800), m_fenetre(0), police(NULL), texte(NULL) {}

void 	SdlImageLib::initLibrary( TMap & map )
{
	this->_inputArray[SDLK_ESCAPE] = STD_EXIT;

	this->_inputArray[SDLK_RIGHT] = STD_RIGHT;
	this->_inputArray[SDLK_LEFT] = STD_LEFT;
	this->_inputArray[SDLK_UP] = STD_UP;
	this->_inputArray[SDLK_DOWN] = STD_DOWN;

	this->_inputArray[SDLK_d] = STD_RIGHT_P2;
	this->_inputArray[SDLK_a] = STD_LEFT_P2;
	this->_inputArray[SDLK_w] = STD_UP_P2;
	this->_inputArray[SDLK_s] = STD_DOWN_P2;

	this->_inputArray[SDLK_F1] = STD_LIB1;
	this->_inputArray[SDLK_F2] = STD_LIB2;
	this->_inputArray[SDLK_F3] = STD_LIB3;

	this->m_largeurFenetre = map.size.getX();
	this->m_hauteurFenetre = map.size.getY();

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Quit();
		throw LibraryException(std::string("SDLImage-Lib: Erreur lors de l'initialisation de la SDL : ") + SDL_GetError());
	}

	this->m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->m_largeurFenetre * BLOCK_SIZE, this->m_hauteurFenetre * BLOCK_SIZE, SDL_WINDOW_SHOWN);

	if (this->m_fenetre == NULL)
	{
		SDL_Quit();
		throw LibraryException(std::string("SDLImage-Lib: Erreur lors de la creation de la fenetre : ") + SDL_GetError());
	}
	this->m_windowsurface = SDL_GetWindowSurface(this->m_fenetre);

	this->body = SDL_LoadBMP("libraries/lib_sdlimages/img/body.bmp");
	this->head_d = SDL_LoadBMP("libraries/lib_sdlimages/img/head_d.bmp");
	this->head_u = SDL_LoadBMP("libraries/lib_sdlimages/img/head_u.bmp");
	this->head_l = SDL_LoadBMP("libraries/lib_sdlimages/img/head_l.bmp");
	this->head_r = SDL_LoadBMP("libraries/lib_sdlimages/img/head_r.bmp");
	this->food = SDL_LoadBMP("libraries/lib_sdlimages/img/food.bmp");
	this->bonus = SDL_LoadBMP("libraries/lib_sdlimages/img/bonus.bmp");
	this->rock = SDL_LoadBMP("libraries/lib_sdlimages/img/rock.bmp");

	if (this->bonus == NULL || this->body == NULL || this->head_d == NULL || this->head_u == NULL || this->head_l == NULL || this->head_r == NULL || this->food == NULL || this->rock == NULL)
		throw LibraryException("SDLImage-Lib: SDL_LoadBMP could not load the picture(s)");

	if( TTF_Init() == -1 )
		throw LibraryException(std::string("SDLImage-Lib: SDL_ttf could not initialize! SDL_ttf Error : ") + TTF_GetError());

	/* Chargement de la police */
	police = TTF_OpenFont("libraries/font/angelina.ttf", 25);
	police_pause = TTF_OpenFont("libraries/font/angelina.ttf", 70);
	if( police == NULL || police_pause == NULL)
		throw LibraryException(std::string("SDLImage-Lib: Failed to load lazy font! SDL_ttf Error : ") + TTF_GetError());
}

SdlImageLib::~SdlImageLib() {}

void	SdlImageLib::closeLibrary( void )
{
	TTF_CloseFont(police);
	TTF_Quit();
	SDL_FreeSurface(texte);

	SDL_DestroyWindow(m_fenetre);
	SDL_Quit();
}

// Methodes

int		SdlImageLib::getInput( void )
{
		// Gestion des evenements

	SDL_PollEvent(&(this->m_evenements));

	if (this->m_evenements.window.event == SDL_WINDOWEVENT_CLOSE)
		return STD_EXIT;
	if (this->m_evenements.window.event == SDLK_SPACE)
	{
		this->m_evenements.window.event = 0;
		return STD_SPACE;
	}
	if (this->_inputArray.find(this->m_evenements.key.keysym.sym) != this->_inputArray.end())
		return (this->_inputArray[this->m_evenements.key.keysym.sym]);

	return 0;
}

void		SdlImageLib::printMap( TMap const & map )
{
	SDL_Surface		*surfacePtr;
	bool			print = false;

	SDL_FillRect(this->m_windowsurface, NULL, SDL_MapRGB(this->m_windowsurface->format, 255, 255, 255));

	std::list<Vector2>::const_iterator		it;
	std::list<Vector2>::const_iterator		ite;

	std::vector<Player>::const_iterator		itP;
	std::vector<Player>::const_iterator		iteP;

	SDL_Color RED = {255, 0, 0};
	SDL_Color BLUE = {0, 0, 255};
	SDL_Color GREEN = {0, 150, 0};

	if (map.bonus != Vector2(-1, -1))
	{
		this->item_form.x = map.bonus._x * BLOCK_SIZE;
		this->item_form.y = map.bonus._y * BLOCK_SIZE;
		SDL_BlitSurface(this->bonus, NULL, this->m_windowsurface, &this->item_form);
	}

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
	int i = 0;
	if (map.snakes.size() > 0)
	{
		bool		head;
		Vector2		dir;

		iteP = map.snakes.end();
		for (itP = map.snakes.begin(); itP != iteP; itP++)
		{
			std::stringstream ss;
			ss << itP->getName() << "     " << itP->getScore();
			std::string name = ss.str();
			this->position.x = 25;

			if (i == 0)
			{
				texte = TTF_RenderText_Blended(police, name.c_str(), RED);
				this->position.y = 5;
			}
			else
			{
				texte = TTF_RenderText_Blended(police, name.c_str(), BLUE);
				this->position.y = 25;
			}

			SDL_BlitSurface(this->texte, NULL, this->m_windowsurface, &position); /* Blit du texte */

			head = true;
			dir = itP->getDir();

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
			i++;
		}
	}

	if (map.isEnded)
	{
		position.x = ((m_largeurFenetre*BLOCK_SIZE) / 2) - 100;
		position.y = ((m_hauteurFenetre*BLOCK_SIZE) / 2) - 100;
		texte = TTF_RenderText_Blended(police_pause, "GameOver", GREEN);
		SDL_BlitSurface(this->texte, NULL, this->m_windowsurface, &position);

		position.x = ((m_largeurFenetre*BLOCK_SIZE) / 2) - 100;

		if (!(map.snakes.front().isAlive()))
		{
			position.y = ((m_hauteurFenetre*BLOCK_SIZE) / 2);
			std::string print = map.snakes.front().getName() + map.snakes.front().getDeathReason();
			texte = TTF_RenderText_Blended(police, print.c_str(), RED);
			SDL_BlitSurface(this->texte, NULL, this->m_windowsurface, &position);
		}
		if (map.snakes.size() > 1 && !(map.snakes.back().isAlive()))
		{
			position.y = ((m_hauteurFenetre*BLOCK_SIZE) / 2) + 50;
			std::string print = map.snakes.back().getName() + map.snakes.back().getDeathReason();
			texte = TTF_RenderText_Blended(police, print.c_str(), BLUE);
			SDL_BlitSurface(this->texte, NULL, this->m_windowsurface, &position);
		}
	}
	else
	{
		if (map.pause)
		{
			position.x = ((m_largeurFenetre*BLOCK_SIZE) / 2) - 50;
			position.y = ((m_hauteurFenetre*BLOCK_SIZE) / 2) - 100;
			texte = TTF_RenderText_Blended(police_pause, "PAUSE", GREEN);
			SDL_BlitSurface(this->texte, NULL, this->m_windowsurface, &position);
		}
	}

	SDL_UpdateWindowSurface(this->m_fenetre);
}

SdlImageLib		*createLib( void ) {return new SdlImageLib();}

void			deleteLib(SdlImageLib * lib) {delete lib;}

char		getType( void )
{
	return 'g';
}
