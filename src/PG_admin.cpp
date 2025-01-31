#include "PG_admin.h"

// Функция для подключения к базе данных
bool PG_admin::Connect_db(string ip_adr, string db_name, string username, string passworld) {
    // Формирование строки подключения к БД
    string conn_srt = "user=" + username + " password=" + passworld + " host=" + ip_adr + " dbname=" + db_name;
    conn = PQconnectdb(conn_srt.c_str()); // Попытка подключения
    // Проверка статуса подключения
    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Ошибка подключения к базе данных: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return 0;
    }
    else 
        return 1;
}

// Функция для выполнения SQL-запроса
void PG_admin::executeQuery(const std::string &query) {
    PGresult *res = PQexec(conn, query.c_str()); // Выполнение запроса
    
    // Проверка статуса результата
    if (PQresultStatus(res) != PGRES_TUPLES_OK && PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Ошибка выполнения запроса: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        return;
    }

    int rows = PQntuples(res); // Получаем количество строк
    int fields = PQnfields(res); // Получаем количество полей

    // Создаем массив для хранения максимальной ширины столбцов
    int *arr = new int[fields](); // Выделяем память и инициализируем нулями
    
    // Вызываем функцию для получения максимальной ширины каждой колонки
    MaxColumnWidth(arr, res, rows, fields);
    
    // Вывод результата запроса на экран
    Print_result(arr, res, rows, fields);    

    // Чистим за собой
    delete[] arr; 
    PQclear(res); // Освобождаем ресурсы
}

// Находим максимальную длину для каждого столбца для корректного вывода
void PG_admin::MaxColumnWidth(int *arr, PGresult *res, int &rows, int &fields) {
    for (int j = 0; j < fields; j++) {
        arr[j] = strlen(PQfname(res, j)) + 5; // Начальная ширина по заголовку
        // Проходим по всем строкам для обновления максимальной ширины
        for (int i = 0; i < rows; i++) {
            int valueLength = strlen(PQgetvalue(res, i, j)) + 5; // Длина значения
            if (arr[j] < valueLength) {
                arr[j] = valueLength; // Обновляем максимальную длину
            }
        }
    }
}

// Функция для вывода данных
void PG_admin::Print_result(int *arr, PGresult *res, int &rows, int &fields) {
    std::cout << std::endl;

    // Вывод заголовков
    for (int j = 0; j < fields; j++) {
        std::cout << std::setw(arr[j]) << std::left << PQfname(res, j); 
    }
    std::cout << std::endl;

    // Вывод разделителя
    std::cout << std::setfill('-') << std::setw(accumulate(arr, fields)) << "" << std::setfill(' ') << std::endl;

    // Вывод данных
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < fields; j++) {
            std::cout << std::setw(arr[j]) << std::left << PQgetvalue(res, i, j);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Функция для подсчета суммы значений в массиве
int PG_admin::accumulate(int *arr, int fields) {
    int result = 0;
    for (int i = 0; i < fields; i++) {
        result += arr[i]; // Суммируем значения
    }
    return result;
}
