#pragma once

#include <string>
#include "public.h"
#include <ctime>

class Connection {
public:
	Connection();
	~Connection();
	bool connect(std::string ip, unsigned short port, 
		std::string username, std::string password, std::string dbname);
	bool update(std::string sql);
	MYSQL_RES* query(std::string sql);

	void updataTime() { aliveTime = clock(); }
	std::clock_t getAliveTime() const { return difftime(clock(), aliveTime); }
private:
	MYSQL* conn;
	std::clock_t aliveTime;
};