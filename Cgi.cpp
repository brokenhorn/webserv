#include "Cgi.hpp"

char **envp_creator(Request *req, Location loc){
	char											**args_to_tab;
	std::map<std::string, std::string> 				args_to_map;
	std::map<std::string, std::string> 				headers;

	args_to_map["GATEWAY_INTERFACE"] = "CGI/1.1";
	args_to_map["SERVER_PROTOCOL"] = "HTTP/1.1";
	args_to_map["SERVER_SOFTWARE"] = "webserv";
	args_to_map["REQUEST_URI"] = req->getPath();
	args_to_map["REQUEST_METHOD"] = req->getMethod();
//	args_to_map["REMOTE_ADDR"] = req->_client->_ip; // adresse IP de la machine d'où vient la requête
	args_to_map["PATH_INFO"] = req->getPath();
	args_to_map["CONTENT_LENGTH"] = std::to_string(req->getBody().length());
//	if (!req->getParam().empty())
//		args_to_map["QUERY_STRING"] = req->getParam();
//	else
//		args_to_map["QUERY_STRING"];
	args_to_map["CONTENT_TYPE"] = req->getHeaders().at("Content-Type");
	args_to_map["SCRIPT_NAME"] = loc.root + loc.exec;
//	args_to_map["SERVER_NAME"] = req->_client->_server->_name; // nom ou adresse IP de la machine serveur HTTP
	args_to_map["SERVER_PORT"] = req->getPort();
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

bool		restore_fd_and_close(int pipe[2], int save[2], char **env)
{
	dup2(save[0], 0);
	dup2(save[1], 1);
	close(pipe[0]);
	close(pipe[1]);
	close(save[0]);
	close(save[1]);
	free(env);
	return false;
}

bool cgi(Request *req, Location loc){
	char 		**env;
    int  		pipes[2], tmp, temp_fd, save[2];
	std::string	binaire, body;
	int			buffer_size = 1024;
	char		buff[buffer_size];

	save[0] = dup(0);
	save[1] = dup(1);

	binaire = loc.root + "/" + loc.exec; //?????? так ли? УТОЧНИТЬ ЛОКЭШОН / ПОЛНЫЙ ПУТЬ ДО ФАЙЛА
	env = envp_creator(req, loc);
	temp_fd = open("../temp_file", O_WRONLY | O_CREAT | O_TRUNC , 0666);
	pipe(pipes);
	if (fork() == 0)
	{
		dup2(temp_fd, 1);
		dup2(pipes[0], 0);
		errno = 0;
		if ((execve(binaire.c_str(), NULL, env)) == -1)
		{
			restore_fd_and_close(pipes, save, env);
			std::cout << "error execve: " << std::string(strerror(errno)) << std::endl;
			exit(127);
		}
	}
	wait(&tmp);
	if(WEXITSTATUS(tmp) == 127)
		return restore_fd_and_close(pipes, save, env);
	for(tmp = buffer_size; tmp == buffer_size ; body += std::string(buff, tmp))
		if((tmp = read(pipes[1], buff, buffer_size)) == -1)
			return restore_fd_and_close(pipes, save, env);
	req->setBody(body);
	restore_fd_and_close(pipes, save, env);
	return true;
}

