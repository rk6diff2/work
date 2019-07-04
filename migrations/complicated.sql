-- 1
SELECT t.flight, t.dep_date, SUM(d.miles) FROM ticket AS t
    JOIN detail AS d ON (t.uid = d.ticket_id) GROUP BY t.flight, t.dep_date;
-- 2
SELECT dep_airport, MONTH(dep_date), class, COUNT(*) FROM ticket
    WHERE YEAR(dep_date) = 2014 GROUP BY dep_airport, MONTH(dep_date), class;
-- 3 XXX = 10
SELECT p.* FROM profile AS p WHERE p.uid IN (
    SELECT profile_id FROM detail d JOIN ticket t ON (d.ticket_id = t.uid) WHERE t.flight = 10 AND d.price = (
    SELECT MAX(d.price) FROM detail AS d JOIN ticket AS t ON (d.ticket_id = t.uid) WHERE t.flight = 10));
-- 4
SELECT p.* FROM profile AS p LEFT JOIN detail AS d ON (p.uid = d.profile_id) WHERE d.profile_id IS NULL;

-- 5
SELECT p.* FROM profile AS p WHERE uid NOT IN (
    SELECT profile_id FROM detail AS d WHERE YEAR(d.buy_date) = 2014 AND MONTH(d.buy_date) = 3);
-- 6
CREATE OR REPLACE VIEW often_pas AS
    SELECT p.uid, COUNT(*) as num FROM profile AS p JOIN detail AS d ON (p.uid = d.profile_id)
    WHERE YEAR(d.buy_date) = 2013 AND MONTH(d.buy_date) BETWEEN 3 AND 4 GROUP BY p.uid;

SELECT p.* FROM profile AS p WHERE p.uid IN (
    SELECT uid FROM often_pas WHERE num = ( SELECT MAX(num) FROM often_pas ));
