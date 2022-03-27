# ÉShell

ÉShell est un shell proposant quelques fonctionnalités basiques.

## Compilation

Pour compiler le code, utilisez la commande `make` : elle génère l'exécutable `bin/eshell`.
Le sous-dossier `tests` contient des programmes simples permettant de tester le fonctionnement du shell. Ils sont également compilés lors d'un appel à `make`.

## Utilisation

Les commandes à exécuter doivent être tapées après le symbole `╬═╬`, qui représente une échelle (ÉShell). Il est possible de quitter ÉSell avec la commande `exit`. Des arguments peuvent être passés à un programme. Si le premier caractère d'une ligne est `#`, la ligne est considérée comme un commentaire, et est donc ignorée.

### Processus
Si une commande se termine par `&`, le processus est lancé en arrière plan. Il est possible d'exécuter une commande en arrière plan sans qu'elle soit interrompue par la fermeture du shell en la précédant de `nohup`. Le processus en premier plan peut être interrompu avec `Ctrl+C`, et stoppé avec `Ctrl+Z`. La liste des processus en cours d'exécution, c'est-à-dire dont l'état est `running` ou `stopped`, peut être affichée avec `ps`.
Un signal peut être envoyé à un processus avec la commande `kill`. Elle s'utilise de la manière suivante : `kill signal pid`, où `signal` est l'un des signaux `SIGINT`, `SIGTSTP` et `SIGCONT`. Pour remettre en arrière-plan le dernier processus suspendu, il est également possible d'utiliser `bg`.

### Environnement
Une variable d'environnement peut être affichée avec `echo $VAR`. Par exemple, `echo $PATH` affiche la valeur de la variable d'environnement `PATH`. L'environnement complet peut être affiché avec la commande `env`. Pour définir une nouvelle variable d'environnement, on utilise `export MY_VAR=test`.

## Exemple

Certaines fonctionnalités d'ÉShell peuvent être testées à l'aide des commandes ci-dessous :

```bash
# Exécution de programmes
# Count doit être interrompu avec Ctrl+C, et mis en arrière plan avec Ctrl+Z
./bin/hello
./bin/count

# Gestion de l'environnement
ls
export PATH=/usr/bin:/bin
echo $PATH
ls

# Ajout d'une variable à l'environnement
env
export MY_VAR=test
env

# Passage d'arguments
./bin/args arg1 arg2 arg3

# Fermeture du shell
exit
```
