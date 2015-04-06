
#ifndef SDLIMAGELIB_HPP
# define SDLIMAGELIB_HPP

// Includes

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <unistd.h>

#include "LibraryException.hpp"
#include "IGraphicLib.hpp"
#include "TMap.hpp"

#include "Vector3.class.hpp"

# define BLOCK_SIZE 25

// Classe

class SdlImageLib : IGraphicLib
{
public:

    SdlImageLib( void );
    ~SdlImageLib( void );

    void		initLibrary( TMap & map );
    void		closeLibrary( void );
    void		printMap( TMap const & map );
    int			getInput( void );

private:

    std::string		m_titreFenetre;
    int				m_largeurFenetre;
    int				m_hauteurFenetre;

	SDL_Surface		*rock;
	SDL_Surface		*food;
	SDL_Surface		*body;
	SDL_Surface		*head_u;
	SDL_Surface		*head_d;
	SDL_Surface		*head_l;
	SDL_Surface		*head_r;

	SDL_Rect item_form;

    SDL_Window*		m_fenetre;
	SDL_Surface*	m_windowsurface;
    SDL_Event		m_evenements;

    TTF_Font *police;
    TTF_Font *police_pause;
    SDL_Rect position;
    SDL_Surface *texte;

    std::map<int, int>		_inputArray;
};

extern "C" {
	SdlImageLib		*createLib( void );
	void			deleteLib( SdlImageLib * lib );
}

#endif // ** SDLIMAGELIB_HPP ** //
