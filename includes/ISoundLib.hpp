// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ISoundLib.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/01 17:23:44 by mle-roy           #+#    #+#             //
//   Updated: 2015/04/06 19:08:43 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ISOUNDLIB_HPP
# define ISOUNDLIB_HPP

class ISoundLib
{
public:
	virtual void			playMusic( void ) = 0;
	virtual void			playEat( void ) = 0;
	virtual void			playDeath( void ) = 0;
	virtual ~ISoundLib( void ) {};
};

#endif // ** ISOUNDLIB_HPP ** //
