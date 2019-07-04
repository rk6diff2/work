DROP PROCEDURE IF EXISTS  update_purse;
DELIMITER $$ ;
CREATE PROCEDURE update_purse ( IN start_date DATE )
BEGIN
    DECLARE ticket_miles   INT           DEFAULT 0 ;
    DECLARE profile_id     INT           DEFAULT 0 ;
    DECLARE done           INT           DEFAULT 0 ;
    DECLARE cur CURSOR FOR
        SELECT d.profile_id, d.miles FROM detail AS d WHERE DATE_FORMAT(d.buy_date, '%Y-%m-%d') = start_date;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;
    OPEN cur;
    WHILE done = 0 DO
        FETCH cur INTO profile_id, ticket_miles;
        UPDATE profile SET miles = miles + ticket_miles WHERE uid = profile_id;
    END WHILE;
END $$
DELIMITER ; $$
