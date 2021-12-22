#include "Response.hpp"

int main()
{
	std::string		line = "GET /site/str.html?login=true HTTP/1.1\r\n"
							  "Content-Type: image/jpeg; charset=utf-8\r\n"
							  "Host: local:8080\r\n"
							  "Content-Length: 19912\r\n\r\n"
							  "<HTML></HTML>\r\n";
	std::string		line1 = "GET / HTTP/1.1\r\n"
							   "Host: localhost:8000\r\n"
							   "Connection: keep-alive\r\n"
							   "Cache-Control: max-age=0\r\n"
							   "sec-ch-ua: \" Not A;Brand\";v=\"99\", \"Chromium\";v=\"96\", \"Google Chrome\";v=\"96\"\r\n"
							   "sec-ch-ua-mobile: ?0\r\n"
							   "sec-ch-ua-platform: \"macOS\"\r\n"
							   "Upgrade-Insecure-Requests: 1\r\n"
							   "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.55 Safari/537.36\r\n"
							   "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\n"
							   "Sec-Fetch-Site: cross-site\r\n"
							   "Sec-Fetch-Mode: navigate\r\n"
							   "Sec-Fetch-User: ?1\r\n"
							   "Sec-Fetch-Dest: document\r\n"
							   "Accept-Encoding: gzip, deflate, br\r\n"
							   "Accept-Language: en-US,en;q=0.9\r\n\r\n";
	Request		request(line1);
	Serv		serv;
	Location	location;
	location.location = "/";
	serv.locations.push_back(location);
	Response	response(request, serv);
	std::cout << request.getCode() << std::endl << request.getPort() << std::endl;
	return 0;
}
