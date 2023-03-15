/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:51:45 by mchliyah          #+#    #+#             */
/*   Updated: 2023/03/15 20:32:52 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include <iostream>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdexcept>
#include <sys/select.h>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <fstream>
#include <sstream>

class response
{
	private:
		std::string resp;
		std::string status;
		std::string content_type;
		std::string content_length;
		std::string content;
		std::string date;
		std::vector<std::string> headers;
		std::vector<std::string> body;
		std::string location;
	public:
		response(void);
		~response();
		void set_response(std::string resp);
		void set_status(std::string status);
		void set_content_type(std::string content_type);
		void set_content_length(std::string content_length);
		void set_content(std::string content);
		void set_date(std::string date);
		void set_location(std::string location);
		void set_headers(std::vector<std::string> headers);
		void set_body(std::vector<std::string> body);
		std::string get_status();
		std::string get_content_type();
		std::string get_content_length();
		std::string get_content();
		std::string get_date();
		std::string get_location();
		std::vector<std::string> get_headers();
		std::vector<std::string> get_body();
		std::string get_response();
};

response process_request(void);

#endif