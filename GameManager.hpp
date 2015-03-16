// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/16 19:55:34 by mle-roy           #+#    #+#             //
//   Updated: 2015/03/16 20:48:31 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GAMEMANAGER_HPP
# define GAMEMANAGER_HPP

#include <vector>
#include <list>
#include "Player.hpp"
#include "ft_timer.hpp"

struct t_map
{
	Vector2		size;
	char		**map;
};

class GameManager
{
private:
	t_map							_map;
	int								_players;
	ft_timer						_timer;
	std::vector<Player>				_snakes;
	std::list<Vector2>				_foods;
	std::vector<std::string>		_libs;
	std::string						_endGame;
	IGraphicLib *					_lib;

	bool			_updateMap( void );
	void			_initMap(Vector2 size);
	GameManager( void );
	GameManager(GameManager const &src);
	GameManager &	operator=(GameManager const &rhs);

public:
	GameManager(int players, Vector2 size, std::vector<std::string> libs);
	~GameManager();

	void	Update();
};

#endif // ** GAMEMANAGER_HPP ** //
