
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
	refresh();
}

void		MenuLib::_initNCurses( void )
{
	int		maxY;
	int		maxX;

	if (initscr() == NULL)
		throw LibraryException("NCursesLib : Could not init NCurses");
	clear();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	start_color();
	init_pair(M_UNSELECTED, COLOR_WHITE, COLOR_BLACK);
	init_pair(M_SELECTED, COLOR_BLACK, COLOR_WHITE);
	getmaxyx(stdscr, maxY, maxX);
	if ( MENU_HEIGHT >= maxY || MENU_LENGTH >= maxX )
		throw LibraryException("MenuLib : window too small !");
	if ((this->_menuWin = newwin(MENU_HEIGHT, MENU_LENGTH, 0, 0)) == NULL)
		throw LibraryException("MenuLib : couldn't create Menu Window !");
	this->_drawMenuBorders();
	wrefresh(this->_menuWin);
	refresh();
}

void		MenuLib::_printString(WINDOW *win, int y, int x, const char *str, bool selected)
{
	int		pair = M_UNSELECTED;

	if (selected)
		pair = M_SELECTED;
	wattron(win, COLOR_PAIR(pair));
	mvwprintw(win, y, x, str);
	wattroff(win, COLOR_PAIR(pair));
}

void		MenuLib::_printMain( void )
{
	clear();
	wclear(this->_menuWin);
	refresh();
	wrefresh(this->_menuWin);
	this->_drawMenuBorders();
	this->_printString(this->_menuWin, 4, 18, "START", this->_mainS.s);
	this->_printString(this->_menuWin, 5, 15, "MULTIPLAYER", this->_mainS.m);
	this->_printString(this->_menuWin, 6, 17, "OPTIONS", this->_mainS.o);
	this->_printString(this->_menuWin, 7, 18, "EXIT", this->_mainS.e);
	wrefresh(this->_menuWin);
	refresh();
}

void		MenuLib::_printMulti( void )
{
	clear();
	wclear(this->_menuWin);
	refresh();
	wrefresh(this->_menuWin);
	this->_drawMenuBorders();
	this->_printString(this->_menuWin, 4, 12, "MULTIPLAYER", this->_multiS.m);
	if (this->_opt.twoPlayers)
		this->_printString(this->_menuWin, 4, 24, " ON", false);
	else
		this->_printString(this->_menuWin, 4, 24, " OFF", false);
	this->_printString(this->_menuWin, 5, 13, "PLAYER 1 NAME", this->_multiS.p1);
	this->_printString(this->_menuWin, 6, 13, "PLAYER 2 NAME", this->_multiS.p2);
	this->_printString(this->_menuWin, 7, 18, "BACK",  this->_multiS.b);
	wrefresh(this->_menuWin);
	refresh();
}

void		MenuLib::_printOptions( void )
{
	clear();
	wclear(this->_menuWin);
	refresh();
	wrefresh(this->_menuWin);
	this->_drawMenuBorders();
	this->_printString(this->_menuWin, 4, 17, "SOUND", this->_optionS.s);
	if (this->_opt.sound)
		this->_printString(this->_menuWin, 4, 23, " ON", false);
	else
		this->_printString(this->_menuWin, 4, 23, " OFF", false);
	this->_printString(this->_menuWin, 5, 15, "OBSTACLES", this->_optionS.o);
	if (this->_opt.obstacles)
		this->_printString(this->_menuWin, 5, 25, " ON", false);
	else
		this->_printString(this->_menuWin, 5, 25, " OFF", false);
	this->_printString(this->_menuWin, 6, 19, "BACK", this->_optionS.b);
	wrefresh(this->_menuWin);
	refresh();
}

void		MenuLib::_mainInput( int input )
{
	if (input == NC_ENTER)
		this->_main = false;
	if (this->_mainS.s)
	{
		if (input == NC_ENTER)
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
		if (input == NC_ENTER)
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
		if (input == NC_ENTER)
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
		if (input == NC_ENTER)
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

void			MenuLib::_getPlayerName( char player, const char *str )
{
	char		buff[80];

	clear();
	wclear(this->_menuWin);
	nocbreak();
	echo();
	curs_set(1);
	refresh();

	this->_drawMenuBorders();
	this->_printString(this->_menuWin, 5, 11, str, false);
	wrefresh(this->_menuWin);
	refresh();

	move(6, 12);
	refresh();
	getnstr(buff, 75);
	if (player == P1)
		this->_opt.names.first = std::string(buff);
	else if (player == P2)
		this->_opt.names.second = std::string(buff);
	noecho();
	cbreak();
	curs_set(0);

}

void		MenuLib::_multiInput( int input )
{
	if (this->_multiS.m)
	{
		if (input == NC_ENTER)
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
		if (input == NC_ENTER)
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
		if (input == NC_ENTER)
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
		if (input == NC_ENTER)
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
		if (input == NC_ENTER)
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
		if (input == NC_ENTER)
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
		if (input == NC_ENTER)
		{
			this->_options = false;
			this->_main = true;
		}
		else if (input == NC_UP || input == NC_DOWN)
		{
			this->_optionS.b = false;
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
	refresh();
	while (42)
	{
		if (this->_start || this->_exit || !this->_main)
			break ;
		this->_printMain();
		input = getch();

		if (input == NC_EXIT)
			this->_exit = true;
		else if (input != -1)
			this->_mainInput(input);
		input = -1;
	}
}

void		MenuLib::_multiLoop( void )
{
	int		input;

	clear();
	refresh();

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
		input = -1;
	}
}

void		MenuLib::_optionsLoop( void )
{
	int		input;

	clear();
	refresh();

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
		input = -1;
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
	this->_initOpt();
	this->_initNCurses();
	this->_menuLoop();
	this->_clearNCurses();
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

char		getType( void )
{
	return 'm';
}
