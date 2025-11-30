# RECOMMANDATIONS D'AMÉLIORATION - ANTIFRAGILITÉ

**Document**: Guide de renforcement du code MiniDesign  
**Date**: 29 novembre 2025

---

## 📋 TABLE DES MATIÈRES

1. [Validation des Entrées](#validation)
2. [Const-Correctness](#const)
3. [Gestion des Erreurs](#erreurs)
4. [Exemples de Code Amélioré](#exemples)

---

## <a id="validation"></a>1. VALIDATION DES ENTRÉES

### Problème Actuel

La fonction `analyserPosition()` ne valide pas ses paramètres :

```cpp
// ❌ CODE ACTUEL (VULNÉRABLE)
pair<int,int> analyserPosition(string& posStr)
{
    int x, y;  // Non initialisés!
    size_t commaPos = posStr.find(',');
    if (commaPos != string::npos) {
        x = stoi(posStr.substr(0, commaPos));  // Peut lever!
        y = stoi(posStr.substr(commaPos + 1));  // Peut lever!
    } else {
        istringstream iss(posStr);
        iss >> x >> y;  // Peut échouer silencieusement
    }
    return {x, y};  // Peut retourner des valeurs aléatoires
}
```

### Problèmes Spécifiques

1. **Variables non initialisées**: Si le parsing échoue, `x` et `y` contiennent des valeurs aléatoires
2. **Pas de try-catch**: `stoi()` peut lever `std::invalid_argument` ou `std::out_of_range`
3. **Pas de limite**: Accepte les coordonnées impossibles (-999999, 999999)
4. **Pas de vérification**: N'accepte que les formats "(x,y)" ou "x y" mais pas "(x y)" ou "x,y"

### ✅ SOLUTION RECOMMANDÉE

Créez un fichier `Validateur.h` :

```cpp
#pragma once

#include <string>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

class Validateur {
public:
    // Limites raisonnables
    static constexpr int MIN_COORD = -1000;
    static constexpr int MAX_COORD = 1000;
    static constexpr int MAX_POINTS = 10000;
    
    /**
     * Valide si les coordonnées sont dans les limites acceptables
     * @param x Coordonnée X
     * @param y Coordonnée Y
     * @return true si valide, false sinon
     */
    static bool coordonneesValides(int x, int y) {
        return x >= MIN_COORD && x <= MAX_COORD &&
               y >= MIN_COORD && y <= MAX_COORD;
    }
    
    /**
     * Analyse une position au format "(x,y)" ou "x y"
     * @param posStr Chaîne à analyser
     * @return pair<bool, pair<int,int>> : (succès, (x, y))
     * 
     * Exemples:
     *   "(5,10)" → {true, {5, 10}}
     *   "5 10" → {true, {5, 10}}
     *   "999999" → {false, {0, 0}} (coordonnée invalide)
     *   "abc" → {false, {0, 0}} (format invalide)
     */
    static pair<bool, pair<int,int>> analyserPosition(const string& posStr) {
        int x = 0, y = 0;  // ✅ Initialisés par défaut
        
        try {
            // Essayer le format "(x,y)"
            string temp = posStr;
            // Nettoyer les parenthèses
            temp.erase(remove(temp.begin(), temp.end(), '('), temp.end());
            temp.erase(remove(temp.begin(), temp.end(), ')'), temp.end());
            temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
            
            size_t commaPos = temp.find(',');
            if (commaPos != string::npos) {
                // Format "(x,y)"
                x = stoi(temp.substr(0, commaPos));
                y = stoi(temp.substr(commaPos + 1));
            } else {
                // Format "x y"
                istringstream iss(posStr);
                if (!(iss >> x >> y)) {
                    cerr << "Erreur: impossible de parser la position" << endl;
                    return {false, {0, 0}};
                }
            }
            
            // ✅ Vérifier les limites
            if (!coordonneesValides(x, y)) {
                cerr << "Erreur: coordonnées hors limites (" 
                     << MIN_COORD << " à " << MAX_COORD << ")" << endl;
                return {false, {0, 0}};
            }
            
            return {true, {x, y}};
            
        } catch (const std::invalid_argument& e) {
            cerr << "Erreur: format invalide - " << e.what() << endl;
            return {false, {0, 0}};
        } catch (const std::out_of_range& e) {
            cerr << "Erreur: nombre hors limites - " << e.what() << endl;
            return {false, {0, 0}};
        } catch (const exception& e) {
            cerr << "Erreur: " << e.what() << endl;
            return {false, {0, 0}};
        }
    }
    
    /**
     * Valide un ID
     * @param id L'ID à valider
     * @return true si ID >= 0
     */
    static bool idValide(int id) {
        return id >= 0;
    }
    
    /**
     * Valide une collection d'IDs
     * @param ids Vecteur des IDs
     * @return true si tous les IDs sont valides et pas vide
     */
    static bool idsValides(const vector<int>& ids) {
        if (ids.empty()) {
            cerr << "Erreur: au moins un ID requis" << endl;
            return false;
        }
        if (ids.size() > MAX_POINTS) {
            cerr << "Erreur: trop d'IDs (max: " << MAX_POINTS << ")" << endl;
            return false;
        }
        for (int id : ids) {
            if (!idValide(id)) {
                cerr << "Erreur: ID invalide (" << id << ")" << endl;
                return false;
            }
        }
        return true;
    }
};
```

### Créez `Validateur.cpp`

```cpp
#include "Validateur.h"

// Tout est inline dans le header pour faciliter les tests unitaires
```

### Mise à Jour de MiniDesign.cpp

```cpp
#include "Validateur.h"

// ...

int main(int argc, char* argv[]) {
    // ... code existant ...
    
    while (true) {
        afficherMenu();
        getline(std::cin, cmd);
        
        // ... autres commandes ...
        
        else if (cmd == "d") {
            cout << "Entrez l'ID du point a deplacer : ";
            string idStr;
            getline(cin, idStr);
            
            // ✅ Validation
            try {
                int id = stoi(idStr);
                if (!Validateur::idValide(id)) {
                    cerr << "ID invalide" << endl;
                    continue;  // Retour au menu
                }
                
                // Vérifier existence
                if (!plan.getGraphElementById(id)) {
                    cerr << "Point avec ID " << id << " n'existe pas" << endl;
                    continue;
                }
                
            } catch (const exception& e) {
                cerr << "Erreur: " << e.what() << endl;
                continue;
            }
            
            cout << "Entrez la nouvelle position (x y) ou (x,y) : ";
            string posStr;
            getline(cin, posStr);
            
            // ✅ Analyser et valider
            auto [succes, pos] = Validateur::analyserPosition(posStr);
            if (!succes) {
                continue;
            }
            
            shared_ptr<Commande> commande = make_shared<CommanderDéplacer>(
                plan, id, pos
            );
            invocateur.executer(commande);
            cout << "Point déplacé avec succès" << endl;
        }
    }
}
```

---

## <a id="const"></a>2. CONST-CORRECTNESS

### Problème Actuel

```cpp
// ❌ MAUVAIS: Plan peut être modifié
class CommandeAffichage : public Commande {
private:
    Plan& m_plan;  // Pas const
};

// ❌ MAUVAIS: String peut être modifié
pair<int,int> analyserPosition(string& posStr) {  // Référence non-const
    posStr.erase(...);  // Modificateur utilisé!
    ...
}
```

### ✅ SOLUTION

```cpp
// BON: Plan n'est pas modifié
class CommandeAffichage : public Commande {
private:
    const Plan& m_plan;  // ✅ Const
};

// BON: String n'est pas modifié
pair<bool, pair<int,int>> analyserPosition(const string& posStr) {
    // string temp = posStr; // Copier si besoin
    // temp.erase(...);      // Modifier la copie
    ...
}

// BON: Plan n'est pas modifié
shared_ptr<PointCloud> Plan::getNuagesByTexture(const string& texture) const {
    for (const auto& element : m_graphElements) {  // ✅ const auto&
        ...
    }
}
```

### Mise à Jour CommandeAffichage.h

```cpp
#pragma once

#include "Commande.h"
#include "Affichage.h"
#include <memory>

using namespace std;

class CommandeAffichage : public Commande
{
    public:
        void executer() override;
        ~CommandeAffichage() override = default;
        CommandeAffichage(unique_ptr<Affichage> affichage, const Plan& plan);  // ✅ const
    
    private:
        unique_ptr<Affichage> m_affichage;
        const Plan& m_plan;  // ✅ const
    
};
```

---

## <a id="erreurs"></a>3. GESTION DES ERREURS

### Problème Actuel

```cpp
// ❌ Pas d'information si la commande échoue
shared_ptr<Commande> commande = make_shared<CommanderDéplacer>(plan, id, newPos);
invocateur.executer(commande);
// Silence total si erreur!
```

### ✅ SOLUTION

Modifier `Commande.h` :

```cpp
#pragma once

using namespace std;

class Commande
{
    public:
        virtual ~Commande() = default;
        
        /**
         * Exécute la commande
         * @return true si exécution réussie, false sinon
         */
        virtual bool executer() = 0;
        
        /**
         * Annule la commande (pour undo)
         * @return true si annulation réussie, false sinon
         */
        virtual bool undo() { return false; }
        
        /**
         * Retourne le message d'erreur (si erreur)
         * @return Message d'erreur vide si succès
         */
        virtual string getErreur() const { return ""; }
};
```

Modifier `CommanderDéplacer.h` :

```cpp
class CommanderDéplacer : public Commande
{
    public:
        CommanderDéplacer(Plan& plan, int id, const pair<int,int>& position);
        bool executer() override;
        bool undo() override;
        string getErreur() const override { return m_erreur; }
    private:
        Plan& m_plan;
        int m_id;
        pair<int,int> m_position;
        pair<int,int> m_anciennePosition;
        string m_erreur;  // Message d'erreur
};
```

Modifier `CommanderDéplacer.cpp` :

```cpp
bool CommanderDéplacer::executer()
{
    m_erreur.clear();
    
    // Vérifier que l'élément existe
    auto element = m_plan.getGraphElementById(m_id);
    if (!element) {
        m_erreur = "Point avec ID " + to_string(m_id) + " n'existe pas";
        cerr << "Erreur: " << m_erreur << endl;
        return false;  // ✅ Indique l'erreur
    }
    
    // Sauvegarder l'ancienne position
    getPositionIfPoint(element, m_anciennePosition);
    
    // Exécuter le déplacement
    m_plan.deplacerGraphElementById(m_id, m_position);
    return true;  // ✅ Succès
}

bool CommanderDéplacer::undo()
{
    m_erreur.clear();
    
    auto element = m_plan.getGraphElementById(m_id);
    if (!element) {
        m_erreur = "Impossible d'annuler: point n'existe plus";
        return false;
    }
    
    m_plan.deplacerGraphElementById(m_id, m_anciennePosition);
    return true;
}
```

Modifier `Invocateur.cpp` :

```cpp
void Invocateur::executer(shared_ptr<Commande> cmd)
{
    if (!cmd) {
        cerr << "Erreur: commande nulle" << endl;
        return;
    }
    
    // ✅ Vérifier si l'exécution a réussi
    if (!cmd->executer()) {
        cerr << "Commande échouée: " << cmd->getErreur() << endl;
        return;
    }
    
    pile_annulation_.push_back(cmd);
    pile_rétablissement_.clear();
}
```

---

## <a id="exemples"></a>4. EXEMPLES DE CODE AMÉLIORÉ

### Exemple Complet: Parsing de Points

```cpp
// ✅ AVANT (Vulnérable)
vector<shared_ptr<GraphElement>> points;
for (const auto& posStr : positions) {
    auto pos = analyserPosition(const_cast<string&>(posStr));
    auto point = make_shared<Point>(pos);
    points.push_back(point);
}

// ✅ APRÈS (Robuste)
vector<shared_ptr<GraphElement>> points;
for (const auto& posStr : positions) {
    auto [succes, pos] = Validateur::analyserPosition(posStr);
    
    if (!succes) {
        cerr << "Impossible de créer le point à partir de: " << posStr << endl;
        continue;  // Sauter ce point, pas d'erreur fatale
    }
    
    if (!Validateur::coordonneesValides(pos.first, pos.second)) {
        cerr << "Coordonnées hors limites: " << pos.first << "," << pos.second << endl;
        continue;
    }
    
    try {
        auto point = make_shared<Point>(pos);
        points.push_back(point);
    } catch (const exception& e) {
        cerr << "Erreur lors de création du point: " << e.what() << endl;
        continue;
    }
}

if (points.empty()) {
    cerr << "Erreur: aucun point valide" << endl;
    return false;
}
```

### Exemple: Fusion Sécurisée

```cpp
// ✅ AVANT
else if (cmd == "f") {
    vector<int> ids;
    string idsStr;
    getline(cin, idsStr);
    istringstream iss(idsStr);
    int id;
    while (iss >> id) {
        ids.push_back(id);  // ❌ Pas de limites!
    }
    auto commande = make_shared<FusionEnNuageCommand>(plan, ids, texturesNuages);
    invocateur.executer(commande);
}

// ✅ APRÈS
else if (cmd == "f") {
    cout << "Entrez les IDs à fusionner (séparés par des espaces) : ";
    vector<int> ids;
    string idsStr;
    getline(cin, idsStr);
    
    try {
        istringstream iss(idsStr);
        int id;
        while (iss >> id) {
            ids.push_back(id);
        }
        
        // ✅ Valider
        if (!Validateur::idsValides(ids)) {
            continue;
        }
        
        // ✅ Vérifier existence
        for (int id : ids) {
            if (!plan.getGraphElementById(id)) {
                cerr << "Point " << id << " n'existe pas" << endl;
                continue;  // Retour menu
            }
        }
        
        auto commande = make_shared<FusionEnNuageCommand>(plan, ids, texturesNuages);
        if (!commande->executer()) {
            cerr << "Fusion échouée: " << commande->getErreur() << endl;
            continue;
        }
        
        pile_annulation_.push_back(commande);
        cout << "Fusion réussie" << endl;
        
    } catch (const exception& e) {
        cerr << "Erreur lors de la fusion: " << e.what() << endl;
    }
}
```

---

## 🎯 CONCLUSION DES RECOMMANDATIONS

### Fichiers à Créer
1. ✅ `Validateur.h` - Classe de validation
2. ✅ `Validateur.cpp` - Implémentation

### Fichiers à Modifier
1. ✅ `Commande.h` - Ajouter retour d'erreur
2. ✅ `CommandeAffichage.h` - Const-correctness
3. ✅ `CommanderDéplacer.h/.cpp` - Validation + erreurs
4. ✅ `CommanderSupprimer.h/.cpp` - Validation + erreurs
5. ✅ `Invocateur.h/.cpp` - Vérifier retour commandes
6. ✅ `MiniDesign.cpp` - Utiliser Validateur + vérifier résultats

### Priorité d'Implémentation
1. **Urgent** : Validateur + validation MiniDesign.cpp
2. **Important** : Const-correctness
3. **Recommandé** : Retour d'erreur des commandes

**Temps estimé**: 2-3 heures pour un implémentation complète.

---

*Document de recommandations - 29 novembre 2025*
