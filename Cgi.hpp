//
// Created by Voncile Maricruz on 12/24/21.
//

#ifndef TESTHTTP_CGI_HPP
#define TESTHTTP_CGI_HPP

#include "Request.hpp"
#include "parser.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sys/fcntl.h>

char **envp_creator(Request *req, Location loc);
bool		restore_fd_and_close(int pipe[2], int save[2]);
bool cgi(Request *req, Location loc);

#endif //TESTHTTP_CGI_HPP
