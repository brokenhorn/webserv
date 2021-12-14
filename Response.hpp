#ifndef PARSERHTML_RESPONSE_HPP
#define PARSERHTML_RESPONSE_HPP

#include "iostream"
#include "string"
#include "map"
#include "vector"

class Response
{
private:
	std::string									_response;
	std::string									_protocol_version;
	int 										_code;
	std::map<int, std::string>					_status_message;
	std::map<std::string, std::string>			_headers;
	std::string									_body;
	std::string									_line;

	Response();
	Response(Response const &other);
};


#endif
