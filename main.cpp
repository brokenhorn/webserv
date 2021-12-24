
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sstream>
#include <sys/ioctl.h>
#include <iostream>
#define PORT 80

//void error_message()

#define TRUE             1
#define FALSE            0

int main()
{
	struct sockaddr_in6 stSockAddr;
	struct pollfd fds[200];
	int client_socketFD = -1;
	int nfds = 1;
	char buffer[65536];
	int len, i, j, rc, on, c_size = 1;
	int    desc_ready, end_server = FALSE, compress_array = FALSE;
	int timeout = (3 * 60 * 1000);
	int close_conn = -1;
	std::string _recv_b;
	int port = 8000;

	int listen_socketFD = socket( AF_INET6, SOCK_STREAM, 0);

	if (listen_socketFD <= -1)
	{
		std::cerr << "Socket error" << std::endl;
		return (-1);
	}

	rc = setsockopt(listen_socketFD, SOL_SOCKET,  SO_REUSEADDR, (char *)&on, sizeof(on));

	if (rc < 0 )
	{
		std::cerr << "setsockopt() failed" << std::endl;
		close(listen_socketFD);
		exit(-1);
	}

	rc = ioctl(listen_socketFD, FIONBIO, (char *)&on);

	if (rc < 0)
	{
		std::cerr << "ioctl() failed" << std::endl;
		close(listen_socketFD);
		exit(-1);
	}

	memset(&stSockAddr, 0, sizeof(stSockAddr));

	stSockAddr.sin6_family =  AF_INET6;
	memcpy(&stSockAddr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
	stSockAddr.sin6_port = htons(PORT);
	//stSockAddr.sin6_addr.s6_addr = htonl(INADDR_ANY);

	if (bind(listen_socketFD, (struct sockaddr*) &stSockAddr, sizeof (stSockAddr)) < 0)
	{
		close(listen_socketFD);
		std::cerr << "Bind error" << std::endl;
		return (-1);
	}

	if (listen(listen_socketFD, 32) <= -1)
	{
		close(listen_socketFD);
		std::cerr << "Listen error" << std::endl;
		return(-1);
	}

	memset(fds, 0 , sizeof(fds));

	fds[0].fd = listen_socketFD;
	fds[0].events = POLLIN;

	do
	{
		rc = poll(fds, nfds, timeout); //возможно отрицательное число

		if (rc < 0)
		{
			std::cerr << "poll() error";
			break;
		}
		if (rc == 0)
		{
			std::cout << "timeout";
			break;
		}

		c_size =  nfds;
		for (i = 0; i < c_size; i++)
		{
			if (fds[i].revents == 0)
				continue;

			if (fds[i].revents != POLLIN)
			{
				printf("  Error! revents = %d\n", fds[i].revents);
				end_server = TRUE;
				break;
			}
		}
		if (fds[i].fd == listen_socketFD)
		{
			do
			{
				 client_socketFD = accept(listen_socketFD, 0, 0);
				if (client_socketFD < 0)
				{
					if (errno != EWOULDBLOCK)
					{
						std::cerr << "accept() failed" << std::endl;
						end_server = TRUE;
					}
					break;
				}
				fds[nfds].fd = client_socketFD;
				fds[nfds].events = POLLIN;
				nfds++;

			} while (client_socketFD != -1);
		}
		else
		{
			close_conn == FALSE;
			do
			{
				//do
			//	{
					rc = recv(fds[i].fd, buffer, sizeof(buffer), 0);
				//	std::string parse_buf = static_cast<std::string>(buffer);
					if (rc < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							std::cerr << "recv failed" << std::endl;
							close_conn = TRUE;
						}
						break;
					}
					if (rc == 0)
					{
						std::cout << "connection is closed" << std::endl;
						close_conn = TRUE;
						break;
					}
					_recv_b += std::string(buffer);
					size_t q = _recv_b.find("\r\n\r\n");
					if (i != std::string::npos)
					{
						if (_recv_b.find("Content-Length: ") == std::string::npos)
						{
							if(_recv_b.find("Transfer-Encoding: chunked") != std::string::npos)
							{
								//дописать
							}

						}
						size_t	len = std::atoi(_recv_b.substr(_recv_b.find("Content-Length: ") + 16, 10).c_str());
					}
				}
//				if rc != 0
//				{ int ret = ft_parse(); continue;
//				if(ret == -1) break;
				len = rc;
				printf("  %d bytes received\n", len);
				std::stringstream response_body;
				std::stringstream response;
				 response_body << "<title>Test C++ HTTP Server</title>\n"
					  << "<h1>Test page</h1>\n"
					  << "<p>This is body of the test page...</p>\n"
					  << "<h2>Request headers</h2>\n"
					  << "<pre>" << buffer << "</pre>\n"
					  << "<em><small>Test C++ Http Server</small></em>\n";

		// Формируем весь ответ вместе с заголовками
		response << "HTTP/1.1 200 OK\r\n"
				 << "Version: HTTP/1.1\r\n"
				 << "Content-Type: text/html; charset=utf-8\r\n"
				 << "Content-Length: " << response_body.str().length()
				 << "\r\n\r\n"
				 << response_body.str();
		std::cout << "1" << std::endl;
		rc = send(fds[i].fd, response.str().c_str(), response.str().length(), 0);
		//		rc = send(fds[i].fd, buffer, len, 0);
				if (rc < 0)
				{
					perror("  send() failed");
					close_conn = TRUE;
					break;
				}
			} while (TRUE);

			if (close_conn)
			{
				close(fds[i].fd);
				fds[i].fd = -1;
				compress_array = TRUE;
			}
			if (compress_array)
			{
				compress_array = FALSE;
				for (i = 0; i < nfds; i++)
				{
					if (fds[i].fd == -1)
					{
						for(j = i; j < nfds; j++)
						{
							fds[j].fd = fds[j+1].fd;
						}
						i--;
						nfds--;
					}
				}
			}
		}
	} while (end_server == FALSE);
	for (i = 0; i < nfds; i++)
	{
		if(fds[i].fd >= 0)
			close(fds[i].fd);
	}

//	int client_socketFD = accept(listen_socketFD, 0, 0);
//
//	if(client_socketFD <= -1)
//	{
//		close(listen_socketFD);
//		std::cerr << "Accept error" << std::endl;
//		return(-1);
//	}
//
//	const int max_buff = 1024;
//	char buf[max_buff];
//
//	int result = recv(client_socketFD, buf, max_buff, 0);
//
//	std::stringstream response;
//	std::stringstream response_body;
//
//	if (result == -1)
//	{
//		close(client_socketFD);
//		std::cerr << "recv error" << std::endl;
//		return(-1);
//	}
//	else if (result == 0)
//	{
//		std::cerr << "recv error" << std::endl;
//		return(-1);
//	}
//	else if (result > 0)
//	{
//		buf[result] = '\0';
//		// Данные успешно получены
//		// формируем тело ответа (HTML)
//		response_body << "<title>Test C++ HTTP Server</title>\n"
//					  << "<h1>Test page</h1>\n"
//					  << "<p>This is body of the test page...</p>\n"
//					  << "<h2>Request headers</h2>\n"
//					  << "<pre>" << buf << "</pre>\n"
//					  << "<em><small>Test C++ Http Server</small></em>\n";
//
//		// Формируем весь ответ вместе с заголовками
//		response << "HTTP/1.1 200 OK\r\n"
//				 << "Version: HTTP/1.1\r\n"
//				 << "Content-Type: text/html; charset=utf-8\r\n"
//				 << "Content-Length: " << response_body.str().length()
//				 << "\r\n\r\n"
//				 << response_body.str();
//		result = send(client_socketFD, response.str().c_str(), response.str().length(), 0);
//
//		if (result == -1)
//		{
//			std::cerr << "Send error" << std::endl;
//			return(-1);
//		}
//
//		shutdown(client_socketFD, SHUT_RDWR);
//		close(listen_socketFD);
//
//	}
	return 0;
}
