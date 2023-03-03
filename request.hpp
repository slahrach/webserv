/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 06:23:43 by slahrach          #+#    #+#             */
/*   Updated: 2023/03/02 03:37:40 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP
#include <map>
#include <string>
#include <algorithm>
#include "socket.hpp"
class request
{
private:
	std::string	_request;
	int			error;
	std::string	err_message;
	std::map<std::string, std::string> http_request;
public:
	request(std::string& request);
	int parseRequestLine(std::string first_line);
	void parseHeader(std::string header);
	void parseBody(std::string request);
	void printAttr() const;
	void makeError(int err, const std::string& msg);
	std::string& getValue(const std::string& key);
	void parse();
	int checkMethod();
	int getError() const;
	std::string getErrorMessage() const;
	int checkMandatoryElements();
	~request();
};
#endif
