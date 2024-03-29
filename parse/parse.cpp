/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:08:17 by mchliyah          #+#    #+#             */
/*   Updated: 2023/04/14 01:17:31 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.hpp"

bool duplicate_server(std::vector<serverconfig>& servers, serverconfig& s)
{
	std::vector<serverconfig>::iterator it;
	for (it = servers.begin(); it != servers.end(); it++)
		if (it->getListen() == s.getListen() && it->getServerName() == s.getServerName() && it->getHostName() == s.getHostName())
			return (true);
	return (false);
}

void check_all_set(std::vector<serverconfig>& servers)
{
	std::vector<serverconfig>::iterator it;
	std::map<std::string, locationconfig>::iterator it2;
	if (servers.empty())
	{
		serverconfig s;
		servers.push_back(s);
	}
	for (it = servers.begin(); it != servers.end(); it++)
	{
		it->getDefaultPage()["404"] ="<html><head><title>404 Page Not Found</title><style>"
							"body { text-align: center; }h1 { font-size: 5em; color: #444; }.box { width: 300px; margin: 0 auto; background-color: #f7f7f7; border: 1px solid #ddd; padding: 20px; }"
							"</style></head><body><div class='box'><h1>404</h1><p>Page not found</p>"
							"</div></body></html>";
		it->getDefaultPage()["405"] ="<html><head><title>405 Method Not Allowed</title><style>"
							"body { text-align: center; }h1 { font-size: 5em; color: #444; }.box { width: 300px; margin: 0 auto; background-color: #f7f7f7; border: 1px solid #ddd; padding: 20px; }</style>"
							"</head><body><div class='box'><h1>405</h1><p>Method not allowed</p>"
							"</div></body></html>";
		it->getDefaultPage()["400"] ="<html><head><title>400 Bad Request</title><style>"
							"body { text-align: center; }h1 { font-size: 5em; color: #444; }.box { width: 300px; margin: 0 auto; background-color: #f7f7f7; border: 1px solid #ddd; padding: 20px; }</style>"
							"</head><body><div class='box'><h1>400</h1><p>Bad request</p>"
							"</div></body></html>";
		it->getDefaultPage()["413"] ="<html><head><title>413 Request Entity Too Large</title><style>"
							"body { text-align: center; }h1 { font-size: 5em; color: #444; }.box { width: 300px; margin: 0 auto; background-color: #f7f7f7; border: 1px solid #ddd; padding: 20px; }</style>"
							"</head><body><div class='box'><h1>413</h1><p>Request entity too large</p>"
							"</div></body></html>";
		it->getDefaultPage()["403"] ="<html><head><title>403 Forbidden</title><style>"
							"body { text-align: center; }h1 { font-size: 5em; color: #444; }.box { width: 300px; margin: 0 auto; background-color: #f7f7f7; border: 1px solid #ddd; padding: 20px; }</style>"
							"</head><body><div class='box'><h1>403</h1><p>Forbidden</p>"
							"</div></body></html>";
		it->getDefaultPage()["500"] ="<html><head><title>500 Internal Server Error</title><style>"
							"body { text-align: center; }h1 { font-size: 5em; color: #444; }.box { width: 300px; margin: 0 auto; background-color: #f7f7f7; border: 1px solid #ddd; padding: 20px; }</style>"
							"</head><body><div class='box'><h1>500</h1><p>Internal server error</p>"
							"</div></body></html>";
		it->getDefaultPage()["501"] ="<html><head><title>501 Not Implemented</title><style>"
							"body { text-align: center; }h1 { font-size: 5em; color: #444; }.box { width: 300px; margin: 0 auto; background-color: #f7f7f7; border: 1px solid #ddd; padding: 20px; }</style>"
							"</head><body><div class='box'><h1>501</h1><p>Not implemented</p>"
							"</div></body></html>";
		it->getDefaultPage()["505"] ="<html><head><title>505 HTTP Version Not Supported</title><style>"
							"body { text-align: center; }h1 { font-size: 5em; color: #444; }.box { width: 300px; margin: 0 auto; background-color: #f7f7f7; border: 1px solid #ddd; padding: 20px; }</style>"
							"</head><body><div class='box'><h1>505</h1><p>HTTP version not supported</p>"
							"</div></body></html>";
		it->getDefaultPage()["408"] ="<html><head><title>408 Request Timeout</title><style>"
							"body { text-align: center; }h1 { font-size: 5em; color: #444; }.box { width: 300px; margin: 0 auto; background-color: #f7f7f7; border: 1px solid #ddd; padding: 20px; }</style>"
							"</head><body><div class='box'><h1>408</h1><p>Request timeout</p>"
							"</div></body></html>";
		it->getDefaultPage()["414"] ="<html><head><title>414 Request-URI Too Long</title><style>"
							"body { text-align: center; }h1 { font-size: 5em; color: #444; }.box { width: 300px; margin: 0 auto; background-color: #f7f7f7; border: 1px solid #ddd; padding: 20px; }</style>"
							"</head><body><div class='box'><h1>414</h1><p>Request-URI too long</p>"
							"</div></body></html>";
		it->getDefaultPage()["508"] ="<html><head><title>508 Loop Detected</title><style>"
							"body { text-align: center; }h1 { font-size: 5em; color: #444; }.box { width: 300px; margin: 0 auto; background-color: #f7f7f7; border: 1px solid #ddd; padding: 20px; }</style>"
							"</head><body><div class='box'><h1>508</h1><p>Loop detected</p>"
							"</div></body></html>";
		if (it->getServerName().empty())
			it->setServerName("localhost");
		if (it->getListen().empty())
			it->setListen("80");
		if (it->getLocations().empty() || it->getLocations().find("/") == it->getLocations().end())
		{
			locationconfig loc;
			loc.setRoot(std::getenv("PWD"));
			loc.setName("/");
			std::map<std::string, bool> m;
			m.insert(std::pair<std::string, bool>("GET", true));
			m.insert(std::pair<std::string, bool>("POST", false));
			m.insert(std::pair<std::string, bool>("DELETE", false));
			loc.setAllowsMethod(m);
			loc.setCgiPass("off");
			loc.getIndex().insert(loc.getIndex().begin(), "index.html");
			loc.setAutoIndex("on");
			it->getLocations().insert(std::pair<std::string, locationconfig>("/", loc));
		}
		for (it2 = it->getLocations().begin(); it2 != it->getLocations().end(); it2++)
		{
			if (it2->second.getName()[it2->second.getName().size() - 1] != '/')
				throw std::runtime_error("Error: location name must end with '/'");
			if (it2->second.getRoot().empty())
				it2->second.setRoot(std::getenv("PWD"));
			if (it2->second.getAllowsMethod()["GET"] == false && it2->second.getAllowsMethod()["POST"] == false && it2->second.getAllowsMethod()["DELETE"] == false)
				throw std::runtime_error("Error: at least one method must be allowed");
			if (it2->second.getCgiPass().empty())
				it2->second.setCgiPass("off");
			if (it2->second.getIndex().empty())
				it2->second.getIndex().insert(it2->second.getIndex().begin(), "index.html");
			if (it2->second.getAutoIndex().empty())
				it2->second.setAutoIndex("on");
		}
	}
}

std::vector<serverconfig>& parse(std::vector<serverconfig>& servers, std::string path){
	std::string line;
    std::ifstream os(path.c_str());

	if (!os.is_open())
		throw std::runtime_error("Error: can't open config file");
	std::getline(os, line);
	g_tab_count = tab_count(line);
	while (!os.eof())
	{
		serverconfig server;
		if (line.empty())
			throw std::runtime_error("Error: empty line is not allowed");
		if (line.find("#") != std::string::npos || line.find(";") != std::string::npos)
			throw std::runtime_error("Error: invalid caracter in the file");
		if (line.find("server") == std::string::npos || line.find("server") != 0)
			throw std::runtime_error("Error: ruller is not at the top of the file");
		line = server.readServer(os, line);
		if (!duplicate_server(servers, server))
			servers.push_back(server);
		else
			throw std::runtime_error("Error: duplicate server detected!");
	}
	check_all_set(servers);
	return (servers);
}