#ifndef _SCANIP_H_
#define _SCANIP_H_

#include <postgresql/libpq-fe.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;


class PG_admin {
    
public:
    int get_libpq_ver(); // Получить версию библиотеки libpq
    void Connect_db(string ip_adr, string db_name, string username, string passworld); // Функция для подключения к базе данных
    void executeQuery(const std::string &query); // Функция для выполнения SQL-запроса

private:
    int libpq_ver; // Хранит версию библиотеки
    PGconn* conn = NULL; // Указатель на соединение с базой данных

    void MaxColumnWidth(int *arr, PGresult *res, int &rows, int &fields); // Определяем максимальную ширину столбцов
    void Print_result(int *arr, PGresult *res, int &rows, int &fields); // Функция для вывода результатов
    int accumulate(int *arr, int fields); // Функция для подсчета суммы значений в массиве

};

#endif
