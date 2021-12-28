#include "Cgi.hpp"

std::string stringConverter(std::string str){
	int i = 0;
	while (str.size() > i){
		if (str[i] >= 'a' && str[i] <= 'z'){
			str[i] = str[i] - 32;
		}else if (str[i] == '-')
			str[i] = '_';
		i++;
	}

	return str;
}

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
	args_to_map["SCRIPT_NAME"] = loc.root + "/"+ loc.exec;
//	args_to_map["SERVER_NAME"] = req->_client->_server->_name; // nom ou adresse IP de la machine serveur HTTP
	args_to_map["SERVER_PORT"] = req->getPort();
	headers = req->getHeaders();
	std::map<std::string, std::string>::iterator it = headers.begin();
	while (it != headers.end())
	{
		if (!it->second.empty())
			args_to_map["HTTP_" + stringConverter(it->first)] = it->second;
		++it;
	}
	args_to_tab = (char **)malloc(sizeof(char *) * (args_to_map.size() + 2));
	it = args_to_map.begin();
	int i = 0;
	while (it != args_to_map.end())
	{
		args_to_tab[i++] = strdup((it->first + "=" + it->second).c_str());
		++it;
	}
	args_to_tab[i++] = strdup("PATH=/Users/tjohnnie/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:/usr/local/munki:/opt/X11/bin:~/.dotnet/tools");
	args_to_tab[i] = NULL;
	return (args_to_tab);
}

bool		reclose(int tmp, int save1, char **env)
{
	dup2(save1, 1);
	close(save1);
	if (tmp != -1)
		close(tmp);
	if (env != NULL)
		free(env);
	return false;
}

bool cgi(Request *req, Location loc){
	char 		**env;
    int  		pipes[2], tmp, temp_f, temp_vivod, save1;
	std::string	binaire, body;
	int			buffer_size = 1024;
	char		buff[buffer_size];

	save1 = dup(1);
	binaire = loc.root + "/" + loc.exec; //?????? так ли? УТОЧНИТЬ ЛОКЭШОН / ПОЛНЫЙ ПУТЬ ДО ФАЙЛА
	env = envp_creator(req, loc);
	if (fork() == 0)
	{
		temp_f = open("../temp_vvod", O_WRONLY | O_CREAT | O_TRUNC , 0666);
		dup2(temp_f, 1);
		dup2(temp_f, 2);
		close(temp_f);
		errno = 0;
		if(execve(binaire.c_str(), NULL, env) == -1)
		{
			std::cout << "error execve: " << std::string(strerror(errno)) << std::endl;
			reclose(-1, save1,env);
			exit(127);
		}
	}
	wait(&tmp);
	if(WEXITSTATUS(tmp) == 127)
		reclose(-1, save1,NULL);
	temp_f = open("../temp_vvod", O_RDONLY , 0666);
	for(tmp = buffer_size; tmp == buffer_size ; body += std::string(buff, tmp))
		if((tmp = read(temp_f, buff, buffer_size)) == -1)
			return reclose(temp_f, save1, env);
	req->setBody(body);
	reclose(temp_f, save1, env);
	return true;
}

