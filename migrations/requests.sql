SELECT * FROM catalog c JOIN product p ON (p.id = c.item_id) WHERE YEAR(enter_date) = 2013 AND MONTH(enter_date) = 3;

SELECT * FROM order_t WHERE DATEDIFF(current_timestamp(), o_date) <= 30;

SELECT status, COUNT(id) FROM order_t WHERE DATEDIFF(current_timestamp(), o_date) <= 5 GROUP BY status;

SELECT category, COUNT(p.id) FROM catalog JOIN product p ON (item_id = p.id) GROUP BY category;

SELECT cust_code, SUM(common_cost) FROM order_t WHERE status <> 2 GROUP BY cust_code;
-- либо тут этот запрос, если отмененные заказы не считаются
-- SELECT cust_code, SUM(common_cost) FROM order_t WHERE status = 1 GROUP BY cust_code;

SELECT cust_code, MIN(`sum`) FROM payment JOIN order_t o ON (order_id = o.id) WHERE YEAR(p_date) = 2013  GROUP BY cust_code;