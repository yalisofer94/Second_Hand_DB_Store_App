#include "database.h"
using namespace std;

MySQL ::MySQL()
{
    connect = mysql_init(NULL);
    if (!connect)
    {
        cout << "MySQL Initialization Failed";
    }

    connect = mysql_real_connect(connect, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0);

    if (connect)
    {
        cout << "Connection Succeeded\n";
    }

    else
    {
        cout << "Connection Failed\n";
    }
}

MySQL ::~MySQL()
{
    mysql_close(connect);
}

char *MySQL::stringToChar(string str)
{
    int n = str.length();
    char *cstr = new char[n + 1];
    copy(str.begin(), str.end(), cstr);
    cstr[n] = '\0';
    return cstr;
}

bool validDate(string date)
{
    if (date[4] != '-' || date[7] != '-' || date.size() != 10)
        return false;

    char delimiter = '-';
    int year = 0, month = 0, day = 0;

    string yearStr = date.substr(0, 4);
    string monthStr = date.substr(date.find(delimiter) + 1, date.find(delimiter) - 2);
    string dayStr = date.substr(8, 9);

    year = stoi(yearStr);
    month = stoi(monthStr);
    day = stoi(dayStr);

    if (year < 0 || month < 0 || month > 12 || day < 0 || day > 30)
        return false;

    return true;
}

//--------------------------------------------QUERIES------------------------------------------

void MySQL::query_1()
{
    string part1 = "select (warehouse_inventory + store_inventory) as in_stock from books_details bd left join inventory i on i.book_id = bd.book_id where bd.title ='";
    string part2 = "';";
    string user;

    cout << "Enter book title:" << endl;
    cin.ignore();
    getline(cin, user);

    part1 = part1 + user + part2;
    char *final_query = stringToChar(part1);

    /** Add MySQL Query */
    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        row = mysql_fetch_row(res_set);
        cout << "The book is in stock! amount[" << row[0] << "]" << endl;
    }
    else
        cout << "Sorry, can't find '" << user << "' book" << endl;
    system("pause");
}

void MySQL::query_2()
{
    string q2 = "select concat(customer_first_name, ' ', customer_last_name) as full_name, MIN(transaction_date) as 'date'\
                 from transactions t\
                 left join transaction_details td on td.transaction_id = t.transaction_id\
                 left join customers c on c.customer_id = t.customer_id\
                 left join books_details bd on bd.book_id = td.book_id; ";

    char *final_query = stringToChar(q2);

    /** Add MySQL Query */
    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        row = mysql_fetch_row(res_set);
        cout << "Oldest customer is " << row[0] << endl;
    }
    else
        cout << "Sorry, can't find oldest customer" << endl;
    system("pause");
}

void MySQL::query_3()
{
    string q3 = "select title from\
                (select transaction_date, bd.book_id, title from\
                    (select transaction_date, td.book_id  from transactions t\
                        left join transaction_details td on td.transaction_id = t.transaction_id\
                        group by transaction_date order by transaction_date desc) PURCHASE\
                        left join books_details bd ON bd.book_id = PURCHASE.book_id\
                    group by bd.book_id) as allbks order by transaction_date asc limit 1; ";

    char *final_query = stringToChar(q3);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        row = mysql_fetch_row(res_set);
        cout << "Oldest book in stock is '" << row[0] << "'" << endl;
    }
    else
        cout << "Sorry, can't find oldest book" << endl;
    system("pause");
}

void MySQL::query_4()
{
    string q4 = "select order_id, customer_id, order_date, payment_method_name, shipping_type_name from orders o\
                 join payment_method pm on pm.payment_method_id = o.payment_method\
                 join shipping_types st on st.shipping_type_id = o.shipping_method\
                 where shipping_status != 'Collected'\
                 order by order_date; ";

    char *final_query = stringToChar(q4);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    cout << "Current orders are:" << endl;

    if (res_set != nullptr && res_set->row_count != 0)
    {
        cout << "order id\t"
             << "customer id\t"
             << "order date\t"
             << "payment method\t"
             << "shipping type\t" << endl;
        while (((row = mysql_fetch_row(res_set)) != NULL))
            cout << "\t" << row[0] << "\t\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t\t" << row[4] << endl;
    }
    else
        cout << "No orders to this date!" << endl;

    system("pause");
}

void MySQL::query_5()
{
    string q5_part1 = "select sum(amount) as num_of_copys from transactions t \
                 right join  transaction_details td on td.transaction_id = t.transaction_id\
                 right join books_details bd on bd.book_id = td.book_id\
                 where title = '";
    string q5_part2 = "';";
    string user;

    cout << "Enter book title:" << endl;
    cin.ignore();
    getline(cin, user);

    q5_part1 = q5_part1 + user + q5_part2;
    char *final_query = stringToChar(q5_part1);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        row = mysql_fetch_row(res_set);
        if (*row != nullptr)
            cout << "The book '" << user << "' sold " << row[0] << " copies" << endl;
        else
            cout << "can't find any transaction record with '" << user << "' book" << endl;
    }
    system("pause");
}

void MySQL::query_6()
{
    string q6 = "select author_name from\
                       (select td.transaction_id, book_id, amount from transactions t\
                       left join transaction_details td on td.transaction_id = t.transaction_id\
                       where transaction_date between '";
    string firstDate;
    string secondDate;
    string and = "' and '";
    string rest = "') times_of_transactions\
                   left join books_details on books_details.book_id = times_of_transactions.book_id\
                   left join authors a on a.book_id = books_details.book_id\
                   group by author_name order by amount desc limit 1; ";

    cout << "Enter first date: by this pattern YYYY-MM-DD" << endl;
    cin >> firstDate;

    cout << "Enter second date: by this pattern YYYY-MM-DD" << endl;
    cin >> secondDate;

    if (validDate(firstDate) && validDate(secondDate))
    {
        q6 = q6 + firstDate + and+secondDate + rest;
        char *final_query = stringToChar(q6);

        mysql_query(connect, final_query);
        delete final_query;

        res_set = mysql_store_result(connect);

        if (res_set != nullptr && res_set->row_count != 0)
        {
            row = mysql_fetch_row(res_set);
            cout << "The most read autor is " << row[0] << endl;
        }
        else
            cout << "Sorry, can't find most read autor" << endl;
    }
    else
        cout << "Invalid dates!" << endl;

    system("pause");
}

void MySQL::query_7()
{
    string q7 = "select concat(customer_first_name, ' ', customer_last_name) as full_name, SUM(amount) as total, customers.customer_id from\
                (select transaction_details.transaction_id, book_id, amount, customer_id from transactions t\
                left join transaction_details on transaction_details.transaction_id = t.transaction_id) as sold_bet\
                left join customers on customers.customer_id = sold_bet.customer_id\
                group by customer_id order by total desc limit 3; ";

    char *final_query = stringToChar(q7);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        cout << "---------------Top 3 Customers---------------" << endl;
        cout << "full name\t"
             << "total\t"
             << "customer id\t" << endl;
        while (((row = mysql_fetch_row(res_set)) != NULL))
            cout << row[0] << "\t" << row[1] << "\t" << row[2] << endl;
    }
    else
        cout << "Error" << endl;

    system("pause");
}

void MySQL::query_8()
{
    string q8 = "select bd.title from books_details bd\
                 join books_details s_bd on  bd.title = s_bd.title\
                 where bd.interpreter != s_bd.interpreter\
                 group by title order by count(bd.interpreter) desc LIMIT 1; ";

    char *final_query = stringToChar(q8);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        row = mysql_fetch_row(res_set);
        cout << "The book with the most interpreters is '" << row[0] << "'" << endl;
    }
    else
        cout << "Sorry, can't find the book with the most interpreters" << endl;
    system("pause");
}

void MySQL::query_9()
{
    string q9 = "select concat(customer_first_name, ' ' ,customer_last_name)as full_name, transaction_date, title, amount, customer_price, (customer_price * amount) as total\
                 from transactions t \
                 join customers c on t.customer_id = c.customer_id\
                 join transaction_details td on t.transaction_id = td.transaction_id\
                 join books_details bd on bd.book_id = td.book_id\
                 join books_prices bp on bp.book_id = td.book_id\
                 where customer_first_name = '";

    string and = " and customer_last_name = '";
    string rest = "order by transaction_date;";
    string fname;
    string lname;

    cout << "Enter customer first name: " << endl;
    cin >> fname;
    cout << "Enter customer last name: " << endl;
    cin >> lname;

    q9 = q9 + fname + "'" + and+lname + "' " + rest;

    char *final_query = stringToChar(q9);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        cout << "full name\t"
             << "transaction date\t"
             << "book title\t"
             << "amount\t"
             << "price\t"
             << "total price" << endl;
        while (((row = mysql_fetch_row(res_set)) != NULL))
            cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t\t" << row[3] << "\t" << row[4] << "\t" << row[5] << endl;
    }
    else
        cout << "No transactions record for '" << fname << " " << lname << "'" << endl;

    system("pause");
}

void MySQL::query_10()
{
    string q10 = "select concat(customer_first_name, ' ', customer_last_name) as full_name, order_date, title, total_amount, customer_price, \
                  (total_amount*customer_price) as total\
                  from orders o\
                  join customers c on o.customer_id = c.customer_id\
                  join order_details od on o.order_id = od.order_id\
                  join books_details bd on bd.book_id = od.book_id\
                  join books_prices bp on bp.book_id = od.book_id\
                  where customer_first_name = '";

    string and = "' and customer_last_name = '";
    string rest = "' order by order_date;";
    string fname;
    string lname;

    cout << "Enter customer first name: " << endl;
    cin >> fname;
    cout << "Enter customer last name: " << endl;
    cin >> lname;

    q10 = q10 + fname + and+lname + rest;

    char *final_query = stringToChar(q10);
    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        cout << "full name\t"
             << "order date\t"
             << "book title\t"
             << "amount\t"
             << "book price\t"
             << "total cost" << endl;
        while (((row = mysql_fetch_row(res_set)) != NULL))
            cout << row[0] << "\t\t" << row[1] << "\t" << row[2] << "\t" << row[3] << "\t" << row[4] << "\t\t" << row[5] << endl;
    }
    else
        cout << "No orders record for '" << fname << " " << lname << "'" << endl;

    system("pause");
}

void MySQL::query_11()
{
    string q11 = "select sum(total_amount*weight) as total_weight , shipping_type_price, shipping_type_name, ( sum(total_amount*weight) * 3 + shipping_type_price) as\
                  total_price, sum(total_amount*weight) * 3 from books_details bd\
                  join order_details od on od.book_id = bd.book_id\
                  join orders o on o.order_id = od.order_id\
                  join shipping_types st on st.shipping_type_id = o.shipping_method\
                  where o.order_id = ";

    string orderIdUser;
    cout << "Enter order id: ";
    cin >> orderIdUser;

    q11 = q11 + orderIdUser + ";";

    char *final_query = stringToChar(q11);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        row = mysql_fetch_row(res_set);
        if (*row != nullptr)
        {
            cout << "Calculating order No." << orderIdUser << " cost . . . [we charge 3$ per 1 kilo]" << endl;
            cout << "shipping method '" << row[2] << "' charges: " << row[1] << "$" << endl;
            cout << "+ order total weight: " << row[0] << " * 3$[a kilo] = " << row[4] << "$" << endl;
            cout << ">> total order cost: " << row[3] << "$" << endl;
        }
        else
            cout << "Sorry, no data for order No." << orderIdUser << endl;
    }

    system("pause");
}

void MySQL::query_12()
{
    string q12 = "select concat(customer_first_name, ' ', customer_last_name) as full_name, o.order_id, o.order_date, title, total_amount, o.shipping_status,                                payment_method_name, shipping_type_name\
                  from orders a, orders o\
                  join customers c on o.customer_id = c.customer_id\
                  join order_details od on o.order_id = od.order_id\
                  join shipping_types st on o.shipping_method = st.shipping_type_id\
                  join second_hand_books.payment_method pm on o.payment_method = pm.payment_method_id\
                  join books_details bd on bd.book_id = od.book_id\
                  where customer_first_name = '";

    string and = "' and customer_last_name = '";
    string rest = "' and o.order_date = a.order_date and o.order_id != a.order_id;";
    string fname;
    string lname;

    cout << "Enter customer first name: " << endl;
    cin >> fname;
    cout << "Enter customer last name: " << endl;
    cin >> lname;

    q12 = q12 + fname + and+lname + rest;

    char *final_query = stringToChar(q12);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        cout << "full name\t"
             << "order id\t"
             << "order date\t"
             << "book title\t"
             << "amount\t"
             << "shipping status\t"
             << "payment meyhod\t"
             << "shipping type" << endl;
        while (((row = mysql_fetch_row(res_set)) != NULL))
            cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t\t" << row[3] << "\t" << row[4] << "\t" << row[5] << "\t" << row[6] << "\t" << row[7] << endl;
    }
    else
        cout << "No record of split orders for '" << fname << " " << lname << "'" << endl;

    system("pause");
}

void MySQL::query_13()
{
    string q13 = "select o.order_id, concat(customer_first_name, ' ', customer_last_name) as full_name, o.order_date, shipping_type_name, shipping_status from orders o\
                  join customers c on o.customer_id = c.customer_id\
                  join order_details od on o.order_id = od.order_id\
                  join shipping_types st on o.shipping_method = st.shipping_type_id\
                  where o.order_id = ";

    string order_id;
    string end = ";";
    cout << "Enter order id: " << endl;
    cin >> order_id;

    q13 = q13 + order_id + end;

    char *final_query = stringToChar(q13);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        cout << "order id\t"
             << "customer\t"
             << "order date\t"
             << "shipping type\t"
             << "shipping status" << endl;
        while (((row = mysql_fetch_row(res_set)) != NULL))
            cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t\t" << row[3] << "\t" << row[4] << endl;
    }
    else
        cout << "No record of order No. " << order_id << endl;

    system("pause");
}

void MySQL::query_14()
{
    string q14 = "select count(order_id) as total_shipping_by_Xpress from orders o\
                  where(shipping_method between 4 and 5) and (month(order_date) = ";

    string userMonth;
    string end = ");";
    cout << "Enter month [1-12]: " << endl;
    cin >> userMonth;

    q14 = q14 + userMonth + end;

    char *final_query = stringToChar(q14);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        row = mysql_fetch_row(res_set);
        cout << "In month No. " << userMonth << " total amount of shipping by Xprees is " << row[0] << endl;
    }
    else
        cout << "No shipping by Xpress in " << userMonth << endl;
    system("pause");
}

void MySQL::query_15()
{
    string q15 = "select transaction_date, t.transaction_id , sum(customer_price * amount) as total_by_bit from transaction_details td\
                  join books_prices bp on td.book_id = bp.book_id\
                  join transactions t on t.transaction_id = td.transaction_id\
                  where(payment_method = 1) and (month(transaction_date) = ";

    string userMonth;
    string end = ");";
    cout << "Enter month [1-12]: " << endl;
    cin >> userMonth;

    q15 = q15 + userMonth + end;

    char *final_query = stringToChar(q15);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        row = mysql_fetch_row(res_set);
        if (*row != nullptr)
            cout << "Total income from Bit in month No. " << userMonth << " is " << row[2] << "$" << endl;
        else
            cout << "No income from Bit in month No.in " << userMonth << endl;
    }

    system("pause");
}

void MySQL::query_16()
{
    string q16 = "select td.transaction_id, transaction_date, (amount * customer_price) as income from transaction_details td\
                  join books_prices bp on td.book_id = bp.book_id\
                  join transactions t on t.transaction_id = td.transaction_id\
                  where(amount * customer_price) > (\
                  select avg(amount * customer_price) as _avg from transaction_details td\
                  join books_prices bp on td.book_id = bp.book_id\
                  join transactions t on t.transaction_id = td.transaction_id\
                  where transaction_date between date_sub(now(), interval 12 month) and now())\
                  and (transaction_date between date_sub(now(), interval 12 month) and now()); ";

    char *final_query = stringToChar(q16);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        cout << "transaction id\t"
             << "transaction date\t"
             << "above avg\t" << endl;
        while (((row = mysql_fetch_row(res_set)) != NULL))
            cout << row[0] << "\t\t" << row[1] << "\t\t" << row[2] << "$" << endl;
    }
    else
        cout << "Error" << endl;
    system("pause");
}

void MySQL::query_17()
{
    string q17 = "select sum(shipping_method between 4 and 5) as total_orders_Xpress, sum(shipping_method between 1 and 3) as total_orders_IRpost\
                  from orders\
                  where(order_date between date_sub(now(), interval 12 month) and now()); ";

    char *final_query = stringToChar(q17);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        cout << "Orders Xpress\t"
             << "Orders ISR Post\t" << endl;
        while (((row = mysql_fetch_row(res_set)) != NULL))
            cout << row[0] << "\t\t" << row[1] << endl;
    }
    else
        cout << "Error" << endl;
    system("pause");
}

void MySQL::query_18()
{
    string q18 = "select distinct bd.publisher, oo.order_id, bd.title, o.order_date, o.customer_id from books_details bd\
                  right join order_details od on od.book_id = bd.book_id\
                  right join orders o on o.order_id = od.order_id\
                  right join orders oo on oo.order_date = o.order_date and (oo.order_id = o.order_id)\
                  right join books_details bdd on bdd.publisher != bd.publisher and bd.book_id != bdd.book_id and bd.publishing_year = bdd.publishing_year\
                  where bd.title = bdd.title and o.order_id = od.order_id and o.order_id = oo.order_id and bdd.publisher != bd.publisher and o.order_id = 13\
                  order by o.order_id; ";

    char *final_query = stringToChar(q18);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        cout << "publisher\t"
             << "order id\t"
             << "title\t\t"
             << "order date\t"
             << "customer id\t" << endl;
        while (((row = mysql_fetch_row(res_set)) != NULL))
            cout << row[0] << "\t\t" << row[1] << "\t\t" << row[2] << "\t\t" << row[3] << "\t\t" << row[4] << endl;
    }
    else
        cout << "Error" << endl;
    system("pause");
}

void MySQL::query_19()
{
    string q19 = "select c.customer_id, concat(customer_first_name, ' ',customer_last_name) as full_name, transaction_date from customers c\
                  join transactions t on t.customer_id = c.customer_id\
                  where transaction_date not between date_sub(now(), interval 24 month) and now()\
                  group by customer_id; ";

    char *final_query = stringToChar(q19);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        cout << "customer id\t"
             << "customer name\t"
             << "last transaction\t" << endl;
        while (((row = mysql_fetch_row(res_set)) != NULL))
            cout << row[0] << "\t\t" << row[1] << "\t\t" << row[2] << endl;
    }
    else
        cout << "Error" << endl;
    system("pause");
}

void MySQL::query_20()
{
    string q20 = "select concat(customer_first_name, ' ', customer_last_name) as full_name, order_date from customers c\
                  join orders o on o.customer_id = c.customer_id\
                  where shipping_status = 'Pendding' and order_status = 'Contacted client 14 days ago or more'\
                  order by order_date; ";

    char *final_query = stringToChar(q20);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        cout << "customer name\t"
             << "order date\t" << endl;
        while (((row = mysql_fetch_row(res_set)) != NULL))
            cout << row[0] << "\t\t" << row[1] << "\t\t" << endl;
    }
    else
        cout << "Error" << endl;
    system("pause");
}

void MySQL::query_21()
{
    string q21 = "select(sum(warehouse_inventory) - books_sold) as in_stock from inventory i\
                  join(select sum(total_amount) as books_sold from order_details od\
                  left join orders o on od.order_id = o.order_id\
                  where month(order_date) = ";

    string q21a = " and year(order_date) = 2019) as p; ";

    for (int i = 1; i < 13; i++)
    {
        string newQ = q21 + to_string(i) + q21a;

        char *final_query = stringToChar(newQ);

        mysql_query(connect, final_query);
        delete final_query;
        newQ.clear();

        res_set = mysql_store_result(connect);

        if (res_set != nullptr && res_set->row_count != 0)
        {
            row = mysql_fetch_row(res_set);
            cout << "total books in warehounse in month No." << i << " is " << row[0] << endl;
        }
        else
            cout << "No data regarding warehouse inventory in month No." << i << endl;
    }
    system("pause");
}

void MySQL::query_22()
{
    string q22 = "select sum(books_amount) as books_amount, sum(books_amount * store_price) as total_spend from store_purchases sp\
                  join books_prices bp on bp.book_id = sp.book_id\
                  join books_details bd on bd.book_id = sp.book_id\
                  where purchase_date between '";

    string firstDate;
    string secondDate;
    string and = "' and '";
    string end = "';";

    cout << "Enter first date: by this pattern YYYY-MM-DD" << endl;
    cin >> firstDate;

    cout << "Enter second date: by this pattern YYYY-MM-DD" << endl;
    cin >> secondDate;

    if (validDate(firstDate) && validDate(secondDate))
    {
        q22 = q22 + firstDate + and+secondDate + end;
        char *final_query = stringToChar(q22);

        mysql_query(connect, final_query);
        delete final_query;

        res_set = mysql_store_result(connect);

        if (res_set != nullptr && res_set->row_count != 0)
        {
            row = mysql_fetch_row(res_set);
            cout << "The store purchaed " << row[0] << " books, for " << row[1] << "$" << endl;
        }
        else
            cout << "No purchases between " << firstDate << " and " << secondDate << endl;
    }
    else
        cout << "Invalid dates!" << endl;

    system("pause");
}

void MySQL::query_23()
{
    string q23 = "select (sum(amount * customer_price) - (select sum(books_amount * store_price) as total_spend from store_purchases sp\
                  join books_prices bp on bp.book_id = sp.book_id\
                  join books_details bd on bd.book_id = sp.book_id\
                  where purchase_date between '";

    string userMonth;
    string userYear;
    string end = ";";

    cout << "Enter month: [1-12] " << endl;
    cin >> userMonth;
    cout << "Enter year: " << endl;
    cin >> userYear;

    string dates = userYear + "-" + userMonth + "-01' and '" + userYear + "-" + userMonth + "-30'";
    string q23_part2 = ")) as profit from transaction_details td\
                        join books_prices bp on bp.book_id = td.book_id\
                        join books_details bd on bd.book_id = td.book_id\
                        join transactions t on t.transaction_id = td.transaction_id\
                        where transaction_date between '";

    q23 = q23 + dates + q23_part2 + dates + end;
    char *final_query = stringToChar(q23);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        row = mysql_fetch_row(res_set);
        if (*row != nullptr)
            cout << "Profit in month " << userMonth << " is " << row[0] << "$" << endl;
        else
            cout << "No store transfers in month " << userMonth << endl;
    }
    system("pause");
}

void MySQL::query_24()
{
    string q24 = "select month(transaction_date) as _month, avg(amount*customer_price)\
                  from transaction_details td\
                  join transactions t on td.transaction_id = t.transaction_id\
                  join books_prices bp on td.book_id = bp.book_id\
                  group by _month order by _month; ";

    char *final_query = stringToChar(q24);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        cout << "month\t\t"
             << "average\t" << endl;
        while (((row = mysql_fetch_row(res_set)) != NULL))
            cout << row[0] << "\t\t" << row[1] << endl;
    }
    else
        cout << "Error loading data" << endl;
    system("pause");
}

void MySQL::query_25()
{
    string q25 = "select concat(employee_first_name, ' ',employee_last_name) as full_name, hours_monthly, es.month, es.year, (hours_monthly * 35) as salary\
                  from employees_salary es\
                  join employees_details ed on ed.employee_id = es.employee_id\
                  where employee_first_name = '";
    string fname;
    string lname;
    string userMonth;
    string userYear;

    cout << "Enter employee first name:" << endl;
    cin >> fname;
    cout << "Enter employee last name:" << endl;
    cin >> lname;
    cout << "Enter month: [1-12]" << endl;
    cin >> userMonth;
    cout << "Enter year:" << endl;
    cin >> userYear;

    q25 = q25 + fname + "' and employee_last_name = '" + lname + "' and month = " + userMonth + " and year = " + userYear + ";";

    char *final_query = stringToChar(q25);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        row = mysql_fetch_row(res_set);
        cout << "The employee '" << fname << " " << lname << "' worked on " << userMonth << "/" << userYear << " for " << row[1] << " hours, and his salary was "
             << row[4] << "$" << endl;
    }
    else
        cout << "No salary for employee " << fname << " " << lname << " on given time" << endl;
    system("pause");
}

void MySQL::query_26()
{
    string q26 = "select e.employee_id, employee_first_name, employee_last_name, count(transaction_id) as _sum\
                  from employees_details e\
                  join transactions t on t.employee_id = e.employee_id\
                  where month(transaction_date) = ";

    string rest = " group by(e.employee_id) order by _sum desc limit 1; ";
    string userMonth;
    cout << "Enter month: [1-12]" << endl;
    cin >> userMonth;

    q26 = q26 + userMonth + rest;
    char *final_query = stringToChar(q26);

    mysql_query(connect, final_query);
    delete final_query;

    res_set = mysql_store_result(connect);

    if (res_set != nullptr && res_set->row_count != 0)
    {
        row = mysql_fetch_row(res_set);
        cout << "The employee '" << row[1] << " " << row[2] << "' is the best seller! he made " << row[3] << " transactions on month No. " << userMonth << endl;
        cout << "Well Done!" << endl;
    }
    else
        cout << "No best seller on month No. " << userMonth << endl;
    system("pause");
}