create database if not exists futtracker;
use futtracker;

drop table if exists players;
drop table if exists games;
drop table if exists teams;


create table players( id int auto_increment primary key,
					  name varchar(150),
                      shirtNumber int);


create table teams( id int auto_increment primary key,
					name varchar(150));
                    

create table games( id int auto_increment primary key,
					team1 int,
                    team2 int,
                    tsp date,
                    constraint FK_TEAM1 foreign key (team1) references teams(id),
                    constraint FK_TEAM2 foreign key (team2) references teams(id));

                    
					