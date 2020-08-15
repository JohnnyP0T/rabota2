#include <thread>
#include <chrono>
#include <iostream>
#include "Server.h"
using namespace std;

int main() {
    cout << "Запуск сервера в бесконечном цикле. Ожидание данных от программы №1" << endl;
	Server server;
    server.StartServer();

}