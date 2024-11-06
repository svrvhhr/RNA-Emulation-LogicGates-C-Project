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
   - Création des neurones d'entrée, de la couche cachée et du neurone de sortie.

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

## Threads et Mutex dans le Projet

### Contexte

Dans ce projet, des **threads** et des **mutex** sont utilisés pour paralléliser l'entraînement du réseau de neurones. L'objectif est d'améliorer les performances en permettant à plusieurs parties du réseau d'être entraînées simultanément sur plusieurs cœurs de processeur.

### Rôle des Threads

Les threads permettent de paralléliser les tâches, ce qui est particulièrement utile lors de l'entraînement d'un réseau de neurones. Dans ce projet, chaque neurone d'une couche peut être traité par un thread distinct, ce qui permet d'optimiser l'utilisation des ressources du processeur. L'entraînement est donc effectué plus rapidement en distribuant la charge de travail sur plusieurs threads.

### Rôle des Mutex

Les **mutex** (mutual exclusion locks) sont utilisés pour éviter les conflits d'accès aux ressources partagées, comme les poids du réseau. Lorsqu'un thread met à jour les poids, un mutex garantit que cette mise à jour est exclusive et qu'aucun autre thread ne modifie les mêmes poids en même temps. Cela permet de maintenir la cohérence des données et d'éviter les erreurs de synchronisation.

Les mutex sont utilisés spécifiquement dans la rétropropagation, où les poids doivent être ajustés en fonction des erreurs calculées. Chaque thread obtient un verrou sur les poids avant de les modifier, puis libère ce verrou une fois la mise à jour effectuée. Cela empêche d'autres threads de modifier les poids en même temps et assure la stabilité du modèle.

### Défis et Solutions

- **Synchronisation des Threads :** La gestion de la synchronisation entre les threads est cruciale. L'utilisation de mutex garantit que les ressources partagées, telles que les poids, sont protégées contre les accès concurrentiels indésirables.
  
- **Performance :** L'utilisation de threads améliore la performance de l'entraînement, mais une mauvaise gestion des mutex peut entraîner des blocages. Il est donc essentiel d'optimiser l'utilisation des threads pour éviter les ralentissements dus à une synchronisation excessive.

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

## Rôle du Taux d'Apprentissage

### Contrôle de la Taille des Mises à Jour
- Le taux d'apprentissage détermine la quantité par laquelle les poids du réseau sont ajustés à chaque itération lors de la rétropropagation.
- Si le taux d'apprentissage est trop élevé, les mises à jour des poids peuvent être trop importantes, ce qui peut faire diverger le modèle (c'est-à-dire qu'il ne parviendra pas à converger vers un minimum de la fonction de perte).

### Stabilité de l'Apprentissage
- Un taux d'apprentissage trop élevé peut entraîner des oscillations autour du minimum, où le modèle ne parvient pas à converger, ce qui signifie que l'erreur de prédiction reste élevée.
- En revanche, un taux d'apprentissage trop bas peut rendre l'apprentissage très lent et nécessiter de nombreuses itérations avant d'atteindre une performance acceptable.

### Équilibre entre Vitesse et Précision
- Le choix d'un bon taux d'apprentissage est un équilibre entre rapidité (vitesse de convergence) et précision (capacité à minimiser la fonction de perte).
- Un bon taux d'apprentissage permet au modèle d'apprendre efficacement sans sauter des minima locaux.

## Stratégies d'Optimisation

Pour améliorer le processus d'apprentissage, plusieurs stratégies peuvent être utilisées concernant le taux d'apprentissage :

- **Taux d'Apprentissage Adaptatif**: Des algorithmes comme Adam ou RMSprop ajustent automatiquement le taux d'apprentissage pour chaque poids en fonction de l'historique des gradients.

- **Diminution du Taux d'Apprentissage**: Commencer avec un taux d'apprentissage relativement élevé et le réduire progressivement (annealing) peut aider à stabiliser l'apprentissage à mesure que le modèle converge.
