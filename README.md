## Initialisation des données :
Le programme prend des arguments en ligne de commande pour définir les paramètres du problème, tels que le nombre de philosophes, le temps pour manger, le temps pour dormir, etc.
Les données sont initialisées à l'aide de la fonction parse_input et stockées dans une structure t_table, qui représente la table à laquelle les philosophes dînent.


## Initialisation des philosophes et des fourchettes :
Les philosophes et les fourchettes sont initialisés à l'aide de la fonction data_init. Chaque philosophe est associé à deux fourchettes voisines sur la table.


## Lancement de la simulation :
La fonction dinner_start est appelée pour lancer la simulation.
Si le nombre de philosophes est égal à 1, un philosophe particulier est géré de manière isolée dans la fonction lone_philo. Sinon, chaque philosophe est géré dans la fonction dinner_simulation.
Un moniteur (dinner_monitor) est également créé pour surveiller l'état des philosophes.


## Boucle de simulation :
Chaque philosophe commence par penser (thinking), puis tente de prendre deux fourchettes adjacentes pour manger (eat).
Pendant qu'ils mangent, dorment ou pensent, leurs actions sont affichées à l'écran à l'aide de la fonction write_status.
Le programme continue à s'exécuter jusqu'à ce qu'un philosophe ait atteint le nombre maximal de repas (nbr_limit_meals), ou si un philosophe meurt.


## Gestion des erreurs et nettoyage :
Le programme gère les erreurs à l'aide de fonctions telles que safe_thread, safe_mutex, et safe_malloc.
Les ressources sont libérées et les mutex sont détruits à la fin de la simulation à l'aide de la fonction clean.
