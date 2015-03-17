/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/16 15:48:46 by ael-kadh          #+#    #+#             */
/*   Updated: 2015/03/17 16:39:48 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iterator>
#include <iostream>
#include <string>
#include <list>
#include "Vector2.class.hpp"

#define LEFT Vector2(-1, 0)
#define RIGHT Vector2(1, 0)
#define DOWN Vector2(0, 1)
#define UP Vector2(0, -1)

class Player
{
private:
	int						_length;
      // Vector2  pos();
	Vector2					_dir;
	// Direction				_dir;
	std::list<Vector2>		_links;
	std::string				_name;
	Vector2 				_last;
	Player( void );

	void		_initFirstSnake(Vector2 pos, Vector2 dir);

public:
      /* ------------ Constructors & Destructors ------------- */

	~Player();
      // Player(Vector2 pos);
	Player(std::string name, Vector2 pos);
	Player(std::string name, Vector2 pos, Vector2 dir);

	Player(Player const &src);
	Player &   operator=(Player const &rhs);

      /* ------------ SETTERS & GETTERS -------------- */

	int								getLength() const ;
	Vector2 const &					getDir() const ;
	std::string const &				getName( void ) const ;
	Vector2 const &					getLast( void ) const ;
	Vector2	const &					getHead( void ) const ;
	std::list<Vector2> const &		getLinks() const ;

	void	addLink();
	void	movSnake();
	void	setDir(Vector2 dir);
	void	setLast();
};

#endif
