#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "connection.h"
#include "connectionPool.h"

#if 0
int main(void)
{
#if 0
	clock_t begin = clock();
	for (int i = 0; i < 10000; ++i) {
		Connection conn;
		std::string sql = "insert into user(name,age,sex) values ('zangsan',20,'male')";
		conn.connect("127.0.0.1", 3306, "root", "aglarevv", "chat");
		conn.update(sql);
	}
	clock_t end = clock();
	std::cout << difftime(end, begin) << " ms" << std::endl;
#endif

#if 1
	ConnectionPool* pool = ConnectionPool::getConnectionPool();
	clock_t begin = clock();
	for (int i = 0; i < 10000; ++i) {
		std::shared_ptr<Connection> conn = pool->getConnection();
		std::string sql = "insert into user(name,age,sex) values ('zangsan',20,'male')";
		conn->update(sql);
	}
	clock_t end = clock();
	std::cout << difftime(end, begin) << " ms" << std::endl;
#endif

	return EXIT_SUCCESS;
}
#endif

int main() {
#if 0
	clock_t begin = clock();
	std::thread t1([]() {
		ConnectionPool* pool = ConnectionPool::getConnectionPool();
		for (int i = 0; i < 2500; ++i) {
			std::shared_ptr<Connection> conn = pool->getConnection();
			std::string sql = "insert into user(name,age,sex) values ('zangsan',20,'male')";
			conn->update(sql);
		}
		});
	std::thread t2([]() {
		ConnectionPool* pool = ConnectionPool::getConnectionPool();
		for (int i = 0; i < 2500; ++i) {
			std::shared_ptr<Connection> conn = pool->getConnection();
			std::string sql = "insert into user(name,age,sex) values ('zangsan',20,'male')";
			conn->update(sql);
		}
		});
	std::thread t3([]() {
		ConnectionPool* pool = ConnectionPool::getConnectionPool();
		for (int i = 0; i < 2500; ++i) {
			std::shared_ptr<Connection> conn = pool->getConnection();
			std::string sql = "insert into user(name,age,sex) values ('zangsan',20,'male')";
			conn->update(sql);
		}
		});
	std::thread t4([]() {
		ConnectionPool* pool = ConnectionPool::getConnectionPool();
		for (int i = 0; i < 2500; ++i) {
			std::shared_ptr<Connection> conn = pool->getConnection();
			std::string sql = "insert into user(name,age,sex) values ('zangsan',20,'male')";
			conn->update(sql);
		}
		});
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	clock_t end = clock();
	std::cout << difftime(end, begin) << " ms" << std::endl;
#endif 

#if 1
	Connection conn;
	conn.connect("127.0.0.1", 3306, "root", "aglarevv", "chat");
	clock_t begin = clock();
	std::thread t1([]() {
		for (int i = 0; i < 2500; ++i) {
			Connection conn;
			std::string sql = "insert into user(name,age,sex) values ('zangsan',20,'male')";
			conn.connect("127.0.0.1", 3306, "root", "aglarevv", "chat");
			conn.update(sql);
		}
		});
	std::thread t2([]() {
		for (int i = 0; i < 2500; ++i) {
			Connection conn;
			std::string sql = "insert into user(name,age,sex) values ('zangsan',20,'male')";
			conn.connect("127.0.0.1", 3306, "root", "aglarevv", "chat");
			conn.update(sql);
		}
		});
	std::thread t3([]() {
		for (int i = 0; i < 2500; ++i) {
			Connection conn;
			std::string sql = "insert into user(name,age,sex) values ('zangsan',20,'male')";
			conn.connect("127.0.0.1", 3306, "root", "aglarevv", "chat");
			conn.update(sql);
		}
		});
	std::thread t4([]() {
		for (int i = 0; i < 2500; ++i) {
			Connection conn;
			std::string sql = "insert into user(name,age,sex) values ('zangsan',20,'male')";
			conn.connect("127.0.0.1", 3306, "root", "aglarevv", "chat");
			conn.update(sql);
		}
		});
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	clock_t end = clock();
	std::cout << difftime(end, begin) << " ms" << std::endl;
#endif
}

