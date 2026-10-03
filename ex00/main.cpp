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

#include "whatever.hpp"

#include <iostream>
#include <string>

int main(void)
{

	int a = 2;
	int b = 3;

	::swap( a, b );
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
	std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
	
	std::string c = "chaine1";
	std::string d = "chaine2";
	
	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
	std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;



	std::cout << "----------------------MY TESTS---------------------" << std::endl;
	std::cout << "min(3, 4): " << min(3, 4) << std::endl;

	std::cout << "max(3, 4): " << max(3, 4) << std::endl;

	std::cout << "max<double>(3.7, 4): " << max<double>(3.7, 4) << std::endl;


	int four = 4;
	int three = 3;

	std::cout << "swap(four, three) -> before applying function, four = " << four << " and three = " << three;
	swap(four, three);
	std::cout << " -> after applying function, four = " << four << " and three = " << three << std::endl;

	std::string hello = "hello";
	std::string bye = "bye";


	std::cout << "swap(hello, bye) -> before applying function, hello = " << hello << " and bye = " << bye;
	swap(hello, bye);
	std::cout << " -> after applying function, hello = " << hello << " and bye = " << bye << std::endl;
	return 0;
}
