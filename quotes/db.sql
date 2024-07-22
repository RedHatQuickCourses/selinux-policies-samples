-- Based on quotes from: https://www.freshworks.com/freshservice/general/top-it-quotes-blog/
-- run as: # mysql < db.sql
create database if not exists quotesdb;
create user 'quotesapp'@'%' identified by 'app-password';
grant all on quotesdb.* to 'quotesapp'@'%';
use quotesdb;
create table if not exists famousquotes (id integer primary key, quote varchar(200));
truncate table famousquotes;
insert into famousquotes values (1, 'The only constant in the technology industry is change.');
insert into famousquotes values (2, 'The 4 Ps for Change and Release: Planning Prevents Poor Performance.');
insert into famousquotes values (3, 'Any sufficiently advanced bug is indistinguishable from a feature.');
insert into famousquotes values (4, 'IT is ever-changing and there is the need to evolve in order to stay relevant.');
insert into famousquotes values (5, 'A Release is like a boat. 80% of the holes plugged is not good enough.');
