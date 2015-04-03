// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   NCurseLib.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/17 17:17:43 by mle-roy           #+#    #+#             //
//   Updated: 2015/04/03 19:24:22 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <stdlib.h>
#include "NCurseLib.hpp"
#include "Player.hpp"

NCurseLib::NCurseLib( void ) : _scoreSize(4), _isInit(false)
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

void	NCurseLib::_printEntity(Vector2 coord, char toPrint, int colorPair, Vector2 mapSize)
{
	if (coord.getX() >= 0 && coord.getX() <= mapSize.getX() && coord.getY() >= 0 && coord.getY() <= mapSize.getY())
		mvwaddch(this->_field, coord.getY() + 1 , coord.getX() + 1, toPrint | COLOR_PAIR(colorPair));
}

void	NCurseLib::_clearWin( WINDOW *screen )
{
	int		y;
	int		x;
	int		mY;
	int		mX;

	getmaxyx(screen, mY, mX);
	for (y = 1; y <= (mY - 1); y++)
	{
		for (x = 1; x <= (mX - 1); x++)
			mvwaddch(screen, y , x,  ' ');
	}
}


void	NCurseLib::_printPause( TMap const & map )
{
	int		x;
	int		y;

	x = (map.size.getX() / 2) - 4;
	y = map.size.getY() / 2;
	mvwprintw(this->_field, y - 1, x, "*********");
	mvwprintw(this->_field, y, x, "* PAUSE *");
	mvwprintw(this->_field, y + 1, x, "*********");
}

void	NCurseLib::_printScores( TMap const & map )
{
	std::string		print;

	this->_clearWin(this->_score);
	this->_drawBorders(this->_score);
	if (!(map.isEnded))
	{
		print = map.snakes.front().getName() + " : " + std::to_string(map.snakes.front().getScore());
		mvwprintw(this->_score, 1, 1, print.c_str());
		if (map.snakes.size() > 1)
		{
			print = map.snakes.back().getName() + " : " + std::to_string(map.snakes.back().getScore());
			mvwprintw(this->_score, 2, 1, print.c_str());
		}
	}
	else
	{
		if (!(map.snakes.front().isAlive()))
		{
			print = map.snakes.front().getName() + map.snakes.front().getDeathReason();
			mvwprintw(this->_score, 1, 1, print.c_str());
		}
		if (map.snakes.size() > 1 && !(map.snakes.back().isAlive()))
		{
			print = map.snakes.back().getName() + map.snakes.back().getDeathReason();
			mvwprintw(this->_score, 2, 1, print.c_str());
		}
	}
}

void	NCurseLib::printMap( TMap const & map )
{
	std::list<Vector2>::const_iterator		it;
	std::list<Vector2>::const_iterator		ite;

	std::vector<Player>::const_iterator		itP;
	std::vector<Player>::const_iterator		iteP;

	this->_clearWin(this->_field);
	this->_drawBorders(this->_field);

	if (map.rocks.size() > 0)
	{
		ite = map.rocks.end();
		for (it = map.rocks.begin(); it != ite; it++)
			this->_printEntity(*it, '%', NC_RED, map.size);
	}
	if (map.foods.size() > 0)
	{
		ite = map.foods.end();
		for (it = map.foods.begin(); it != ite; it++)
			this->_printEntity(*it, '@', NC_GREEN, map.size);
	}
	if (map.snakes.size() > 0)
	{
		bool		head;
		int			headPrint = NC_MAGENTA;
		int			bodyPrint = NC_YELLOW;

		iteP = map.snakes.end();
		for (itP = map.snakes.begin(); itP != iteP; itP++)
		{
			head = true;
			if (itP != map.snakes.begin())
			{
				headPrint = NC_YELLOW;
				bodyPrint = NC_MAGENTA;
			}
			ite = itP->getLinks().end();
			for (it = itP->getLinks().begin(); it != ite; it++)
			{
				if (head)
				{
					this->_printEntity(*it, '@', headPrint, map.size);
					head = false;
				}
				else
					this->_printEntity(*it, '#', bodyPrint, map.size);
			}
		}
	}

	this->_printScores(map);
	if (map.pause)
		this->_printPause(map);
	this->_refresh();
}

int		NCurseLib::getInput( void )
{
	int		input;

	input = getch();
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
		case KEY_F(1):
			return (STD_LIB1);
		case KEY_F(2):
			return (STD_LIB2);
		case KEY_F(3):
			return (STD_LIB3);
	}
	return (0);
}

void	NCurseLib::gameOver( std::string toPrint ) const
{
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
	start_color();
	init_pair(NC_WHITE, COLOR_WHITE, COLOR_BLACK);
	init_pair(NC_RED, COLOR_RED, COLOR_BLACK);
	init_pair(NC_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(NC_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(NC_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(NC_BW, COLOR_BLACK, COLOR_WHITE);
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
