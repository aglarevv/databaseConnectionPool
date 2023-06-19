#include "connection.h"
#include "public.h"

Connection::Connection()
{
	conn = mysql_init(nullptr);
}

Connection::~Connection()
{
	if (conn != nullptr) {
		mysql_close(conn);
	}
}

bool Connection::connect(std::string ip, unsigned short port, std::string username,
	std::string password, std::string dbname)
{
	MYSQL* mysql = mysql_real_connect(conn, ip.c_str(), username.c_str(), 
		password.c_str(), dbname.c_str(), port, nullptr, 0);
	return mysql != nullptr;
}

bool Connection::update(std::string sql)
{
	if (mysql_query(conn, sql.c_str())) {
		LOG("¸üÐÂÊ§°Ü" + sql);
		std::cout << mysql_error(conn) << std::endl;
		std::cout << mysql_errno(conn) << std::endl;
		return false;
	}
	return true;
}

MYSQL_RES* Connection::query(std::string sql)
{
	if (mysql_query(conn, sql.c_str())) {
		LOG("²éÑ¯Ê§°Ü" + sql);
		return nullptr;
	}
	return mysql_use_result(conn);
}
