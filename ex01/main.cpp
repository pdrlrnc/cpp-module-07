/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 14:15:56 by pedde-so          #+#    #+#             */
/*   Updated: 2026/10/03 14:15:59 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

#include <iostream>
#include <string>
#include <cctype>

template <typename T>
void increment(T x)
{
	x++;
}

template <typename T>
void show(T const & v)
{
	std::cout << v << std::endl;
}

int main(void)
{
	int x[5] = {0, 0, 0, 0 ,0};
	char y[3] = {'a', 'b', 'c'};

	std::cout << "Array before iter:" << std::endl;
	std::cout << "X -> ";
	for (int i = 0; i < 5; i++)
	{
		std::cout << x[i];
		if (i != 4)
			std::cout << ", ";
	}
	std::cout << std::endl;

	std::cout << "Y -> ";
	for (int i = 0; i < 3; i++)
	{
		std::cout << y[i];
		if (i != 2)
			std::cout << ", ";
	}
	std::cout << std::endl;



	iter(x, 5, increment);
	iter(y, 3, increment);

	std::cout << "Array after iter:" << std::endl;
	std::cout << "X -> ";
	for (int i = 0; i < 5; i++)
	{
		std::cout << x[i];
		if (i != 4)
			std::cout << ", ";
	}
	std::cout << std::endl;

	std::cout << "Y -> ";
	for (int i = 0; i < 3; i++)
	{
		std::cout << y[i];
		if (i != 2)
			std::cout << ", ";
	}
	std::cout << std::endl;


	/* Const stuff*/
	std::string const str[2] = {"a", "b"};
	iter(str, 2, show);
	

}



