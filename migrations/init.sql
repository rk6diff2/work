DROP TABLE IF EXISTS payment;
DROP TABLE IF EXISTS order_t;
DROP TABLE IF EXISTS catalog;
DROP TABLE IF EXISTS product;
DROP TABLE IF EXISTS document;

DROP ROLE IF EXISTS stock;

CREATE DATABASE IF NOT EXISTS stock;
CREATE USER IF NOT EXISTS 'stock'@'localhost' IDENTIFIED BY 'admin';

USE stock;

CREATE TABLE IF NOT EXISTS product
(
    id        INT                           NOT NULL AUTO_INCREMENT PRIMARY KEY,
    code      VARCHAR(32)            UNIQUE NOT NULL,
    category  VARCHAR(32)                   NOT NULL DEFAULT 'unsorted',
    name      VARCHAR(32)                   NOT NULL CHECK ( name <> '' ),
    material  VARCHAR(32)                            DEFAULT NULL,
    unit      VARCHAR(8)                    NOT NULL DEFAULT 'm'
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS document
(
    doc_num     INT                  UNIQUE NOT NULL AUTO_INCREMENT PRIMARY KEY,
    created     TIMESTAMP                   NOT NULL DEFAULT current_timestamp
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS order_t
(
    id          INT                         NOT NULL AUTO_INCREMENT PRIMARY KEY,
    cust_code   VARCHAR(64)                 NOT NULL,
    status      SMALLINT                    NOT NULL DEFAULT 1,
    o_date      TIMESTAMP                   NOT NULL DEFAULT current_timestamp,
    item_num    BIGINT                      NOT NULL DEFAULT 0,
    common_cost BIGINT                      NOT NULL DEFAULT 0,
    item_id     INT                         NOT NULL,

    FOREIGN KEY (item_id)   REFERENCES product (id)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS catalog
(
    id           INT                  UNIQUE NOT NULL AUTO_INCREMENT PRIMARY KEY,
    item_id      INT                         NOT NULL,
    item_cost    INT                         NOT NULL,
    enter_date   TIMESTAMP                   NOT NULL DEFAULT current_timestamp,
    num_fix_date TIMESTAMP                   NOT NULL DEFAULT current_timestamp,
    num_in_stock BIGINT                      NOT NULL DEFAULT 0,
    res_fix_date TIMESTAMP                   NOT NULL DEFAULT current_timestamp,
    num_in_res   BIGINT                      NOT NULL DEFAULT 0,

    FOREIGN KEY (item_id) REFERENCES product (id)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS payment
(
    id           INT                  UNIQUE NOT NULL AUTO_INCREMENT PRIMARY KEY,
    order_id     INT                  UNIQUE NOT NULL,
    sum          BIGINT                      NOT NULL DEFAULT 0,
    p_date       TIMESTAMP                   NOT NULL DEFAULT current_timestamp,
    doc_num      INT                         NOT NULL DEFAULT 0,
#     cust_code    VARCHAR(64)                 NOT NULL,

    FOREIGN KEY (order_id)  REFERENCES order_t (id),
#     FOREIGN KEY (cust_code) REFERENCES order_t (cust_code),
    FOREIGN KEY (doc_num)   REFERENCES document (doc_num)
) ENGINE=InnoDB;

-- CREATE OR REPLACE VIEW spring_flight AS
--  SELECT MAX(num) FROM
--     (
--         SELECT COUNT(*) AS num FROM ticket t
--                                         JOIN flight f ON (f.uid = t.flight_id)
--         WHERE YEAR(f.dep_date) = 2013 AND MONTH(f.dep_date) BETWEEN 3 AND 4
--         GROUP BY t.user_id
--     ) subquery;

GRANT ALL   PRIVILEGES ON stock.* TO 'root'@'localhost';
GRANT ALL   PRIVILEGES ON stock.* TO 'stock'@'localhost';
FLUSH PRIVILEGES;
