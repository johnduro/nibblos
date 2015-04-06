// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TMap.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/17 15:32:10 by mle-roy           #+#    #+#             //
//   Updated: 2015/03/31 15:41:38 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TMAP_HPP
# define TMAP_HPP

#include <vector>
#include <list>
// #include "Player.hpp"
#include "Vector2.class.hpp"
class Player;

struct TMap
{
	Vector2							size;
	std::vector<Player>				snakes;
	std::list<Vector2>				foods;
	std::list<Vector2>				rocks;
	bool							pause;
	bool							isEnded;
};

#endif // ** TMAP_HPP ** //
