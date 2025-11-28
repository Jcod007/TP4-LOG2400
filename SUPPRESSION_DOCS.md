# 🗑️ Suppression d'Éléments - Documentation

## Comment ça fonctionne

### Comportement de `supprimerGraphElementById(int id)`

Lorsque vous supprimez un élément du Plan, voici ce qui se passe :

```cpp
void Plan::supprimerGraphElementById(int id) {
    // Étape 1 : Retirer de TOUS les PointClouds
    for (auto& element : m_graphElements) {
        if (auto cloud = dynamic_pointer_cast<PointCloud>(element)) {
            if (cloud->containsPoint(id)) {
                cloud->removePointById(id);
            }
        }
    }
    
    // Étape 2 : Retirer du Plan
    auto it = find_if(m_graphElements.begin(), m_graphElements.end(), 
        [id](const shared_ptr<GraphElement>& element) {
            return element->getId() == id;
        });
    
    if (it != m_graphElements.end()) {
        m_graphElements.erase(it);
    }
}
```

---

## 📊 Exemple Concret

### Situation Initiale
```
Plan contient:
  - Point(id=1, x=10, y=20)
  - Point(id=2, x=30, y=40)
  - Point(id=3, x=50, y=60)
  - PointCloud(id=100) contenant [Point(1), Point(2)]
```

### Appel : `plan.supprimerGraphElementById(1)`

**Étape 1** : Recherche dans les PointClouds
- PointCloud(100) contient Point(1) ✅
- Appel : `PointCloud(100).removePointById(1)`
- Résultat : PointCloud(100) contient maintenant [Point(2)]

**Étape 2** : Suppression du Plan
- Point(1) est retiré du vecteur `m_graphElements`

### Résultat Final
```
Plan contient:
  - Point(id=2, x=30, y=40)
  - Point(id=3, x=50, y=60)
  - PointCloud(id=100) contenant [Point(2)]  ← Point(1) retiré !
```

---

## 🔄 Undo/Redo avec SupprimerCommand

### Execute
```cpp
void SupprimerCommand::execute() {
    // 1. Sauvegarder l'élément
    m_backup = m_plan.getGraphElementById(m_id);
    
    // 2. Sauvegarder les IDs des PointClouds affectés
    for (const auto& element : m_plan.getGraphElements()) {
        if (auto cloud = dynamic_pointer_cast<PointCloud>(element)) {
            if (cloud->containsPoint(m_id)) {
                m_affectedCloudIds.push_back(cloud->getId());
            }
        }
    }
    
    // 3. Supprimer
    m_plan.supprimerGraphElementById(m_id);
}
```

**Sauvegarde** :
- `m_backup` = Point(1)
- `m_affectedCloudIds` = [100]

### Undo
```cpp
void SupprimerCommand::undo() {
    // 1. Remettre dans le Plan
    auto elements = m_plan.getGraphElements();
    elements.push_back(m_backup);
    m_plan.setGraphElements(elements);
    
    // 2. Remettre dans les PointClouds affectés
    for (int cloudId : m_affectedCloudIds) {
        auto cloud = m_plan.getGraphElementById(cloudId);
        cloud->addElement(m_backup);
    }
}
```

**Restauration** :
- Point(1) est remis dans le Plan
- Point(1) est remis dans PointCloud(100)

---

## ✅ Avantages de cette Approche

1. **Cohérence** : L'élément est supprimé partout
2. **Undo complet** : Tout est restauré exactement comme avant
3. **Gestion mémoire automatique** : Les `shared_ptr` gèrent tout
4. **Pas de pointeurs pendants** : Les PointClouds ne pointent jamais vers des éléments supprimés

---

## 🎯 Points Importants

### Compteur de Références
```
Avant suppression:
  Point(1) → compteur = 2 (Plan + PointCloud)

Pendant execute():
  Point(1) → compteur = 3 (Plan + PointCloud + m_backup)
  
Après suppression du Plan et PointCloud:
  Point(1) → compteur = 1 (m_backup uniquement)
  ✅ L'objet existe ENCORE pour le undo !

Si la commande est détruite:
  Point(1) → compteur = 0
  ✅ L'objet est automatiquement libéré
```

### Ordre des Opérations
**Important** : On supprime d'abord des PointClouds, PUIS du Plan
- Pourquoi ? Pour éviter que `dynamic_pointer_cast` échoue si l'élément est déjà détruit

---

## 🧪 Test Suggéré

```cpp
// Créer des points
auto p1 = make_shared<Point>(1, 10, 20);
auto p2 = make_shared<Point>(2, 30, 40);

// Créer un plan
Plan plan;
plan.setGraphElements({p1, p2});

// Créer un nuage
auto cloud = make_shared<PointCloud>(vector<shared_ptr<GraphElement>>{p1, p2});
auto elements = plan.getGraphElements();
elements.push_back(cloud);
plan.setGraphElements(elements);

// Créer et exécuter la commande
SupprimerCommand cmd(plan, 1);
cmd.execute();

// Vérifier
cout << "Points dans le plan: " << plan.getGraphElements().size() << endl;  // 2 (p2 + cloud)
cout << "Points dans le nuage: " << cloud->getPoints().size() << endl;      // 1 (p2)

// Undo
cmd.undo();

// Vérifier
cout << "Points dans le plan: " << plan.getGraphElements().size() << endl;  // 3 (p1 + p2 + cloud)
cout << "Points dans le nuage: " << cloud->getPoints().size() << endl;      // 2 (p1 + p2)
```
