// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TMap.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/17 15:32:10 by mle-roy           #+#    #+#             //
//   Updated: 2015/03/18 17:49:28 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TMAP_HPP
# define TMAP_HPP

#include "Vector2.class.hpp"

struct TMap
{
	Vector2			size;
	char			**map;
	std::string		scores;
};

#endif // ** TMAP_HPP ** //
