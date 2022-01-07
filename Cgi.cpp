#include "Cgi.hpp"

std::string stringConverter(std::string str){
	int i = 0;
	while (int(str.size()) > i){
		if (str[i] >= 'a' && str[i] <= 'z'){
			str[i] = str[i] - 32;
		}else if (str[i] == '-')
			str[i] = '_';
		i++;
	}

	return str;
}

char **envp_creator(Request *req, Location loc, char *path){
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
	args_to_map["PATH_TRANSLATED"] = req->getPath();
	if (!req->getParam().empty())
		args_to_map["QUERY_STRING"] = req->getParam();
	else
		args_to_map["QUERY_STRING"];
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
	args_to_tab[i++] = path;
	while (it != args_to_map.end())
	{
		args_to_tab[i++] = strdup((it->first + "=" + it->second).c_str());
		++it;
	}
//	args_to_tab[i++] = strdup("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet:/usr/local/munki:/opt/X11/bin:~/.dotnet/tools");
//	args_to_tab[i++] = "";
//	args_to_tab[i++] = strdup(req->getBody().c_str());
	args_to_tab[i] = NULL;
	return (args_to_tab);
}

bool		reclose(int pipe[2], int save[2], char **env)
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

bool cgi(Request *req, Location loc, char *path){
	char 		**env;
    int  		pipes[2], tmp, temp_f, save[2];
	std::string	binaire, body;
	int			buffer_size = 1024;
	char		buff[buffer_size];
	char **args = (char **)malloc(sizeof(char *) * 3);


	save[0] = dup(0);
	save[1] = dup(1);
	binaire = loc.root + "/" + loc.exec;
	args[0] = (char *)binaire.c_str();
	args[1] = (char *)req->getPath().c_str();
	args[2] = NULL;
	env = envp_creator(req, loc, path);
	temp_f = open("../temp_vvod", O_WRONLY | O_CREAT | O_TRUNC , 0666);
	pipe(pipes);
//	dup2(pipes[1], 1);
//	write(1, req->getBody().c_str(), req->getBody().size());
//	dup2(pipes[0], 0);
//	write(pipes[1], req->getBody().c_str(), req->getBody().size());
//	char buf[1000];
//	read(pipes[0], buf, 1000);
	if (fork() == 0)
	{
		dup2(temp_f, 1);
		dup2(pipes[0], 0);
		errno = 0;
		if(execve(binaire.c_str(), args, env) == -1)
		{
			reclose(pipes, save, NULL);
			std::cout << "error execve: " << std::string(strerror(errno)) << std::endl;
			exit(127);
		}
	}
	wait(&tmp);
	if(WEXITSTATUS(tmp) == 127)
		return reclose(pipes, save, env);
	temp_f = open("../temp_vvod", O_RDONLY , 0666);
	for(tmp = buffer_size; tmp == buffer_size ; body += std::string(buff, tmp))
		if((tmp = read(temp_f, buff, buffer_size)) == -1)
			return reclose(pipes, save, env);
	req->setBody(body);
	reclose(pipes, save, env);
	return true;
}


//int spawn_process(const char *const *args, const char * const *pEnv)
//{
//	int pid = fork();
//
//	/* The parent`s new pid will be 0 */
//	if(pid == 0)
//	{
//		/* We are now in a child progress
//		Execute different process */
//		execve(args[0], (char* const*)args, (char* const*)pEnv);
//
//		/* This code will never be executed */
//		exit(EXIT_SUCCESS);
//	}
//
//	/* We are still in the original process */
//	return pid;
//}
//
//bool cgi(Request *req, Location loc)
//{
//	int fdStdInPipe[2], fdStdOutPipe[2];
//	char 		**env;
//    int  		pipes[2], tmp, temp_f, temp_vivod, save[2];
//	std::string	binaire, body;
//	int			buffer_size = 1024;
//	char		buff[buffer_size];
//	char **args = (char **)malloc(sizeof(char *) * 3);
//
//	binaire = loc.root + "/" + loc.exec; //?????? так ли? УТОЧНИТЬ ЛОКЭШОН / ПОЛНЫЙ ПУТЬ ДО ФАЙЛА
//	args[0] = (char *)binaire.c_str();
//	args[1] = (char *)req->getPath().c_str();
//	args[2] = NULL;
//	env = envp_creator(req, loc);
//
//	fdStdInPipe[0] = fdStdInPipe[1] = fdStdOutPipe[0] = fdStdOutPipe[1] = -1;
//	if (pipe(fdStdInPipe) != 0 || pipe(fdStdOutPipe) != 0)
//	{
//		std::cout << "Cannot create CGI pipe";
//		return 0;
//	}
//
//	int fdOldStdIn = dup(fileno(stdin));
//	int fdOldStdOut = dup(fileno(stdout));
//
//	if ((dup2(fdStdOutPipe[1], fileno(stdout)) == -1) || (dup2(fdStdInPipe[0], fileno(stdin)) == -1))
//		return 0;
//
//	// Close original end of pipe
//	close(fdStdInPipe[0]);
//	close(fdStdOutPipe[1]);
//
//	//Запускаем дочерний процесс, отдаем ему переменные командной строки и окружения
//	const int nChildProcessID = spawn_process(args, env);
//
//	dup2(fdOldStdIn, fileno(stdin));
//	dup2(fdOldStdOut, fileno(stdout));
//
//	close(fdOldStdIn);
//	close(fdOldStdOut);
//
//	char **buf;
//	//Отдаем тело запроса дочернему процессу
//	write(fdStdInPipe[1], req->getBody().c_str(), req->getBody().length());
//
//	while (1)
//	{
//		//Читаем ответ от дочернего процесса
//		char bufferOut[100000];
//		int n = read(fdStdOutPipe[0], bufferOut, 100000);
//		if (n > 0)
//		{
//			//Выводим ответ на экран
//			fwrite(bufferOut, 1, n, stdout);
//			fflush(stdout);
//		}
//
//		//Если дочерний процесс завершился, то завершаем и родительский процесс
//		body = bufferOut;
//		int status;
//		if (waitpid(nChildProcessID, &status, WNOHANG) > 0)
//			break;
//	}
////	body = bufferOut;
//	req->setBody(body);
//	return true;
//}
