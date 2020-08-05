-- 1
select (warehouse_inventory + store_inventory) as in_stock from books_details bd  
left join inventory i on i.book_id = bd.book_id  
where bd.title = "The Doom";

-- 2
select customer_first_name, customer_last_name, MIN(transaction_date) as 'date' from transactions t
left join transaction_details td on td.transaction_id = t.transaction_id   
left join customers c on c.customer_id = t.customer_id   
left join books_details bd on bd.book_id = td.book_id;

-- 3
select title from
	(select transaction_date, bd.book_id, title from
		(select transaction_date, td.book_id  from transactions t       
		left join transaction_details td on td.transaction_id = t.transaction_id        
		group by transaction_date order by transaction_date desc) PURCHASE   
	left join books_details bd ON bd.book_id = PURCHASE.book_id    
group by bd.book_id) as allbks order by transaction_date asc limit 1;

-- 4
select order_id, customer_id, order_date, payment_method_name, shipping_type_name from orders o
join payment_method pm on pm.payment_method_id = o.payment_method
join shipping_types st on st.shipping_type_id = o.shipping_method
where shipping_status != 'Collected' 
order by order_date;

-- 5
select sum(amount) as num_of_copys from transactions t 
right join  transaction_details td on td.transaction_id = t.transaction_id  
right join books_details bd on bd.book_id = td.book_id 
where title = "Don Quixote";

-- 6
select author_name from
(select td.transaction_id, book_id, amount from transactions t  
left join transaction_details td on td.transaction_id = t.transaction_id  
where transaction_date between '2012-11-01' and '2020-01-01') times_of_transactions   
left join books_details on books_details.book_id = times_of_transactions.book_id  
left join authors a on a.book_id = books_details.book_id 
group by author_name order by amount desc limit 1;

-- 7
select customer_first_name, customer_last_name, SUM(amount) as total, customers.customer_id from
(select transaction_details.transaction_id, book_id, amount, customer_id from transactions t
left join transaction_details on transaction_details.transaction_id = t.transaction_id) as sold_bet   
left join customers on customers.customer_id = sold_bet.customer_id      
group by customer_id order by total desc limit 3;

-- 8
select bd.title from books_details bd 
join books_details s_bd on  bd.title = s_bd.title 
where bd.interpreter != s_bd.interpreter 
group by title order by count(bd.interpreter) desc LIMIT 1;

-- 9
select concat(customer_first_name, ' ' ,customer_last_name)as full_name, transaction_date, title, amount, customer_price, (customer_price * amount) as total from transactions t 
join customers c on t.customer_id = c.customer_id 
join transaction_details td on t.transaction_id = td.transaction_id 
join books_details bd on bd.book_id = td.book_id 
join books_prices bp on bp.book_id = td.book_id 
where customer_first_name = 'Shay' and customer_last_name = 'Loren' order by transaction_date;

-- 10
select concat(customer_first_name, ' ', customer_last_name) as full_name, order_date, title, total_amount, customer_price, (total_amount*customer_price) as total from orders o
join customers c on o.customer_id = c.customer_id  
join order_details od on o.order_id = od.order_id 
join books_details bd on bd.book_id = od.book_id 
join books_prices bp on bp.book_id = od.book_id 
where customer_first_name = 'Harel' and customer_last_name = 'Toms' order by order_date;

-- 11
select sum(total_amount*weight) as total_weight , shipping_type_price, shipping_type_name, ( sum(total_amount*weight) * 3 + shipping_type_price) as total_price, sum(total_amount*weight) * 3 from books_details bd
join order_details od on od.book_id = bd.book_id
join orders o on o.order_id = od.order_id
join shipping_types st on st.shipping_type_id = o.shipping_method
where o.order_id = 12;

-- 12
select concat(customer_first_name, ' ', customer_last_name) as full_name, o.order_id, o.order_date, title, total_amount, o.shipping_status, payment_method_name, shipping_type_name from orders a, orders o
join customers c on o.customer_id = c.customer_id 
join order_details od on o.order_id = od.order_id
join shipping_types st on o.shipping_method = st.shipping_type_id  
join second_hand_books.payment_method pm on o.payment_method = pm.payment_method_id
join books_details bd on bd.book_id = od.book_id 
where customer_first_name = 'Idan' and customer_last_name = 'Gur' and o.order_date = a.order_date and o.order_id != a.order_id;

-- 13
select o.order_id, concat(customer_first_name, ' ', customer_last_name) as full_name, o.order_date, shipping_type_name, shipping_status from orders o
join customers c on o.customer_id = c.customer_id 
join order_details od on o.order_id = od.order_id
join shipping_types st on o.shipping_method = st.shipping_type_id  
where o.order_id = 10;

-- 14
select count(order_id) as total_shipping_by_Xpress from orders o
where (shipping_method between 4 and 5) and (month(order_date) = 8);

-- 15
select transaction_date, t.transaction_id , sum(customer_price * amount) as total_by_bit from transaction_details td
join books_prices bp on td.book_id = bp.book_id
join transactions t on t.transaction_id = td.transaction_id
where (payment_method = 1) and (month(transaction_date) = 6);

-- 16
select td.transaction_id, transaction_date, (amount * customer_price) as income from transaction_details td
join books_prices bp on td.book_id = bp.book_id
join transactions t on t.transaction_id = td.transaction_id
where (amount * customer_price) > (
		select avg(amount * customer_price) as _avg from transaction_details td
		join books_prices bp on td.book_id = bp.book_id
		join transactions t on t.transaction_id = td.transaction_id
		where transaction_date between date_sub(now(), interval 12 month) and now()) 
and (transaction_date between date_sub(now(), interval 12 month) and now());

-- 17
select sum(shipping_method between 4 and 5) as total_orders_Xpress,
       sum(shipping_method between 1 and 3) as total_orders_IRpost from orders
where (order_date between date_sub(now(), interval 12 month) and now());
-- shipping_method between 4 and 5 -> Xpress
-- shipping_method between 1 and 3 -> Israel Post

-- 18
select distinct bd.publisher, oo.order_id, bd.title, o.order_date, o.customer_id 
from books_details bd
right join order_details od on od.book_id = bd.book_id 
right join orders o on o.order_id = od.order_id  
right join orders oo on oo.order_date = o.order_date and (oo.order_id = o.order_id)
right join books_details bdd on bdd.publisher != bd.publisher and bd.book_id != bdd.book_id and bd.publishing_year = bdd.publishing_year
where bd.title = bdd.title and  o.order_id = od.order_id and o.order_id = oo.order_id and bdd.publisher != bd.publisher 
and o.order_id = 13 order by o.order_id;

-- 19
select c.customer_id, concat(customer_first_name, ' ',customer_last_name) as full_name, transaction_date from customers c
join transactions t on t.customer_id = c.customer_id
where transaction_date not between date_sub(now(), interval 24 month) and now()
group by customer_id;

-- 20
select concat(customer_first_name, ' ', customer_last_name) as full_name, order_date from customers c
join orders o on o.customer_id = c.customer_id
where shipping_status = 'Pendding' and order_status = 'Contacted client 14 days ago or more'
order by order_date;

-- 21
select (sum(warehouse_inventory) - books_sold) as in_stock from inventory i -- will run in loop for 12 times
	join (select sum(total_amount) as books_sold from order_details od
    left join orders o on od.order_id = o.order_id
    where month(order_date) = 12 and year(order_date) = 2019) as p;

-- 22
select sum(books_amount) as books_amount, sum(books_amount * store_price) as total_spend from store_purchases sp -- total books the store purchased in given date range
join books_prices bp on bp.book_id = sp.book_id
join books_details bd on bd.book_id = sp.book_id
where purchase_date between '2019-01-01' and '2019-12-30';

-- 23
select (sum(amount * customer_price) - (select sum(books_amount * store_price) as total_spend from store_purchases sp -- total books the store purchased in given date range
join books_prices bp on bp.book_id = sp.book_id
join books_details bd on bd.book_id = sp.book_id
where purchase_date between '2020-05-01' and '2020-05-30')) as profit from transaction_details td -- total books sold in given date range
join books_prices bp on bp.book_id = td.book_id
join books_details bd on bd.book_id = td.book_id
join transactions t on t.transaction_id = td.transaction_id
where transaction_date between '2020-05-01' and '2020-05-30';

-- 24
select month(transaction_date) as _month, avg(amount*customer_price) from transaction_details td
join transactions t on td.transaction_id = t.transaction_id
join books_prices bp on td.book_id = bp.book_id
group by _month order by _month;

-- 25
select concat(employee_first_name, ' ',employee_last_name) as full_name, hours_monthly, es.month, es.year, (hours_monthly * 35) as salary from employees_salary es
join employees_details ed on ed.employee_id = es.employee_id
where employee_first_name = 'Amit' and employee_last_name = 'David' and month = 7 and year = 2020;

-- 26
select e.employee_id, employee_first_name, employee_last_name, count(transaction_id) as _sum from employees_details e
join transactions t on t.employee_id = e.employee_id
where month(transaction_date) = 2  -- from user
group by(e.employee_id) order by _sum desc limit 1;

