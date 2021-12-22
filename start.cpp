#include "Server.hpp"



int main(int argc, __unused char **argv)
{

	int j = 0;
	//int ports[] = {8000, 8001};
	std::vector<Serv> servers_conf;
	servers_conf = parser();
	int numberOfServers = servers_conf.size();

	if (argc == 1) // 2
	{
		Server sr = Server();
												// это заглушка надо будет переписать
		sr.setConfigs(servers_conf);
		while (numberOfServers > j)
		{
			try
			{
				ServerUnit unit = ServerUnit(servers_conf[j].port);
				sr.addServerUnit(unit);
			}
			catch (std::exception &err){}
			j++;
		}

		sr.preprocess();

		do
		{
			if (sr.poll_process() == -1)
				exit(-1);//переписать под новый класс ***// ПРОВЕРИТЬ ЕСЛИ ОБРУБИТЬ СОЕДИНЕНИЕ ИЗ БРАУЗЕРА
		} while (sr.get_end_server() == FALSE);
		if (sr.getCompressArr())
		{
			sr.setCompressArr(FALSE);
			sr.ft_compress_array();
		}
		sr.close_fds();
	}
	else
		std::cout << "Wrong number of arguments" << std::endl;
	return (1);
}