# FdF - Fil de Fer

**Visualiseur 3D de cartes d'altitudes**  
École 42 - Par nistanoj

---

## 📖 Description

FdF (Fil de Fer) est un programme de visualisation 3D qui transforme des cartes d'altitudes en modèles wireframe interactifs.

Le projet lit un fichier `.fdf` contenant une grille de coordonnées Z (altitudes) et les affiche en 3D avec :
- Plusieurs types de projections (isométrique, parallèle, conique)
- Gestion des couleurs (format hexadécimal ou dégradés automatiques)
- Contrôles interactifs (zoom, rotation, translation)

**Exemple :**
```
Fichier .fdf :          Rendu 3D :
0  0  1  2  3            ╱╲╱╲╱╲
0  1  2  3  2           ╱  ╲  ╲
1  2  3  2  1          ╱    ╲  ╲
                      ╱______╲__╲
```

---

## 🚀 Utilisation

```bash
gcl https://github.com/42paris/minilibx-linux.git
cd minilibx-linux && chmod +x configure && ./configure
cd ..
make
./fdf maps/42.fdf
```

Le programme affiche la carte en 3D avec un HUD montrant les contrôles et paramètres.

---

## 🎮 Contrôles

| Touche | Action |
|--------|--------|
| **ESC** | Quitter |
| **↑ ↓ ← →** | Déplacer la vue |
| **+ / -** ou **Molette** | Zoom / Dézoom |
| **P** | Changer de projection (Iso / Parallèle / Conique) |
| **W A S D** | Rotation X et Y |
| **Q / E** | Rotation Z |
| **Shift / Ctrl** | Modifier l'échelle Z (relief) |
| **R** | Activer/Désactiver rotation automatique |
| **C** | Changer de mode couleur (Auto / Custom) |
| **Espace** | Reset vue

---

## 📦 Format des fichiers .fdf

Les fichiers `.fdf` contiennent une grille d'altitudes (coordonnées Z) :

```
0  0  1  2  3
0  1  2  3  2
1  2  3  2  1
```

- Chaque nombre = altitude d'un point
- Format optionnel avec couleur : `10,0xFF0000` (altitude 10, couleur rouge)
- Les espaces séparent les colonnes
- Les retours à la ligne séparent les lignes

**Exemples de maps :**
- `maps/42.fdf` - Logo 42
- `maps/julia.fdf` - Fractale de Julia (avec couleurs)
- `maps/pyramide.fdf` - Pyramide simple
- `maps/mars.fdf` - Relief martien

---

## 🛠️ Compilation

```bash
make        # Compile le projet
make clean  # Supprime les fichiers objets
make fclean # Supprime tout (objets + exécutable)
make re     # Recompile tout
```

**Norminette :** ✅ Le projet respecte la norme 42

---

## 📚 Technologies

- **Langage** : C
- **Librairie graphique** : MiniLibX
- **Algorithmes** : Bresenham (lignes), transformations 3D (matrices de rotation/projection)
- **Parsing** : Lecture de fichiers avec `get_next_line`

---

## 📝 Notes

Le projet gère :
- ✅ Les grandes maps (jusqu'à 10 000+ points)
- ✅ Les couleurs hexadécimales (parsing corrigé pour `0x...`)
- ✅ Les dégradés automatiques de couleurs
- ✅ Le centrage automatique des maps
- ✅ L'affichage fluide avec HUD

---

**Fait avec ❤️ à l'École 42**
