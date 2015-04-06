// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/16 19:55:34 by mle-roy           #+#    #+#             //
//   Updated: 2015/04/06 12:48:29 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GAMEMANAGER_HPP
# define GAMEMANAGER_HPP

#include <vector>
#include <list>
#include <map>
#include "Player.hpp"
#include "ft_timer.hpp"
#include "TMap.hpp"
#include "IGraphicLib.hpp"
#include "ISoundLib.hpp"
#include "IMenuLib.hpp"

# define TIME_BASE 300000

class GameManager
{
private:

	typedef void  (GameManager::*inputFunctionPtr)(int input);

	TMap							_map;
	int								_players;
	ft_timer						_timer;
	std::vector<std::string>		_libs;
	IGraphicLib *					_lib;
	ISoundLib *						_libSound;
	IMenuLib *						_libMenu;
	void *							_dl_handle;
	void *							_dl_handle_sound;
	void *							_dl_handle_menu;
	bool							_isLibInit;
	bool							_isLibSoundInit;
	bool							_isLibMenuInit;
	int								_input;
	int								_timeTick;
	bool							_isExited;
	std::map<int, inputFunctionPtr>	_inputFunction;
	std::string						_initiatedLib;
	TOption							_options;
	unsigned long					_nbObstacles;

	void			_playerOneMvt( int input );
	void			_gamePause( int input );
	void			_gameExit( int input );
	void			_gameSpeed( int input );
	void			_gameLib( int input );
	void			_playerTwoMvt( int input );


	void			_updateMap( void );
	void			_eatFood( Player & play );
	void			_initMap( Vector2 size );
	void			_checkInput( void );
	void			_movesSnakes( void );
	void			_generateFood( void );
	void			_generateRocks( void );
	void			_initLib( std::string lib );
	void			_initSoundLib( void );
	void			_initMenuLib( void );
	void			_closeLib( void );
	void			_closeSoundLib( void );
	void			_closeMenuLib( void );
	void			_setMap( void );
	void			_changeTimer( int input );
	void			_playerCollision( Player & play, std::string const & reason);
	bool			_checkCollision(Vector2 somePlace, std::list<Vector2>::const_iterator it, std::list<Vector2>::const_iterator ite);
	void			_generateFirstState( void );



	GameManager( void );
	GameManager(GameManager const &src);
	GameManager &	operator=(GameManager const &rhs);

public:
	GameManager(int players, Vector2 size, std::vector<std::string> libs);
	~GameManager();

	void	Update();

	class GameManagerException : public std::runtime_error
	{
	private:
		GameManagerException const & operator=(GameManagerException const &) throw();
		GameManagerException() throw();

	public:
		GameManagerException(std::string const & errorMsg) throw();
		~GameManagerException() throw();
		virtual const char* 		what() const throw();

	};
};

#endif // ** GAMEMANAGER_HPP ** //
