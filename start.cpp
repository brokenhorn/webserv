#include "Server.hpp"



int main(int argc, char **argv)
{
	int numberOfServers = 2;
	int j = 0;
	int ports[] = {8000, 8001};
	if (argc == 1) // 2
	{
		Server sr = Server();
		while (numberOfServers > j)
		{
			try
			{
				ServerUnit unit = ServerUnit(ports[j]);
				sr.addServerUnit(unit);
			}
			catch (std::exception err){}
			j++;
		}

		sr.preprocess();

		do
		{
			if (sr.poll_process() == -1)
				exit(-1);//переписать под новый класс
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