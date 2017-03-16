### Postgres ###


http://www.teampostgresql.com/

Tutorial : https://www.digitalocean.com/community/tutorials/how-to-create-remove-manage-tables-in-postgresql-on-a-cloud-server

Installation :
apt-get install postgresql postgresql-client postgresql-server-dev-9.4  

Accès :
sudo -u postgres psql postgres  
psql bigdata
psql postgres

Création utilisateur :
postgres=# CREATE ROLE julie UNENCRYPTED PASSWORD 'julie' LOGIN SUPERUSER CREATEDB CREATEROLE;  

Liste des utilisateurs :
postgres=# \du  

Supprimer un utilisateur :
postgres=# DROP ROLE username;  

Quitter :
postgres=# \q  

Liste des tables :
postgres=# \l  

Création base :
postgres=# CREATE DATABASE bigdata;  

Connexion base :
postgres=# \c bigdata  

Création table :  
postgres=# CREATE TABLE name (...);  

Liste des colonnes d'une table :
postgres=# \d+ name  

