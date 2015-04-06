// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   NCurseLib.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/17 17:07:38 by mle-roy           #+#    #+#             //
//   Updated: 2015/04/06 19:09:40 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef NCURSELIB_HPP
# define NCURSELIB_HPP

#include <ncurses.h>
#include <map>
#include "IGraphicLib.hpp"

# define NC_LEFT 260
# define NC_RIGHT 261
# define NC_UP 259
# define NC_DOWN 258
# define NC_SPACE 32
# define NC_EXIT 27
# define NC_PLUS 43
# define NC_MINUS 45
# define NC_LEFT_P2 97
# define NC_RIGHT_P2 100
# define NC_UP_P2 119
# define NC_DOWN_P2 115

# define NC_WHITE 1
# define NC_RED 2
# define NC_GREEN 3
# define NC_YELLOW 4
# define NC_MAGENTA 5
# define NC_BW 6

class NCurseLib : public IGraphicLib
{
private:
	int						_scoreSize;
	bool					_isInit;
	WINDOW					*_field;
	WINDOW					*_score;
	std::map<int, int>		_inputArray;

	NCurseLib(NCurseLib const & src);
	NCurseLib &		operator=(NCurseLib const & src);

	void	_refresh( void ) const;
	void	_drawBorders(WINDOW *screen) const;
	void	_printEntity(Vector2 coord, char toPrint, int colorPair, Vector2 mapSize);
	void	_clearWin( WINDOW *screen);
	void	_printScores( TMap const & map );
	void	_printPause( TMap const & map );

public:
	void			printMap( TMap const & map );
	int				getInput( void );
	void			initLibrary( TMap & map );
	void			closeLibrary( void );
	~NCurseLib( void );
	NCurseLib( void );

};

extern "C" {
	NCurseLib		*createLib( void );
	void			deleteLib( NCurseLib * lib );
	char			getType( void );
}

#endif // ** NCURSELIB_HPP ** //
