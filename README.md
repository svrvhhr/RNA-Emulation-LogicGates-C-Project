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
