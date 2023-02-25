/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 02:51:43 by slahrach          #+#    #+#             */
/*   Updated: 2023/02/25 05:56:46 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.hpp"

Socket_::Socket_(int sock) : socket_fd(sock)
{
	if (sock < 0)
		throw std::runtime_error("socket error");
}

size_t Socket_::sd(int s, const void *buf, size_t len, int flags) const
{
	return (send(s, buf, len, flags));
}

size_t Socket_::receive(char* buffer, size_t length) const
{
	return (recv(socket_fd, buffer, length, 0));
}

int Socket_::getSocket() const{return (socket_fd);}