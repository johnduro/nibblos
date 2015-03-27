// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TMap.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/17 15:32:10 by mle-roy           #+#    #+#             //
//   Updated: 2015/03/27 18:54:03 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TMAP_HPP
# define TMAP_HPP

#include "Vector2.class.hpp"

// # define EMPTY 0
// # define FOOD 1
// # define BODY_1 2
// # define HEAD_U_1 3
// # define HEAD_D_1 4
// # define HEAD_L_1 5
// # define HEAD_R_1 6


struct TMap
{
	Vector2			size;
	char			**map;
	std::string		scores;
enum	mapBlock
{
	empty,
	food,
	rock,
	body_1,
	head_u_1,
	head_d_1,
	head_l_1,
	head_r_1,
	body_2,
	head_u_2,
	head_d_2,
	head_l_2,
	head_r_2
};
};

#endif // ** TMAP_HPP ** //
