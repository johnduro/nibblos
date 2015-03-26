// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   NCurseLib.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/17 17:17:43 by mle-roy           #+#    #+#             //
//   Updated: 2015/03/26 14:40:15 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <stdlib.h>
#include "NCurseLib.hpp"

NCurseLib::NCurseLib( void ) : _scoreSize(3), _isInit(false)
{

}

NCurseLib::~NCurseLib( void )
{
	if (this->_isInit)
		endwin();
}

void					NCurseLib::_refresh( void ) const
{
	wrefresh(this->_field);
	wrefresh(this->_score);
}

void					NCurseLib::_drawBorders(WINDOW *screen) const
{
	int		x;
	int		y;
	int		i;

	getmaxyx(screen, y, x);
	mvwprintw(screen, 0, 0, "+");
	mvwprintw(screen, y - 1, 0, "+");
	mvwprintw(screen, 0, x - 1, "+");
	mvwprintw(screen, y - 1, x - 1, "+");
	for (i = 1; i < (y - 1); i++)
	{
		mvwprintw(screen, i, 0, "|");
		mvwprintw(screen, i, x - 1, "|");
	}
	for (i = 1; i < (x - 1); i++)
	{
		mvwprintw(screen, 0, i, "-");
		mvwprintw(screen, y - 1, i, "-");
	}
}

void	NCurseLib::printMap(TMap & map)
{
	int		y = 1;
	int		x;

	this->_drawBorders(this->_field);
	this->_drawBorders(this->_score);
	// std::cout << "mapY : " << map.size.getY() << std::endl << "mapX : " << map.size.getX() << std::endl;
	while (y <= map.size.getY())
	{
		x = 1;
		// std::cout << "YY - " << y << std::endl;
		while (x <= map.size.getX())
		{
			// std::cout << "XX - " << x << std::endl;
			// std::cout << "char ->" << map.map[y][x] << "<-" << std::endl;
			mvwaddch(this->_field, y, x, map.map[y - 1][x - 1]);
			x++;
		}
		y++;
	}
	// wclear(this->_score);
	mvwprintw(this->_score, 1, 1, map.scores.c_str());
	this->_refresh();
}

int		NCurseLib::getInput( void )
{
	int		input;

	input = getch();
	// if (input != -1)
	// 	std::cout << "INPUT : " << input << std::endl;
	switch (input)
	{
		case NC_LEFT:
			return (STD_LEFT);
		case NC_RIGHT:
			return (STD_RIGHT);
		case NC_UP:
			return (STD_UP);
		case NC_DOWN:
			return (STD_DOWN);
		case NC_EXIT:
			return (STD_EXIT);
		case NC_SPACE:
			return (STD_SPACE);
		case NC_PLUS:
			return (STD_PLUS);
		case NC_MINUS:
			return (STD_MINUS);
	}
	return (0);
}

void	NCurseLib::gameOver( std::string toPrint ) const
{
	// mvwprintw(this->_score, 1, 1, "SCORE : ");
	// wclear(this->_score);
	mvwprintw(this->_score, 1, 1, toPrint.c_str());
}

void	NCurseLib::initLibrary( TMap & map )
{
	int		maxY;
	int		maxX;

	initscr();
	clear();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	timeout(0);
	getmaxyx(stdscr, maxY, maxX);
	if (((map.size.getY() + 2) + this->_scoreSize) >= maxY || (map.size.getX() + 2) >= maxX )
	{
		std::cout << "FAIL TROP PETIT" << std::endl;
		exit(-1);
	}
	this->_field = newwin((map.size.getY() + 2), (map.size.getX() + 2), 0, 0);
	this->_score = newwin(this->_scoreSize, (map.size.getX() + 2), (map.size.getY() + 2), 0);
	this->_refresh();
	this->_drawBorders(this->_field);
	this->_drawBorders(this->_score);
	this->_isInit = true;
}

void	NCurseLib::closeLibrary( void )
{
	if (this->_isInit)
		endwin();
	this->_isInit = false;
}

NCurseLib		*createLib( void )
{
	return new NCurseLib();
}

void			deleteLib( NCurseLib * lib )
{
	delete lib;
}
