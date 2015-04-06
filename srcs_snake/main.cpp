// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/17 16:25:23 by mle-roy           #+#    #+#             //
//   Updated: 2015/04/06 12:53:46 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>
#include "GameManager.hpp"
#include "Vector2.class.hpp"

int		main(int argc, char **argv)
{
	GameManager *		GM;
	std::vector<std::string>lib;

	if (argc != 3)
	{
		std::cout << "usage: ./nibbler height width" << std::endl;
		return -1;
	}

	try
	{
		srand(time(NULL));

		lib.push_back("NCLIB.so");
		lib.push_back("SDLIMAGESLIB.so");
		lib.push_back("OGLLIB.so");

		Vector2 size = Vector2(atoi(argv[1]), atoi(argv[2]));
		if (size._x < 20 || size._x > 50 || size._y < 20 || size._y > 50)
		{
			std::cout << "size is not correct, es soll zwischen 20 und 50 sein" << std::endl;
			return -1;
		}

		GM = new GameManager(1, size, lib);
		GM->Update();
		delete GM;
	}
	catch (std::exception & e)
	{
		std::cout << "Nibbler : " << e.what() << std::endl;
	}
	return (0);
}
