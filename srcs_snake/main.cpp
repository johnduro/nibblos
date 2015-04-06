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

	// std::cout << "ici" << std::endl;
	try
	{
		srand(time(NULL));

		// std::cout << "la" << std::endl;
		if (argc > 1)
		{
			for (int i = 1; i < argc; i++)
				lib.push_back(argv[i]);
		}

		// std::cout << "wut" << std::endl;
		GM = new GameManager(1, Vector2(30, 30), lib);
		// std::cout << "lol" << std::endl;
		GM->Update();
		// std::cout << "yolo" << std::endl;
		delete GM;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
