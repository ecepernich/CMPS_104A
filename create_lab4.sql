DROP SCHEMA lab4 CASCADE;
CREATE SCHEMA lab4;

CREATE TABLE lab4.Stores
( store_id INT PRIMARY KEY,
  name CHAR(20),
  address VARCHAR(50),
  manager CHAR(20));

CREATE TABLE lab4.Customers
( customer_id INT PRIMARY KEY,
  name CHAR(20),
  address VARCHAR(50),
  email CHAR(20));

CREATE TABLE lab4.Products
( product_id INT PRIMARY KEY,
  name CHAR(20),
  category CHAR(20),
  manufacturer CHAR(20));

CREATE TABLE lab4.Sales
( store_id INT,
  customer_id INT,
  product_id INT,
  purchase_date DATE,
  quantity INT,
  unit_price DECIMAL(6,2),
  shipped BOOLEAN,
  PRIMARY KEY(store_id, customer_id, product_id, purchase_date) );

CREATE TABLE lab4.NewSales
( store_id INT,
  customer_id INT,
  product_id INT,
  purchase_date DATE,
  quantity INT,
  unit_price DECIMAL(6,2),
  PRIMARY KEY(store_id, customer_id, product_id, purchase_date) );
  