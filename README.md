# RNA-Emulation-LogicGates-C-Project

Ce projet implémente un Réseau de Neurones Artificiels (RNA) en C pour émuler le fonctionnement des portes logiques AND, OR et XOR. Le réseau comprend une couche cachée avec la fonction d'activation sigmoïde, et il est entraîné à l'aide de la rétropropagation pour ajuster les poids en fonction des entrées. L'objectif est de démontrer les principes de base des réseaux de neurones en utilisant des exemples simples de logique binaire.

## Modélisation

Le modèle du réseau de neurones est constitué de :

- **Entrées :** 2 neurones (pour AND et OR), 2 neurones (pour XOR)
- **Couche Cachée :** 2 neurones
- **Sortie :** 1 neurone

## Mise en Œuvre

### Étapes de Réalisation

1. **Définition de la Structure du Réseau :** 
   - Création des neurones d'entrée, de la couche cachée et de la neurone de sortie.

2. **Fonction d'Activation :**
   - Utilisation de la fonction sigmoïde pour introduire la non-linéarité.

3. **Initialisation des Poids :**
   - Initialisation aléatoire des poids des connexions entre les neurones.

4. **Fonctions de la RNA :**
   - Développement des fonctions pour la propagation avant et la rétropropagation.

5. **Entraînement du Réseau :**
   - Mise en place d'une boucle d'entraînement pour ajuster les poids.

6. **Test du Réseau :**
   - Création de fonctions pour tester les performances sur les portes logiques.

7. **Optimisation :**
   - Ajustement des hyperparamètres pour améliorer les résultats.


## Propagation Avant et Rétropropagation

### 1. Propagation Avant
La propagation avant calcule la sortie de chaque neurone, couche par couche, de l'entrée à la sortie.

- **Sommation pondérée** (entrée du neurone) :
  \[
  z_j^{(l)} = \sum_{i} w_{ij}^{(l)} \cdot a_i^{(l-1)} + b_j^{(l)}
  \]
  où :
  - \( w_{ij}^{(l)} \) est le poids entre le neurone \( i \) de la couche \( l-1 \) et le neurone \( j \) de la couche \( l \),
  - \( a_i^{(l-1)} \) est l'activation du neurone \( i \) dans la couche précédente,
  - \( b_j^{(l)} \) est le biais du neurone \( j \) dans la couche \( l \).

- **Activation** (sortie du neurone) :
  \[
  a_j^{(l)} = f(z_j^{(l)})
  \]
  où \( f \) est la fonction d'activation. Pour une fonction sigmoïde :
  \[
  f(z) = \frac{1}{1 + e^{-z}}
  \]

### 2. Rétropropagation
La rétropropagation ajuste les poids et biais pour réduire l'erreur entre la sortie prédite et la sortie attendue, en suivant le gradient de l'erreur.

- **Calcul de l'erreur en sortie** :
  Pour la couche de sortie \( L \), l'erreur pour chaque neurone \( j \) est donnée par :
  \[
  \delta_j^{(L)} = \frac{\partial C}{\partial a_j^{(L)}} \cdot f'(z_j^{(L)})
  \]
  où :
  - \( C \) est la fonction de coût (par exemple, l'erreur quadratique moyenne),
  - \( f'(z_j^{(L)}) \) est la dérivée de la fonction d'activation appliquée à \( z_j^{(L)} \).

- **Propagation de l'erreur vers l'arrière** :
  Pour une couche \( l \) avant la couche de sortie, l'erreur \( \delta_j^{(l)} \) pour chaque neurone \( j \) est :
  \[
  \delta_j^{(l)} = \left( \sum_{k} \delta_k^{(l+1)} \cdot w_{jk}^{(l+1)} \right) \cdot f'(z_j^{(l)})
  \]

- **Mise à jour des poids et biais** :
  Les poids et biais sont ajustés pour chaque couche :
  \[
  w_{ij}^{(l)} := w_{ij}^{(l)} - \eta \cdot \delta_j^{(l)} \cdot a_i^{(l-1)}
  \]
  \[
  b_j^{(l)} := b_j^{(l)} - \eta \cdot \delta_j^{(l)}
  \]
  où \( \eta \) est le taux d'apprentissage.

Ces étapes permettent au réseau de minimiser l'erreur entre les prédictions et les valeurs cibles.