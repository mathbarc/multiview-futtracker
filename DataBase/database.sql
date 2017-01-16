create database if not exists futtracker;
use futtracker;

drop table if exists escalacao;
drop table if exists players;
drop table if exists games;
drop table if exists teams;


create table players( id int auto_increment primary key,
					  name varchar(150));


create table teams( id int auto_increment primary key,
					name varchar(150));
                    

create table games( id int auto_increment primary key,
					team1 int,
                    team2 int,
                    tsp date,
                    constraint FK_TEAM1 foreign key (team1) references teams(id),
                    constraint FK_TEAM2 foreign key (team2) references teams(id));
                    
create table escalacao( team_id int,
						player_id int,
                        game_id int,
                        numero_camisa int,
                        constraint FK_TEAM foreign key (team_id) references teams(id),
                        constraint FK_PLAYER foreign key (player_id) references players(id),
                        constraint FK_GAME foreign key (game_id) references games(id),
                        constraint PK_ESC primary key (team_id, player_id, game_id));

                    
					