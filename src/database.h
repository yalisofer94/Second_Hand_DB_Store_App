#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <cstring>
#include <mysql.h>
using namespace std;

#define SERVER "localhost"
#define USER "root"
#define PASSWORD "123qwe321"
#define DATABASE "second_hand_books"

class MySQL
{
protected:
    /** MySQL connectivity Variables */
    MYSQL *connect;
    MYSQL_RES *res_set;
    MYSQL_ROW row;

    unsigned int i;

public:
    MySQL();
    ~MySQL();

    char *stringToChar(string str);
    void query_1();
    void query_2();
    void query_3();
    void query_4();
    void query_5();
    void query_6();
    void query_7();
    void query_8();
    void query_9();
    void query_10();
    void query_11();
    void query_12();
    void query_13();
    void query_14();
    void query_15();
    void query_16();
    void query_17();
    void query_18();
    void query_19();
    void query_20();
    void query_21();
    void query_22();
    void query_23();
    void query_24();
    void query_25();
    void query_26();
};
