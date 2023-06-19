#pragma once
#include <string>
#include <queue>
#include "connection.h"
#include "public.h"
#include <atomic>
#include <functional>
#include <memory>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <ctime>


class ConnectionPool
{
public:

	static ConnectionPool* getConnectionPool();
	std::shared_ptr<Connection> getConnection();

private:
	ConnectionPool();

	void produceConnectionTask();
	void connectionTimmingTask();

	std::string ip;
	unsigned short port;
	std::string username;
	std::string password;
	std::string dbname;
	int initSize;
	int maxSize;
	int maxIdleTime;
	int connectionTimeout;

	std::queue<Connection*> connectionPool;
	std::mutex queueMutex;
	std::atomic_int connectionCount;
	std::condition_variable conditionVariable;

	bool loadConfigFile();

	
};
