### Postgres ###


http://www.teampostgresql.com/

Tutorial : https://www.digitalocean.com/community/tutorials/how-to-create-remove-manage-tables-in-postgresql-on-a-cloud-server

Installation :
```sh
apt-get install postgresql postgresql-client postgresql-server-dev-9.4  
```

Accès :
```sh
sudo -u postgres psql postgres  
psql bigdata
psql postgres
```

Création utilisateur :
```sh
postgres=# CREATE ROLE julie UNENCRYPTED PASSWORD 'julie' LOGIN SUPERUSER CREATEDB CREATEROLE;  
```

Liste des utilisateurs :
```sh
postgres=# \du  
```
Supprimer un utilisateur :
```sh
postgres=# DROP ROLE username;  
```

Quitter :
```sh
postgres=# \q  
```

Liste des tables :
```sh
postgres=# \l  
```

Création base :
```sh
postgres=# CREATE DATABASE bigdata;  
```

Connexion base :
```sh
postgres=# \c bigdata  
```
Création table :  
```sh
postgres=# CREATE TABLE table_name (...);  
```
Liste des colonnes d'une table :
```sh
postgres=# \d+ table_name  
```

Accès pour l'exterieur, modifier :

> gedit /etc/postgresql/9.4/main/pg_hba.conf
> gedit /etc/postgresql/9.4/main/postgresql.conf
