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
gcl https://github.com/NikoStano/FdF.git
cd FdF
make mlx
./fdf maps/42.fdf
```

Le programme affiche la carte en 3D avec un HUD montrant les contrôles et paramètres en temps réel.

---

## 🎮 Contrôles

### Déplacement et Vue
| Touche | Action |
|--------|--------|
| **ESC** | Quitter |
| **↑ ↓ ← →** ou **W A S D** | Déplacer la vue |
| **+ / -** ou **Molette** | Zoom / Dézoom |
| **Shift / Ctrl** | Modifier l'échelle Z (relief) |

### Rotation
| Touche | Action |
|--------|--------|
| **I / K** | Rotation X (haut / bas) |
| **J / L** | Rotation Y (gauche / droite) |
| **Q / E** | Rotation Z (sens horaire / anti-horaire) |
| **Espace** | Activer/Désactiver rotation automatique |

### Options
| Touche | Action |
|--------|--------|
| **P** | Changer de projection (Isométrique / Parallèle / Conique) |
| **C** | Changer de mode couleur (Auto / Gradient) |
| **R** | Reset vue (retour à la position initiale) |

> 💡 **Astuce :** Les touches peuvent être maintenues pour une action continue !  
> Le HUD affiche en temps réel les touches pressées en **vert**.

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
- ✅ L'affichage fluide avec HUD interactif
- ✅ **Nouveau** : Affichage en temps réel des touches pressées (HUD dynamique)
- ✅ **Nouveau** : Actions continues lors du maintien des touches
- ✅ **Nouveau** : Contrôle précis de la vitesse (throttling à 20 FPS pour les inputs)

### Fonctionnalités avancées
- **HUD dynamique** : Affiche les paramètres actuels (projection, angles, échelle) et les touches pressées en vert
- **Rotation automatique** : Mode démo qui fait tourner la carte automatiquement
- **3 modes de projection** : Isométrique (défaut), Parallèle, Conique
- **2 modes de couleur** : Auto (basé sur l'altitude) ou Gradient personnalisé

---

**Fait avec ❤️ à l'École 42**
