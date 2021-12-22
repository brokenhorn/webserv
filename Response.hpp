#ifndef PARSERHTML_RESPONSE_HPP
#define PARSERHTML_RESPONSE_HPP

#include "Request.hpp"
#include "../parser/parser.hpp"


class Response
{
private:
	Request										_request;
	Location									_location;
	Serv										_serv;
	std::string									_response;
	std::string									_header;
	std::string									_type;
	std::string									_protocol_version;
	int 										_code;
	std::map<int, std::string>					_status_message;
	std::map<std::string, std::string>			_headers;
	std::string									_body;

	Response();
	Response(Response const &other);

	void										initStatusMessage();
	void										takeLocation();
	void										startMethod();
	void										Get();
	void										Post();
	void										Delete();
	const std::string							&makeDate() const;

public:
	Response(Request const &request, Serv const &conf);
	~Response();
	Response &operator =(Response const &other);

	const std::string							&getResponse() const;
};

#endif
