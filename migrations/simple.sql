-- 1
SELECT * FROM detail d JOIN ticket t ON (d.ticket_id = t.uid) WHERE YEAR(d.buy_date) = 2013 AND MONTH(d.buy_date) = 3;
-- 2
SELECT * FROM detail d JOIN ticket t ON (d.ticket_id = t.uid) WHERE DATEDIFF(current_timestamp(), d.buy_date) <= 60;
-- 3
SELECT SUM(price) FROM detail WHERE YEAR(buy_date) = 2013 AND MONTH(buy_date) = 3;
-- 4
SELECT MAX(miles) FROM profile;
-- 5
SELECT t.flight, t.class, COUNT(*) FROM detail d JOIN ticket t ON (d.ticket_id = t.uid) WHERE YEAR(d.buy_date) = 2014 GROUP BY t.flight, t.class;
-- 6
SELECT p.full_name, COUNT(*) FROM profile p JOIN detail d ON (p.uid = d.profile_id) WHERE YEAR(d.buy_date) = 2014 GROUP BY p.full_name;