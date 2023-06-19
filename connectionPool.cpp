#include "connectionPool.h"
#include <fstream>
#include <cstdlib>


ConnectionPool* ConnectionPool::getConnectionPool()
{
	static ConnectionPool pool;
	return &pool;
}

std::shared_ptr<Connection> ConnectionPool::getConnection()
{
	std::unique_lock<std::mutex> lock(queueMutex);
	while (connectionPool.empty()) {
		if (std::cv_status::timeout ==
			conditionVariable.wait_for(lock, std::chrono::milliseconds(connectionTimeout))) {
			if (connectionPool.empty()) {
				LOG("���ӳ�ʱ");
				return nullptr;
			}
		}
	}
	//�Զ�����շ�ʽ�������ӹ黹������
	std::shared_ptr<Connection> connection(connectionPool.front(), [&](Connection* pconn) {
		std::unique_lock<std::mutex> lock(queueMutex);
		pconn->updataTime();
		connectionPool.push(pconn);
		});
	connectionPool.pop();
	conditionVariable.notify_all();
	return connection;
}

ConnectionPool::ConnectionPool()
{
	if (!loadConfigFile()) {
		return;
	}
	for (int i = 0; i < initSize; ++i)
	{
		Connection* conn = new Connection();
		conn->connect(ip, port, username, password, dbname);
		conn->updataTime();
		connectionPool.push(conn);
		connectionCount++;
	}
	//���������߳�
	std::thread produceConnectionThread(std::bind(&ConnectionPool::produceConnectionTask,this));
	produceConnectionThread.detach();
	//��ʱ����߳�
	std::thread connectionTimmingThread(std::bind(&ConnectionPool::connectionTimmingTask, this));
	connectionTimmingThread.detach();
}
//����
void ConnectionPool::produceConnectionTask()
{
	while(true) {

		std::unique_lock<std::mutex> lock(queueMutex);
		while (!connectionPool.empty()) {
			conditionVariable.wait(lock);
		}
		if (connectionCount < maxSize) {
			Connection* conn = new Connection();
			conn->connect(ip, port, username, password, dbname);
			conn->updataTime();
			connectionPool.push(conn);
			connectionCount++;
		}
		conditionVariable.notify_all();
	}
}
//��ʱ���
void ConnectionPool::connectionTimmingTask()
{
	while (true) {
		//��ʱ
		std::this_thread::sleep_for(std::chrono::seconds(maxIdleTime));
		std::unique_lock<std::mutex> lock(queueMutex);
		while (connectionCount > initSize) {
			Connection* pconn = connectionPool.front();
			if (pconn->getAliveTime() >= maxIdleTime * 1000) {
				connectionPool.pop();
				connectionCount--;
				delete pconn;
			}
			else {
				break;
			}
		}
	}
}

bool ConnectionPool::loadConfigFile()
{
	FILE* fp = fopen("mysqlconfig.ini", "r");
	if (fp == nullptr) {
		LOG("mysqlconfig.ini file open error");
		return false;
	}
	while (!feof(fp)) {
		char buf[1024] = { 0 };
		fgets(buf, 1024, fp);
		std::string str = buf;
		int index = str.find('=', 0);
		if (index == -1) {
			continue;
		}
		int endindex = str.find('\n', index);
		std::string key = str.substr(0, index);
		std::string value = str.substr(index + 1, endindex - index - 1);
		if (key == "ip") {
			ip = value;
		}
		else if (key == "port") {
			port = atoi(value.c_str());
		}
		else if (key == "username") {
			username = value;
		}
		else if (key == "password") {
			password = value;
		}
		else if (key == "dbname") {
			dbname = value;
		}
		else if (key == "initSize") {
			initSize = atoi(value.c_str());
		}
		else if (key == "maxSize") {
			maxSize = atoi(value.c_str());
		}
		else if (key == "maxIdleTime") {
			maxIdleTime = atoi(value.c_str());
		}
		else if (key == "connectionTimeout") {
			connectionTimeout = atoi(value.c_str());
		}
	}
	return true;
}