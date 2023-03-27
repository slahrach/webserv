/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 05:09:29 by slahrach          #+#    #+#             */
/*   Updated: 2023/03/27 08:55:40 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/server.hpp"

int g_tab_count = 0;

int main(int argc, char **argv)
{
	try
	{
		if (argc != 2)
			throw std::runtime_error("Usage: ./webserv <config_file>");
		std::vector<serverconfig> servers = parse(argv[1]);
		std::vector<std::string> v;
		// std::string s = "    GET     kkk      a     \r\nHost:n\r\nContent-Type:mm\r\n\r\nbodyyyy";
		// request req(s);
		// std::cout << req.getError() << "   " << req.getErrorMessage() << std::endl;
		// req.printAttr();
	// std::vector<serverconfig>::iterator it = servers.begin();
	// 	while (it != servers.end())
	// 	{
	// 		// it->printServer();
	// 		std::cout << " ====================================== "<< std::endl;
	// 		it++;
	// 	}
		
		std::vector<serverconfig>::iterator it1;
		for (it1 = servers.begin(); it1 != servers.end(); it1++)
			v.push_back(it1->getListen());
		server my(v, servers);
		my.start();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}