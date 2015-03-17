// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   NCurseLib.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/17 17:07:38 by mle-roy           #+#    #+#             //
//   Updated: 2015/03/17 20:17:13 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef NCURSELIB_HPP
# define NCURSELIB_HPP

#include <ncurses.h>
#include "IGraphicLib.hpp"

# define NC_LEFT 260
# define NC_RIGHT 261
# define NC_EXIT 27

class NCurseLib : public IGraphicLib
{
private:
	int				_scoreSize;
	bool			_isInit;
	WINDOW			*_field;
	WINDOW			*_score;

	NCurseLib(NCurseLib const & src);
	NCurseLib &		operator=(NCurseLib const & src);

	void	_refresh( void ) const;
	void	_drawBorders(WINDOW *screen) const;

public:
	void	printMap(TMap & map) const;
	int		getInput( void ) const;
	void	gameOver( std::string toPrint ) const;
	void	initLibrary( TMap & map );
	void	closeLibrary( void );
	~NCurseLib( void );
	NCurseLib( void );

};

extern "C" {
	NCurseLib		*createLib( void );
	void			deleteLib( NCurseLib * lib );
}

#endif // ** NCURSELIB_HPP ** //
