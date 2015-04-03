// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IGraphicLib.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/17 15:34:58 by mle-roy           #+#    #+#             //
//   Updated: 2015/04/03 19:48:19 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IGRAPHICLIB_HPP
# define IGRAPHICLIB_HPP

#include "TMap.hpp"

# define STD_LEFT 1
# define STD_RIGHT 2
# define STD_UP 3
# define STD_DOWN 4
# define STD_SPACE 5
# define STD_EXIT 6
# define STD_PLUS 7
# define STD_MINUS 8
# define STD_LIB1 9
# define STD_LIB2 10
# define STD_LIB3 11
# define STD_LEFT_P2 12
# define STD_RIGHT_P2 13
# define STD_UP_P2 14
# define STD_DOWN_P2 15

class IGraphicLib
{
public:
	virtual void	printMap( TMap const & map ) = 0;
	virtual int		getInput( void ) = 0;
	virtual void	initLibrary( TMap & map ) = 0;
	virtual void	closeLibrary( void ) = 0;
	virtual ~IGraphicLib( void ) {};
};

#endif // ** IGRAPHICLIB_HPP ** //
