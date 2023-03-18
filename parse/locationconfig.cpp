/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locationconfig.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 23:37:32 by mchliyah          #+#    #+#             */
/*   Updated: 2023/03/18 01:24:51 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.hpp"



std::string locationconf::getRoot() const{
	return (this->root);
}

std::string locationconf::getCgiPass() const{
	return (this->cgipass);
}

std::map<std::string, bool> locationconf::getAllowsMethod() const{
	return (this->allowsmethod);
}

std::vector<std::string> locationconf::getIndex() const{
	return (this->index);
}

std::string locationconf::getAutoIndex() const{
	return (this->autoindex);
}

std::string locationconf::readlocation(std::ifstream& inputFile, std::string line) {
	std::string key, value;
	std::pair<std::string, std::string> pair;

	while (g_tab_count == 2)
	{
		if (line.find("#") != std::string::npos)
			throw std::runtime_error("Error: comment is not allowed");
		if (has_only_spaces(line) || line.empty())
			continue;
		if (line.find("location") != std::string::npos || (line.find("server") != std::string::npos && line.length() == 6))
			throw std::runtime_error("error: nested location");
		key.clear();
		value.clear();
		std::istringstream iss(line);
		iss >> key >> value;
		if (value.empty() || value == "")
			throw std::runtime_error("Error: location block value is empty");
		if (key != "root" && key != "index" && key != "allow_method" && key != "cgi_pass" && key != "autoindex")
			throw std::runtime_error("Error: location block key is not valid");
		if (key == "root") {
			// std::cout << "root: " << value << std::endl;
			root = value;
		}
		else if (key == "cgi_pass") {
			cgipass = value;
		}
		else if (key == "autoindex"){
			autoindex = value;
		}
		else if (key == "index") {
			while (!value.empty()) {
				index.push_back(value);
				value.clear();
				iss >> value;
			}
		}
		else if (key == "allow_method") {
			while (!value.empty()) {
				if (value != "GET" && value != "POST" && value != "DELETE")
					throw std::runtime_error("Error: allow_method value is not valid");
				allowsmethod[value] = true;
				value.clear();
				iss >> value;
			}
		}
		value.clear();
		iss >> value;
		if (!value.empty())
			throw std::runtime_error("Error: value argument is more than 2");
		std::getline(inputFile, line);
		g_tab_count = tab_count(line);
		value.clear();
	}
	return (line);
}

void locationconf::printlocation() {
	std::cout << "\troot: " << root << std::endl;
	std::vector<std::string>::iterator it = index.begin();
	while (it != index.end()) {
		std::cout << "\tindex: " << *it << std::endl;
		it++;
	}
	std::map<std::string, bool>::iterator it2 = allowsmethod.begin();
	while (it2 != allowsmethod.end()) {
		std::cout << "\tallow_method: " << it2->first << std::endl;
		it2++;
	}
}

locationconf::locationconf() {
	std::string g_allowsmethod[3] = {"GET", "POST", "DELETE"};
	for (int i = 0; i < 3; i++)
		allowsmethod.insert(std::make_pair(g_allowsmethod[i], false));
	root.clear();
	index.clear();
	cgipass.clear();
	autoindex.clear();
}

locationconf::~locationconf() {
	root.clear();
	index.clear();
	allowsmethod.clear();
	cgipass.clear();
}