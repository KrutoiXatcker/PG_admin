#include <iostream>
#include <iostream>
#include "PG_admin.h"


int main(){

    PG_admin admin;
    std::string user_name, password, ip, db_name; 
    std::string query;
   
    std::cout << "Введите имя пользователя: ";
    std::getline(std::cin, user_name);
    std::cout << "Введите пароль: ";
    std::getline(std::cin, password);
    std::cout << "Введите IP адрес хоста (по умолчанию 127.0.0.1): ";
    std::getline(std::cin, ip);
    if (ip.empty()) ip = "127.0.0.1"; // Значение по умолчанию
    std::cout << "Введите имя базы данных: ";
    std::getline(std::cin, db_name);

    admin.Connect_db(ip,db_name,user_name,password);


    while (true) {
        std::cout << "Введите SQL-запрос (или 'exit' для выхода):\n";
        std::getline(std::cin,query);
        if (query == "exit") break;
        admin.executeQuery(query.c_str());
    }

    return 0;
}