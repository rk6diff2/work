-- 1
SELECT * FROM details JOIN ticket ON (ticket_id = uid) WHERE YEAR(buy_date) = 2013 AND MONTH(buy_date) = 3;
-- 2
SELECT * FROM details JOIN ticket ON (ticket_id = uid) WHERE DATEDIFF(current_timestamp(), buy_date) <= 60;
-- 3
SELECT SUM(price) FROM detail WHERE YEAR(buy_date) = 2013 AND MONTH(buy_date) = 3;
-- 4
SELECT MAX(miles) FROM profile;
-- 5
SELECT flight, class, COUNT(*) FROM details JOIN ticket ON (ticket_id = uid) WHERE YEAR(buy_date) = 2014 GROUP BY flight, class;
-- 6
SELECT full_name, COUNT(*) FROM profile JOIN details ON (uid = profile_id) WHERE YEAR(buy_date) = 2014 GROUP BY full_name;