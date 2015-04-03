// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MenuLib.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/02 13:34:34 by mle-roy           #+#    #+#             //
//   Updated: 2015/04/03 13:00:01 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MENULIB_HPP
# define MENULIB_HPP

#include <ncurses.h>
#include "IMenuLib.hpp"

// START
// MULTIPLAYER
// OPTIONS
// EXIT

# define MENU_HEIGHT 12
# define MENU_LENGTH 41
# define M_SELECTED 1
# define M_UNSELECTED 2

# define NC_LEFT 260
# define NC_RIGHT 261
# define NC_UP 259
# define NC_DOWN 258
# define NC_ENTER 32
# define NC_EXIT 27
# define P1 1
# define P2 2

struct mainMenu
{
	bool		s;
	bool		m;
	bool		o;
	bool		e;
};

struct multiMenu
{
	bool		m;
	bool		p1;
	bool		p2;
	bool		b;
};

struct optionsMenu
{
	bool		s;
	bool		o;
	bool		b;
};

class MenuLib : public IMenuLib
{
private :
	TOption			_opt;
	WINDOW			*_menuWin;

	bool				_start;
	bool				_main;
	bool				_multi;
	bool				_options;
	bool				_exit;
	mainMenu			_mainS;
	multiMenu			_multiS;
	optionsMenu			_optionS;

	void			_initOpt( void );
	void			_initNCurses( void );
	void			_menuLoop( void );
	void			_clearNCurses( void );
	void			_drawMenuBorders( void );
	void			_mainLoop( void );
	void			_multiLoop( void );
	void			_optionsLoop( void );
	void			_mainInput( int input );
	void			_multiInput( int input );
	void			_optionsInput( int input );
	void			_printMain( void );
	void			_printMulti( void );
	void			_printOptions( void );
	void			_getPlayerName( char player, const char *str);
	// void			_printString(WINDOW *win, int y, int x, const char *str, int pair);
	void			_printString(WINDOW *win, int y, int x, const char *str, bool selected);


public :
	MenuLib( void );
	~MenuLib( void );
	TOption		startMenu( void );
	// TOption		getMenuOption( void );
};

extern "C" {
	MenuLib		*createLib( void );
	void		deleteLib( MenuLib * lib );
}

#endif // ** MENULIB_HPP ** //
