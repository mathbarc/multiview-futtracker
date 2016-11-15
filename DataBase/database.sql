create database if not exists futtracker;

drop table if exists players;
create table players( name varchar(150),
                      shirtNumber int,
                      id int);