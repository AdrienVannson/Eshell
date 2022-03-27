# ÉShell

ÉShell est un shell proposant quelques fonctionnalités basiques.

## Compilation

Pour compiler le code, utiliser la commande `make` : elle génère l'exécutable `bin/eshell`.
Le sous-dossier `tests` contient des programmes simples permettant de tester le fonctionnement du shell. Ils sont également compilés lors d'un appel à `make`.

## Utilisation

Les commandes à exécuter doivent être tapées après le symbole `╬═╬`, qui représente une échelle (ÉShell). Il est possible de quitter ÉSell avec la commande `exit`. Si le premier caractère d'une ligne est `#`, la ligne est considérée comme un commentaire, et est donc ignorée.

### Processus
La liste des processus en cours d'exécution peut être affichée avec `ps`.
Un signal peut être envoyé à un processus avec la commande `kill`. Elle s'utilise de la manière suivante : `kill signal pid`, où `signal` est l'un des signaux `SIGINT`, `SIGTSTP` et `SIGCONT`.

### Environnement
Une variable d'environnement peut être affichée avec `echo $VAR`. Par exemple, `echo $PATH` affiche la valeur de la variable d'environnement `PATH`. L'environnement complet peut être affiché avec la commande `env`.

## Exemple

Les fonctionnalités d'ÉShell peuvent être testées à l'aide des commandes ci-dessous :

```bash
# Exécution de programmes
# Count doit être interrompu avec Ctrl+C
./bin/hello
./bin/count

# Gestion de l'environnement
echo $PATH
ls
export PATH=/bin/
ls

# Ajout d'une variable à l'environnement
env
export MY_VAR=test
env

# Fermeture du programme
exit
```
