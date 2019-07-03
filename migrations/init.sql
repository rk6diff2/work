DROP ROLE IF EXISTS miles;
CREATE DATABASE IF NOT EXISTS miles_program;
CREATE USER'miles'@'localhost' IDENTIFIED BY 'admin';

USE miles_program;
ALTER TABLE ticket DROP FOREIGN KEY detail_id_fk;
# ALTER TABLE ticket DROP FOREIGN KEY detail_id;
DROP TABLE IF EXISTS detail;
DROP TABLE IF EXISTS ticket;
DROP TABLE IF EXISTS profile;

CREATE TABLE IF NOT EXISTS profile
(
    uid       INT                           NOT NULL AUTO_INCREMENT PRIMARY KEY,
    full_name VARCHAR(256)                  NOT NULL,
    birthday  DATE                          NOT NULL,
    miles     INT                           NOT NULL DEFAULT 0
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS ticket
(
    uid         INT                         NOT NULL AUTO_INCREMENT PRIMARY KEY,
    flight      INT                         NOT NULL,
    dep_airport VARCHAR(256)                NOT NULL CHECK ( dep_airport <> '' ),
    arr_airport VARCHAR(256)                NOT NULL CHECK ( arr_airport <> '' ),
    dep_date    TIMESTAMP                   NOT NULL DEFAULT current_timestamp,
    class       INT                         NOT NULL DEFAULT 4,
    detail_id   INT                  UNIQUE NOT NULL

#     FOREIGN KEY (detail_id) REFERENCES detail (uid)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS detail
(
    uid         INT                         NOT NULL AUTO_INCREMENT PRIMARY KEY,
    profile_id  INT                         NOT NULL,
    ticket_id   INT                         NOT NULL,
    price       INT                         NOT NULL DEFAULT 0,
    buy_date    TIMESTAMP                   NOT NULL DEFAULT current_timestamp,
    miles       INT                         NOT NULL DEFAULT 0,

    FOREIGN KEY (profile_id) REFERENCES profile (uid),
    FOREIGN KEY (ticket_id)  REFERENCES ticket  (uid)
) ENGINE=InnoDB;

ALTER TABLE ticket ADD CONSTRAINT detail_id_fk FOREIGN KEY (detail_id) REFERENCES detail (uid) ON DELETE NO ACTION;

GRANT ALL   PRIVILEGES ON miles_program.* TO 'root'@'localhost';
GRANT ALL   PRIVILEGES ON miles_program.* TO 'miles'@'localhost';
FLUSH PRIVILEGES;
