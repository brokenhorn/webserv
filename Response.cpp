#include "Response.hpp"

Response::Response(Request const &request, Serv const &conf) : _code(request.getCode()), _protocol_version(request.getProtocol_version()),
																_serv(conf), _location(), _request(request)
{
	takeLocation();
	initStatusMessage();

//	_header = _protocol_version + " " + std::to_string(_code) + " " + _status_message[_code] + "\r\n";
//	startMethod();
//	_response = getHeader(_response.size(), Conf.path, _code, _type, Conf.ContentLocation, Conf.Language) + "\r\n" + _response;
}

Response::~Response() {}

Response &Response::operator =(Response const &other)
{
	this->_body = other._body;
	this->_code = other._code;
	this->_headers = other._headers;
	this->_protocol_version = other._protocol_version;
	this->_response = other._response;
	this->_status_message = other._status_message;

	return *this;
}

void	Response::initStatusMessage()
{
	_status_message[100] = "Continue";
	_status_message[200] = "OK";
	_status_message[201] = "Created";
	_status_message[204] = "No Content";
	_status_message[400] = "Bad Request";
	_status_message[403] = "Forbidden";
	_status_message[404] = "Not Found";
	_status_message[405] = "Method Not Allowed";
	_status_message[413] = "Payload Too Large";
	_status_message[500] = "Internal Server Error";
	_status_message[505] = "HTTP Version Not Supported";
}

//void	Response::startMethod()
//{
//	std::map< std::string, std::function<void()> > map;
//
//	map["GET"] = &Response::Get;
//	map["POST"] = &Response::Post;
//	map["DELETE"] = &Response::Delete;
//
////	if (std::find(_location.methods.begin(), _location.methods.end(), _request.getMethod()) != _location.methods.end())
////		this->_code = 405;
////	else if (_location.max_body != -1 && _request.getBody().size() > _location.max_body)
////		this->_code = 413;
////	else
////		map[_request.getMethod()]();
//
//	//	ЧТО ДЕЛАТЬ ЕСЛИ 405 ИЛИ 413
//}

void	Response::takeLocation()
{
	std::vector<Location>::iterator it;

	it = _serv.locations.begin();
	while (it != _serv.locations.end())
	{
		if ((*it).location == _request.getPath())
		{
			_location = *it;
			break;
		}
		it++;
	}
	if (_location.location == "")
		this->_code = 404;
}

//void	Response::Get()
//{
//	std::string		str;
//
//	if (Conf.CgiPass != "")
//	{
//		int		i = 0;
//		int		j = _response.size() - 2;
//
//		//_response = из cgi
//
//		while (_response.find("\r\n\r\n", i) != std::string::npos || _response.find("\r\n", i) == i)
//		{
//			str = _response.substr(i, _response.find("\r\n", i) - i);
//			if (str.find("Status: ") == 0)
//				_code = std::atoi(str.substr(8, 3).c_str());
//			else if (str.find("Content-type: ") == 0)
//				_type = str.substr(14, str.size());
//			i += str.size() + 2;
//		}
//		while (_response.find("\r\n", j) == j)
//			j -= 2;
//
//		_response = _response.substr(i, j - i);
//	}
//	else if  (_code == 200)
//		_code = readContent();
//	else
//		_response = readHtml(_serv.error_page[_code]);
//	if (_code == 500)
//		_response = readHtml(_serv.error_page[_code]);
//}
//
//void	Response::Post()
//{
//	if (Conf.CgiPass != "")
//	{
//		size_t		i = 0;
//		size_t		j = _response.size() - 2;
//
//		//_response = из cgi
//
//		while (_response.find("\r\n\r\n", i) != std::string::npos || _response.find("\r\n", i) == i)
//		{
//			std::string	str = _response.substr(i, _response.find("\r\n", i) - i);
//			if (str.find("Status: ") == 0)
//				_code = std::atoi(str.substr(8, 3).c_str());
//			else if (str.find("Content-Type: ") == 0)
//				_type = str.substr(14, str.size());
//			i += str.size() + 2;
//		}
//		while (_response.find("\r\n", j) == j)
//			j -= 2;
//
//		_response = _response.substr(i, j - i);
//	}
//	else
//	{
//		_code = 204;
//		_response = "";
//	}
//	if (_code == 500)
//		_response = readHtml(_serv.error_page[_code]);
//}
//
//void	Response::Delete()
//{
//	(void)_request;
//
//	_response = "";
//	if (pathIsFile(_request.getPath()))
//	{
//		if (remove(_request.getPath().c_str()) == 0)
//			_code = 204;
//		else
//			_code = 403;
//	}
//	else
//		_code = 404;
//	if (_code == 403 || _code == 404)
//		_response = this->readHtml(_serv.error_page[_code]);
//}

const std::string	&Response::makeDate() const
{
	time_t		now;
	struct tm	tm;
	char		buf[100];
	std::string answer;

	now = time(0);
	tm = *gmtime(&now);
	strftime(buf, sizeof(buf), "%a, %d %b %Y %X", &tm);
	answer = buf;
	answer += " GMT";
	return answer;
}

const std::string	&Response::getResponse() const { return _response; }