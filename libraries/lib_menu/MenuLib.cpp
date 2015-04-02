
#include <iostream>
#include "MenuLib.hpp"

MenuLib::MenuLib( void )
	: _start(false), _main(true), _multi(false), _options(false), _exit(false)
{
	this->_mainS.s = true;
	this->_mainS.m = false;
	this->_mainS.o = false;
	this->_mainS.e = false;
	this->_multiS.m = true;
	this->_multiS.p1 = false;
	this->_multiS.p2 = false;
	this->_multiS.b = false;
	this->_optionS.s = true;
	this->_optionS.o = false;
	this->_optionS.b = false;
}

MenuLib::~MenuLib( void )
{

}

void			MenuLib::_drawMenuBorders( void )
{
	int		x;
	int		y;
	int		i;

	getmaxyx(this->_menuWin, y, x);
	for (i = 0; i < y; i++)
	{
		mvwprintw(this->_menuWin, i, 0, "<");
		mvwprintw(this->_menuWin, i, x - 1, ">");
	}
	for (i = 1; i < (x - 1); i++)
	{
		mvwprintw(this->_menuWin, 0, i, "-");
		mvwprintw(this->_menuWin, y - 1, i, "-");
	}
	wrefresh(this->_menuWin);
}

void		MenuLib::_initNCurses( void )
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
	init_pair(M_UNSELECTED, COLOR_WHITE, COLOR_BLACK);
	init_pair(M_SELECTED, COLOR_BLACK, COLOR_WHITE);
	// init_pair(NC_RED, COLOR_RED, COLOR_BLACK);
	// init_pair(NC_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	// init_pair(NC_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
	// init_pair(NC_GREEN, COLOR_GREEN, COLOR_BLACK);
	getmaxyx(stdscr, maxY, maxX);
	if ( MENU_HEIGHT >= maxY || MENU_LENGTH >= maxX )
	{
		std::cout << "MENU FENETRE TROP PETIT" << std::endl;
		exit(-1);
	}
	this->_menuWin = newwin(MENU_HEIGHT, MENU_LENGTH, 0, 0);
	// this->_score = newwin(this->_scoreSize, (map.size.getX() + 2), (map.size.getY() + 2), 0);
	// this->_refresh();
	this->_drawMenuBorders();
	wrefresh(this->_menuWin);
	// this->_drawBorders(this->_score);
	// wbkgd(this->_score, COLOR_PAIR(BW));
	// this->_isInit = true;
}

void		MenuLib::_printString(WINDOW *win, int y, int x, const char *str, int pair)
{
	attron(COLOR_PAIR(pair));
	mvwprintw(win, y, x, str);
	attroff(COLOR_PAIR(pair));
}

void		MenuLib::_printMain( void )
{
	if (this->_mainS.s)
		this->_printString(this->_menuWin, 4, 18, "START", M_SELECTED);
	else
		this->_printString(this->_menuWin, 4, 18, "START", M_UNSELECTED);

	if (this->_mainS.m)
		this->_printString(this->_menuWin, 5, 15, "MULTIPLAYER", M_SELECTED);
	else
		this->_printString(this->_menuWin, 5, 15, "MULTIPLAYER", M_UNSELECTED);

	if (this->_mainS.o)
		this->_printString(this->_menuWin, 6, 17, "OPTIONS", M_SELECTED);
	else
		this->_printString(this->_menuWin, 6, 17, "OPTIONS", M_UNSELECTED);

	if (this->_mainS.e)
		this->_printString(this->_menuWin, 7, 18, "EXIT", M_SELECTED);
	else
		this->_printString(this->_menuWin, 7, 18, "EXIT", M_UNSELECTED);
	wrefresh(this->_menuWin);
}

void		MenuLib::_printMulti( void )
{
	if (this->_multiS.m)
		this->_printString(this->_menuWin, 4, 18, "MULTIPLAYER", M_SELECTED);
	else
		this->_printString(this->_menuWin, 4, 18, "MULTIPLAYER", M_UNSELECTED);

	if (this->_opt.twoPlayers)
		this->_printString(this->_menuWin, 4, 23, " ON", M_UNSELECTED);
	else
		this->_printString(this->_menuWin, 4, 23, " OFF", M_UNSELECTED);

	if (this->_multiS.p1)
		this->_printString(this->_menuWin, 5, 15, "PLAYER 1 NAME", M_SELECTED);
	else
		this->_printString(this->_menuWin, 5, 15, "PLAYER 1 NAME", M_UNSELECTED);

	if (this->_multiS.p2)
		this->_printString(this->_menuWin, 6, 17, "PLAYER 2 NAME", M_SELECTED);
	else
		this->_printString(this->_menuWin, 6, 17, "PLAYER 2 NAME", M_UNSELECTED);

	if (this->_multiS.b)
		this->_printString(this->_menuWin, 7, 18, "BACK", M_SELECTED);
	else
		this->_printString(this->_menuWin, 7, 18, "BACK", M_UNSELECTED);
	wrefresh(this->_menuWin);
}

void		MenuLib::_printOptions( void )
{
	if (this->_optionS.s)
		this->_printString(this->_menuWin, 4, 17, "SOUND", M_SELECTED);
	else
		this->_printString(this->_menuWin, 4, 17, "SOUND", M_UNSELECTED);

	if (this->_opt.sound)
		this->_printString(this->_menuWin, 4, 23, " ON", M_UNSELECTED);
	else
		this->_printString(this->_menuWin, 4, 23, " OFF", M_UNSELECTED);

	if (this->_optionS.o)
		this->_printString(this->_menuWin, 5, 15, "OBSTACLES", M_SELECTED);
	else
		this->_printString(this->_menuWin, 5, 15, "OBSTACLES", M_UNSELECTED);

	if (this->_opt.obstacles)
		this->_printString(this->_menuWin, 5, 25, " ON", M_UNSELECTED);
	else
		this->_printString(this->_menuWin, 5, 25, " OFF", M_UNSELECTED);

	if (this->_optionS.b)
		this->_printString(this->_menuWin, 6, 19, "BACK", M_SELECTED);
	else
		this->_printString(this->_menuWin, 6, 19, "BACK", M_UNSELECTED);
	wrefresh(this->_menuWin);
}

void		MenuLib::_mainInput( int input )
{
	if (input == KEY_ENTER)
		this->_main = false;
	if (this->_mainS.s)
	{
		if (input == KEY_ENTER)
			this->_start = true;
		else if (input == NC_UP || input == NC_DOWN)
		{
			this->_mainS.s = false;
			if (input == NC_UP)
				this->_mainS.e = true;
			else
				this->_mainS.m = true;
		}
	}
	else if (this->_mainS.m)
	{
		if (input == KEY_ENTER)
			this->_multi = true;
		else if (input == NC_UP || input == NC_DOWN)
		{
			this->_mainS.m = false;
			if (input == NC_UP)
				this->_mainS.s = true;
			else
				this->_mainS.o = true;
		}
	}
	else if (this->_mainS.o)
	{
		if (input == KEY_ENTER)
			this->_options = true;
		else if (input == NC_UP || input == NC_DOWN)
		{
			this->_mainS.o = false;
			if (input == NC_UP)
				this->_mainS.m = true;
			else
				this->_mainS.e = true;
		}
	}
	else if (this->_mainS.e)
	{
		if (input == KEY_ENTER)
		{
			this->_exit = true;
			this->_opt.isExited = true;
		}
		else if (input == NC_UP || input == NC_DOWN)
		{
			this->_mainS.e = false;
			if (input == NC_UP)
				this->_mainS.o = true;
			else
				this->_mainS.s = true;
		}
	}
}

void			MenuLib::_getPlayerName( char player, const char *str)
{
	char		buff[80];

	clear();
	this->_drawMenuBorders();
	this->_printString(this->_menuWin, 5, 10, str, M_UNSELECTED);
	nocbreak();
	echo();
	wmove(this->_menuWin, 6, 12);
	getnstr(buff, 75);
	if (player == P1)
		this->_opt.names.first = std::string(buff);
	else if (player == P2)
		this->_opt.names.second = std::string(buff);
	noecho();
	cbreak();
}


void		MenuLib::_multiInput( int input )
{
	if (this->_multiS.m)
	{
		if (input == KEY_ENTER)
			this->_opt.twoPlayers = !(this->_opt.twoPlayers);
		else if (input == NC_UP || input == NC_DOWN)
		{
			this->_multiS.m = false;
			if (input == NC_UP)
				this->_multiS.b = true;
			else
				this->_multiS.p1 = true;
		}
	}
	else if (this->_multiS.p1)
	{
		if (input == KEY_ENTER)
			this->_getPlayerName(P1, "ENTER PLAYER 1 NAME :");
		else if (input == NC_UP || input == NC_DOWN)
		{
			this->_multiS.p1 = false;
			if (input == NC_UP)
				this->_multiS.m = true;
			else
				this->_multiS.p2 = true;
		}
	}
	else if (this->_multiS.p2)
	{
		if (input == KEY_ENTER)
			this->_getPlayerName(P2, "ENTER PLAYER 2 NAME :");
		else if (input == NC_UP || input == NC_DOWN)
		{
			this->_multiS.p2 = false;
			if (input == NC_UP)
				this->_multiS.p1 = true;
			else
				this->_multiS.b = true;
		}
	}
	else if (this->_multiS.b)
	{
		if (input == KEY_ENTER)
		{
			this->_multi = false;
			this->_main = true;
		}
		else if (input == NC_UP || input == NC_DOWN)
		{
			this->_multiS.b = false;
			if (input == NC_UP)
				this->_multiS.p2 = true;
			else
				this->_multiS.m = true;
		}
	}
}

void		MenuLib::_optionsInput( int input )
{
	if (this->_optionS.s)
	{
		if (input == KEY_ENTER)
			this->_opt.sound = !(this->_opt.sound);
		else if (input == NC_UP || input == NC_DOWN)
		{
			this->_optionS.s = false;
			if (input == NC_UP)
				this->_optionS.b = true;
			else
				this->_optionS.o = true;
		}
	}
	else if (this->_optionS.o)
	{
		if (input == KEY_ENTER)
			this->_opt.obstacles = !(this->_opt.obstacles);
		else if (input == NC_UP || input == NC_DOWN)
		{
			this->_optionS.o = false;
			if (input == NC_UP)
				this->_optionS.s = true;
			else
				this->_optionS.b = true;
		}
	}
	else if (this->_optionS.b)
	{
		if (input == KEY_ENTER)
		{
			this->_options = false;
			this->_main = true;
		}
		else if (input == NC_UP || input == NC_DOWN)
		{
			this->_optionS.o = false;
			if (input == NC_UP)
				this->_optionS.o = true;
			else
				this->_optionS.s = true;
		}
	}
}

void		MenuLib::_mainLoop( void )
{
	int		input;

	clear();
	this->_drawMenuBorders();
	while (42)
	{
		if (this->_start || this->_exit)
			break ;
		this->_printMain();
		input = getch();
		if (input == NC_EXIT)
			this->_exit = true;
		else if (input != -1)
			this->_mainInput(input);
	}
}

void		MenuLib::_multiLoop( void )
{
	int		input;

	clear();
	this->_drawMenuBorders();
	while (42)
	{
		if (this->_multi == false)
			break ;
		this->_printMulti();
		input = getch();
		if (input == NC_EXIT)
		{
			this->_multi = false;
			this->_main = true;
		}
		else if (input != -1)
			this->_multiInput(input);
	}
}

void		MenuLib::_optionsLoop( void )
{
	int		input;

	clear();
	this->_drawMenuBorders();
	while (42)
	{
		if (this->_options == false)
			break ;
		this->_printOptions();
		input = getch();
		if (input == NC_EXIT)
		{
			this->_options = false;
			this->_main = true;
		}
		else if (input != -1)
			this->_optionsInput(input);
	}
}

void		MenuLib::_menuLoop( void )
{
	std::cout << "IN MENU LOOP" << std::endl;
	while (42)
	{
		std::cout << "MENU LOOP" << std::endl;
		if (this->_start || this->_exit)
			break ;
		if (this->_main)
			this->_mainLoop();
		else if (this->_multi)
			this->_multiLoop();
		else if (this->_options)
			this->_optionsLoop();
	}
}

void		MenuLib::_clearNCurses( void )
{
	endwin();
}

void		MenuLib::_initOpt( void )
{
	this->_opt.names.first = "Player 1";
	this->_opt.names.second = "Player 2";
	this->_opt.twoPlayers = false;
	this->_opt.obstacles = false;
	this->_opt.sound = true;
	this->_opt.isExited = false;
}

TOption		MenuLib::startMenu( void )
{
	std::cout << "yyOYOYOYOYOYOYOY" << std::endl;
	this->_initOpt();
	std::cout << "22222222222222yyOYOYOYOYOYOYOY" << std::endl;
	this->_initNCurses();
	std::cout << "33333333333yyOYOYOYOYOYOYOY" << std::endl;
	this->_menuLoop();
	std::cout << "4444444444444yyOYOYOYOYOYOYOY" << std::endl;
	this->_clearNCurses();
	std::cout << "5555555555555yyOYOYOYOYOYOYOY" << std::endl;
	return this->_opt;
}

MenuLib		*createLib( void )
{
	return new MenuLib();
}

void			deleteLib( MenuLib * lib )
{
	delete lib;
}
