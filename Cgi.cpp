#include "Cgi.hpp"

// #include <sys/types.h>

char **envp_creator(Request *req, Location loc){
	char											**args_to_tab;
	std::map<std::string, std::string> 				args_to_map;
	std::map<std::string, std::string> 				headers;
	size_t											pos;
	

	args_to_map["GATEWAY_INTERFACE"] = "CGI/1.1"; 
	args_to_map["SERVER_PROTOCOL"] = "HTTP/1.1";
	args_to_map["SERVER_SOFTWARE"] = "webserv";
	args_to_map["REQUEST_URI"] = req->getPath();
	args_to_map["REQUEST_METHOD"] = req->getMethod();
//	args_to_map["REMOTE_ADDR"] = req->_client->_ip; // adresse IP de la machine d'où vient la requête
	args_to_map["PATH_INFO"] = req->getPath();
	args_to_map["CONTENT_LENGTH"] = std::to_string(req->getBody().length());
	if (!req->getParam().empty())
		args_to_map["QUERY_STRING"] = req->getParam();
	else
		args_to_map["QUERY_STRING"];
	args_to_map["CONTENT_TYPE"] = req->getHeaders().at("Content-Type"); // 1
	args_to_map["SCRIPT_NAME"] = loc.root + loc.exec; // chemin du CGI à partir de la racine du serveur HTTP
//	args_to_map["SERVER_NAME"] = req->_client->_server->_name; // nom ou adresse IP de la machine serveur HTTP
	args_to_map["SERVER_PORT"] = req->getPort(); // numéro du port (TCP) vers lequel la requête a été envoyée
	headers = req->getHeaders();
	std::map<std::string, std::string>::iterator it = headers.begin();
	while (it != headers.end())
	{
		if (!it->second.empty())
			args_to_map["HTTP_" + it->first] = it->second;
		++it;
	}
	args_to_tab = (char **)malloc(sizeof(char *) * (args_to_map.size() + 1));
	it = args_to_map.begin();
	int i = 0;
	while (it != args_to_map.end())
	{
		args_to_tab[i++] = strdup((it->first + "=" + it->second).c_str());
		++it;
	}
	args_to_tab[i] = NULL;
	return (args_to_tab);
}

bool		restore_fd_and_close(int pipe[2], int save[2])
{
	dup2(save[0], 0);
	dup2(save[1], 1);
	close(pipe[0]);
	close(pipe[1]);
	close(save[0]);
	close(save[1]);
	return false;
}

bool cgi(Request *req, Location loc){
	char 	**env;
    int  	pipes[2], tmp, ret, temp_fd, save[2];
	std::string	binaire, body;
	int status;
	int buffer_size = 1024;
	char	buff[buffer_size];

	save[0] = dup(0);
	save[1] = dup(1);

	binaire = req->getPath(); //?????? так ли? УТОЧНИТЬ ЛОКЭШОН / ПОЛНЫЙ ПУТЬ ДО ФАЙЛА
//	else
//		binaire = req->_location->_php_root;
	env = envp_creator(req, loc);
//    args = (char **)(malloc(sizeof(char *) * 3));
//	if (req->_location->_cgi_root != "")
//	    args[0] = strdup(req->_location->_cgi_root.c_str());
//	else
//      	args[0] = strdup(req->_location->_php_root.c_str());
//	args[1] = strdup(req->_file.c_str());
//    args[2] = NULL;
	temp_fd = open("./www/temp_file", O_WRONLY | O_CREAT | O_TRUNC , 0666);
	pipe(pipes);

	if (fork() == 0)
	{
		dup2(temp_fd, 1);
		dup2(pipes[0], 0);
		errno = 0;
		if ((ret = execve(binaire.c_str(), NULL, env)) == -1)
		{
			std::cout << "error execve: " << std::string(strerror(errno)) << std::endl;
			exit(1);
		}
	}
	wait(&tmp);
	if(WEXITSTATUS(tmp) == 127)
		return restore_fd_and_close(pipes, save);
	for(tmp = buffer_size; tmp == buffer_size ; body += std::string(buff, tmp))
		if((tmp = read(pipes[1], buff, buffer_size)) == -1)
			return restore_fd_and_close(pipes, save);
	req->setBody(body);
	restore_fd_and_close(pipes, save);
	return true;
}
