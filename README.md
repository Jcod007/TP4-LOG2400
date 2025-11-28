# MiniDesign - Structure du Projet

## 📁 Organisation des Fichiers

Le projet est organisé selon une architecture modulaire claire :

```
MiniDesign/
├── include/              # Tous les fichiers d'en-tête (.h)
│   ├── commands/         # Patron de commande (Command Pattern)
│   │   ├── Commande.h              # Interface de base
│   │   ├── SupprimerCommand.h      # Commande de suppression
│   │   ├── Commande_A.h
│   │   ├── Commande_O.h
│   │   └── Invocateur.h            # Gestionnaire de commandes
│   │
│   ├── models/           # Modèles de données
│   │   ├── Plan.h                  # Gestionnaire du plan
│   │   ├── GraphElement.h          # Élément graphique de base
│   │   ├── Point.h
│   │   ├── PointBase.h
│   │   └── PointCloud.h            # Nuage de points
│   │
│   ├── factories/        # Patron Factory
│   │   └── PointFactory.h          # Création de points
│   │
│   ├── display/          # Affichage et textures
│   │   ├── Affichage.h
│   │   ├── AffichageAvecTexture.h
│   │   ├── AffichageListe.h
│   │   ├── AffichageOrthese.h
│   │   ├── Texture.h
│   │   ├── Texture_F.h
│   │   ├── Texture_O.h
│   │   └── tpAffichage.h
│   │
│   └── builders/         # Construction de surfaces
│       ├── SurfaceBuilder.h
│       ├── IdOrderSurfaceBuilder.h
│       └── NearestNeighborSurfaceBuilder.h
│
├── src/                  # Tous les fichiers d'implémentation (.cpp)
│   ├── commands/         # Implémentation des commandes
│   ├── models/           # Implémentation des modèles
│   ├── factories/        # Implémentation des factories
│   ├── display/          # Implémentation de l'affichage
│   └── builders/         # Implémentation des builders
│
└── MiniDesign.cpp        # Point d'entrée principal
```

## 🎯 Patrons de Conception Utilisés

### 1. **Command Pattern** (Patron de Commande)
- **Localisation** : `include/commands/` et `src/commands/`
- **But** : Encapsuler les actions utilisateur pour permettre undo/redo
- **Classes principales** :
  - `Commande` : Interface de base
  - `SupprimerCommand` : Suppression d'éléments
  - `Invocateur` : Gestionnaire de l'historique des commandes

### 2. **Factory Pattern** (Patron Fabrique)
- **Localisation** : `include/factories/` et `src/factories/`
- **But** : Création d'objets Point
- **Classe** : `PointFactory`

### 3. **Builder Pattern** (Patron Constructeur)
- **Localisation** : `include/builders/` et `src/builders/`
- **But** : Construction de surfaces complexes
- **Classes** : `SurfaceBuilder`, `IdOrderSurfaceBuilder`, `NearestNeighborSurfaceBuilder`

## 📝 Conventions d'Include

Lors de l'inclusion de fichiers, utilisez les chemins relatifs appropriés :

### Depuis un fichier .h dans include/commands/ :
```cpp
#include "Commande.h"                    // Même dossier
#include "../models/Plan.h"              // Autre module
```

### Depuis un fichier .cpp dans src/commands/ :
```cpp
#include "../../include/commands/SupprimerCommand.h"  // Son header
#include "../../include/models/Plan.h"                // Autres headers
```

## 🔄 Implémentation Undo/Redo

Chaque commande implémente :
- `execute()` : Exécute l'action et sauvegarde l'état pour undo
- `undo()` : Annule l'action en restaurant l'état précédent

L'`Invocateur` gère deux piles :
- **undoStack** : Historique des commandes exécutées
- **redoStack** : Commandes annulées pouvant être refaites

## 🚀 Prochaines Étapes

- [ ] Implémenter `DeplacerCommand`
- [ ] Implémenter `FusionEnNuageCommand`
- [ ] Ajouter le `CommandManager` pour gérer undo/redo
- [ ] Mettre à jour les chemins d'include dans tous les fichiers
