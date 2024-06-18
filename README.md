<h1 align="center">Cub3D</h1>

Septième projet de [42](https://42.fr/) et deuxième projet graphique qui utilise la [MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx).

Implémentation du raycasting afin de réaliser un moteur graphique semblable au jeu Wolfeinstein3D.

Le but du joueur est de se déplacer dans un dédale de salles sans objectif précis.

---

### Compilation :

Pour compiler le projet, exécutez la commande suivante :

```
make
```


### Utilisation :

Pour lancer le jeu, `./cub3d` `adresse de la carte`

Exemple :

```
./cub3 ./maps/map.cub
```


### Commandes :

| Clavier | Action |
|---|---|
| <kbd>W</kbd>, <kbd>↑</kbd>| Avancer |
| <kbd>S</kbd>, <kbd>↓</kbd>| Reculer |
| <kbd>A</kbd> | Déplacement à gauche |
| <kbd>D</kbd> | Déplacement à droite |
| <kbd>←</kbd> | Tourner la caméra à gauche |
| <kbd>→</kbd> | Tourner la caméra à droite |
| <kbd>ESC</kbd>, `⎋`| Fermer le jeu |
---
### Structuration de la carte :

| Caractère | Description|
|--|--|
| `0` | Espace vide |
| `1` | Mur |
| `N` | Joueur |

##### Exemple de carte :

```txt
111111
100101
101001
1100N1
111111
```

### Démonstration :

<img src="./img/demo1.gif" />

---

### Correction :

| |
| --- |
| <img src="./img/note.png" style="zoom: 50%;" /> |

| | |
| --- | --- |
| Correcteur 1 | <img src="./img/correction1.png" style="zoom: 67%;" /> |
| Correcteur 2 | <img src="./img/correction2.png" style="zoom:67%;" /> |
