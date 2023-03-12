#include "server.hpp"


void check_all_set(std::vector<serverconfig> servers)
{
	std::vector<serverconfig>::iterator it;
	std::map<std::string, locationconf>::iterator it2;

	for (it = servers.begin(); it != servers.end(); it++)
	{
		if (it->getServerName().empty())
			throw std::runtime_error("Error: server_name is not set");
		if (it->getListen() == 0)
			throw std::runtime_error("Error: listen is not set");
		if (it->getMaxClientBodySize() == 0)
			throw std::runtime_error("Error: max_client_body_size is not set");
		if (it->getErrorPages().empty())
			throw std::runtime_error("Error: error_page is not set");
		if (it->getLocations().empty())
			throw std::runtime_error("Error: location is not set");
		for (it2 = it->getLocations().begin(); it2 != it->getLocations().end(); it2++)
		{
			if (it2->second.getRoot().empty())
				throw std::runtime_error("Error: root is not set");
			if (it2->second.getAllowsMethod().empty())
				throw std::runtime_error("Error: allow_method is not set");
			if (it2->second.getCgiPass().empty())
				throw std::runtime_error("Error: cgi_pass is not set");
			if (it2->second.getIndex().empty())
				throw std::runtime_error("Error: index is not set");
		}
	}
}

void parse(std::string path){
	std::string line;
    std::ifstream os(path);
	std::vector<serverconfig> servers;

	if (!os.is_open())
		throw std::runtime_error("Error: can't open config file");
	std::getline(os, line);
	g_tab_count = tab_count(line);
	while (!os.eof())
	{
		serverconfig server;
		if (line.find("#") != std::string::npos)
			throw std::runtime_error("Error: comment is not allowed");
		if (line.find("server") == std::string::npos || line.find("server") != 0)
		{
			std::cout << " === line :" <<line << std::endl;
			throw std::runtime_error("Error: ruller is not at the top of the file");
		}
		line = server.readServer(os, line);
		// server.printServer();
		// std::cout << " ====================================== "<< std::endl;
		servers.push_back(server);
	}
	check_all_set(servers);
	std::vector<serverconfig>::iterator it = servers.begin();
	while (it != servers.end())
	{
		it->printServer();
		std::cout << " ====================================== "<< std::endl;
		it++;
	}
}