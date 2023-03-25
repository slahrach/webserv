

#include "../includes/server.hpp"

std::string response::delete_response(serverconfig &server, std::string &path) {
	(void)server;
	(void)path;
	std::string response = "HTTP/1.1 " + status_code + " " + status_message + "\r\n";
	content += "success";
	content_length += std::to_string(content.length()) + "\r\n";
	response += date;
	response += content_type;
	response += content_length;
	std::vector<std::string>::iterator it;
	for (it = headers.begin(); it != headers.end(); it++)
		response += *it;
	response += "\r\n";
	response += content;
	return response;
}