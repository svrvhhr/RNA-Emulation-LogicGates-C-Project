# RNA-Emulation-LogicGates-C-Project

Ce projet implémente un Réseau de Neurones Artificiels (RNA) en C pour émuler le fonctionnement des portes logiques AND, OR et XOR. Le réseau comporte une couche cachée avec une fonction d'activation sigmoïde, et il est entraîné avec la rétropropagation pour ajuster les poids en fonction des entrées. L'objectif est de démontrer les principes de base des réseaux de neurones en utilisant des exemples simples de logique binaire.

## Structure du Réseau

Le modèle de réseau de neurones comprend :
- **Entrées** : 2 neurones pour les portes AND, OR et XOR.
- **Couche cachée** : 2 neurones.
- **Sortie** : 1 neurone.

## Étapes de Réalisation

1. **Définition de la Structure du Réseau**
   - Création des neurones d'entrée, de la couche cachée, et de la sortie.

2. **Fonction d'Activation**
   - Utilisation de la fonction sigmoïde pour introduire de la non-linéarité.

3. **Initialisation des Poids**
   - Initialisation aléatoire des poids entre les neurones.

4. **Fonctions du RNA**
   - Développement des fonctions de propagation avant et rétropropagation.

5. **Entraînement du Réseau**
   - Mise en place d'une boucle d'entraînement pour ajuster les poids.

6. **Tests du Réseau**
   - Création de fonctions de test pour évaluer les performances sur les portes logiques.

## Propagation Avant et Rétropropagation

### Propagation Avant
La propagation avant calcule la sortie de chaque neurone, de l'entrée à la sortie, en appliquant des poids et un biais pour chaque connexion.

### Rétropropagation
La rétropropagation ajuste les poids et biais pour réduire l'erreur entre la sortie du réseau et la sortie attendue, en utilisant le gradient de l'erreur.

## Rôle du Taux d'Apprentissage

Le taux d'apprentissage contrôle l'amplitude des ajustements de poids. Un taux trop élevé peut provoquer des oscillations, tandis qu'un taux trop faible ralentit l'apprentissage.

## Optimisations

- **Taux d'Apprentissage Adaptatif** : Ajuste automatiquement le taux d'apprentissage pour chaque poids.
- **Diminution du Taux d'Apprentissage** : Réduit le taux d'apprentissage au fil du temps pour une convergence améliorée.

## Utilisation des Threads et Mutex

L'entraînement du réseau utilise des threads pour paralléliser certains calculs, comme la mise à jour des poids, afin d'accélérer le processus d'entraînement. 

1. **Utilisation des Threads**  
   Les threads permettent d'exécuter plusieurs tâches en simultané, comme le calcul des gradients pour différents poids.

2. **Gestion des Mutex**  
   Les mutex sont utilisés pour synchroniser l'accès aux poids et biais du réseau. Cela garantit que seuls les threads ayant terminé leur calcul peuvent modifier les poids, assurant une mise à jour sécurisée.

3. **Amélioration des Performances**  
   En utilisant plusieurs threads, l'entraînement devient plus rapide, notamment pour de grands ensembles de données et lors de nombreuses itérations.

---

# RNA-Emulation-LogicGates-C-Project

Ce projet implémente un Réseau de Neurones Artificiels (RNA) en C pour émuler le fonctionnement des portes logiques AND, OR et XOR. Le réseau comporte une couche cachée avec une fonction d'activation sigmoïde, et il est entraîné avec la rétropropagation pour ajuster les poids en fonction des entrées. L'objectif est de démontrer les principes de base des réseaux de neurones en utilisant des exemples simples de logique binaire.

## Structure du Réseau

Le modèle de réseau de neurones comprend :
- **Entrées** : 2 neurones pour les portes AND, OR et XOR.
- **Couche cachée** : 2 neurones.
- **Sortie** : 1 neurone.

## Étapes de Réalisation

1. **Définition de la Structure du Réseau**
   - Création des neurones d'entrée, de la couche cachée, et de la sortie.

2. **Fonction d'Activation**
   - Utilisation de la fonction sigmoïde pour introduire de la non-linéarité.

3. **Initialisation des Poids**
   - Initialisation aléatoire des poids entre les neurones.

4. **Fonctions du RNA**
   - Développement des fonctions de propagation avant et rétropropagation.

5. **Entraînement du Réseau**
   - Mise en place d'une boucle d'entraînement pour ajuster les poids.

6. **Tests du Réseau**
   - Création de fonctions de test pour évaluer les performances sur les portes logiques.

## Propagation Avant et Rétropropagation

### Propagation Avant
La propagation avant calcule la sortie de chaque neurone, de l'entrée à la sortie, en appliquant des poids et un biais pour chaque connexion.

### Rétropropagation
La rétropropagation ajuste les poids et biais pour réduire l'erreur entre la sortie du réseau et la sortie attendue, en utilisant le gradient de l'erreur.

## Rôle du Taux d'Apprentissage

Le taux d'apprentissage contrôle l'amplitude des ajustements de poids. Un taux trop élevé peut provoquer des oscillations, tandis qu'un taux trop faible ralentit l'apprentissage.

## Optimisations

- **Taux d'Apprentissage Adaptatif** : Ajuste automatiquement le taux d'apprentissage pour chaque poids.
- **Diminution du Taux d'Apprentissage** : Réduit le taux d'apprentissage au fil du temps pour une convergence améliorée.

## Utilisation des Threads et Mutex

L'entraînement du réseau utilise des threads pour paralléliser certains calculs, comme la mise à jour des poids, afin d'accélérer le processus d'entraînement. 

1. **Utilisation des Threads**  
   Les threads permettent d'exécuter plusieurs tâches en simultané, comme le calcul des gradients pour différents poids.

2. **Gestion des Mutex**  
   Les mutex sont utilisés pour synchroniser l'accès aux poids et biais du réseau. Cela garantit que seuls les threads ayant terminé leur calcul peuvent modifier les poids, assurant une mise à jour sécurisée.

3. **Amélioration des Performances**  
   En utilisant plusieurs threads, l'entraînement devient plus rapide, notamment pour de grands ensembles de données et lors de nombreuses itérations.


## Prérequis

- **Compilateur C** : Un compilateur C standard (comme GCC) est nécessaire pour compiler le code.
- **Outils de gestion des threads** : La bibliothèque `pthread` est utilisée pour la gestion des threads et des mutex dans le programme.

## Limitations

Ce projet a pour objectif de fournir une introduction simple aux réseaux de neurones. Les implémentations plus avancées pourraient inclure plusieurs couches cachées, des fonctions d'activation différentes, et des méthodes d'optimisation plus complexes.

## Améliorations Futures

- **Ajout de couches cachées** pour explorer des réseaux plus profonds.
- **Adaptation du taux d'apprentissage** pour améliorer la convergence et la précision du modèle.
- **Optimisation multithreading** pour gérer des réseaux de neurones plus complexes, avec des poids mis à jour de manière plus efficace.
