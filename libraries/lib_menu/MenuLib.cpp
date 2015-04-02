
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
	// timeout(0);
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
	wrefresh(this->_menuWin);
	// this->_refresh();
	this->_drawMenuBorders();
	// this->_drawBorders(this->_score);
	// wbkgd(this->_score, COLOR_PAIR(BW));
	// this->_isInit = true;
}

void		MenuLib::_printMain( void )
{
	if (this->_mainS.s)
		mvwprintw(this->_menuWin, 4, 18, "START" | COLOR_PAIR(M_SELECTED));
	else
		mvwprintw(this->_menuWin, 4, 18, "START" | COLOR_PAIR(M_UNSELECTED));

	if (this->_mainS.m)
		mvwprintw(this->_menuWin, 5, 15, "MULTIPLAYER" | COLOR_PAIR(M_SELECTED));
	else
		mvwprintw(this->_menuWin, 5, 15, "MULTIPLAYER" | COLOR_PAIR(M_UNSELECTED));

	if (this->_mainS.o)
		mvwprintw(this->_menuWin, 6, 17, "OPTIONS" | COLOR_PAIR(M_SELECTED));
	else
		mvwprintw(this->_menuWin, 6, 17, "OPTIONS" | COLOR_PAIR(M_UNSELECTED));

	if (this->_mainS.e)
		mvwprintw(this->_menuWin, 7, 18, "EXIT" | COLOR_PAIR(M_SELECTED));
	else
		mvwprintw(this->_menuWin, 7, 18, "EXIT" | COLOR_PAIR(M_UNSELECTED));
}

void		MenuLib::_printMulti( void )
{
	if (this->_multiS.m)
		mvwprintw(this->_menuWin, 4, 18, "MULTIPLAYER" | COLOR_PAIR(M_SELECTED));
	else
		mvwprintw(this->_menuWin, 4, 18, "MULTIPLAYER" | COLOR_PAIR(M_UNSELECTED));

	if (this->_opt.twoPlayers)
		mvwprintw(this->_menuWin, 4, 23, " ON");
	else
		mvwprintw(this->_menuWin, 4, 23, " OFF");

	if (this->_multiS.p1)
		mvwprintw(this->_menuWin, 5, 15, "PLAYER 1 NAME" | COLOR_PAIR(M_SELECTED));
	else
		mvwprintw(this->_menuWin, 5, 15, "PLAYER 1 NAME" | COLOR_PAIR(M_UNSELECTED));

	if (this->_multiS.p2)
		mvwprintw(this->_menuWin, 6, 17, "PLAYER 2 NAME" | COLOR_PAIR(M_SELECTED));
	else
		mvwprintw(this->_menuWin, 6, 17, "PLAYER 2 NAME" | COLOR_PAIR(M_UNSELECTED));

	if (this->_multiS.b)
		mvwprintw(this->_menuWin, 7, 18, "BACK" | COLOR_PAIR(M_SELECTED));
	else
		mvwprintw(this->_menuWin, 7, 18, "BACK" | COLOR_PAIR(M_UNSELECTED));
}

void		MenuLib::_printOptions( void )
{
	if (this->_optionS.s)
		mvwprintw(this->_menuWin, 4, 17, "SOUND" | COLOR_PAIR(M_SELECTED));
	else
		mvwprintw(this->_menuWin, 4, 17, "SOUND" | COLOR_PAIR(M_UNSELECTED));

	if (this->_opt.sound)
		mvwprintw(this->_menuWin, 4, 23, " ON");
	else
		mvwprintw(this->_menuWin, 4, 23, " OFF");

	if (this->_optionS.o)
		mvwprintw(this->_menuWin, 5, 15, "OBSTACLES" | COLOR_PAIR(M_SELECTED));
	else
		mvwprintw(this->_menuWin, 5, 15, "OBSTACLES" | COLOR_PAIR(M_UNSELECTED));

	if (this->_opt.obstacles)
		mvwprintw(this->_menuWin, 5, 25, " ON");
	else
		mvwprintw(this->_menuWin, 5, 25, " OFF");

	if (this->_optionS.b)
		mvwprintw(this->_menuWin, 6, 19, "BACK" | COLOR_PAIR(M_SELECTED));
	else
		mvwprintw(this->_menuWin, 6, 19, "BACK" | COLOR_PAIR(M_UNSELECTED));
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

void			MenuLib::_getPlayerName( char player, char *str)
{
	char		buff[80];

	clear();
	this->_drawMenuBorders();
	mvwprintw(this->_menuWin, 5, 10, str | COLOR_PAIR(M_UNSELECTED));
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

void		MenuLip::_mainLoop( void )
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
		this->_mainInput(input);
	}
}

void		MenuLip::_multiLoop( void )
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
			this->_exit = true;
		this->_multiInput(input);
	}
}

void		MenuLip::_optionsLoop( void )
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
		this->_optionsInput(input);
	}
}

void		MenuLib::_menuLoop( void )
{
	while (42)
	{
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
