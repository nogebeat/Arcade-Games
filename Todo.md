# TODO - Projet Arcade

## Semaine 1: Configuration et bases du projet

### Jour 1-2: Setup et architecture
- [x] **Noge**
  - [x] Mettre à jour la structure du projet
  - [x] Compléter le Makefile (ajouter règles core, games, graphicals)
  - [x] Mettre en place les dossiers pour les bibliothèques

- [ ] **Christian**
  - [x] Développer le DLLoader template pour charger les bibliothèques dynamiques
  - [x] Créer l'encapsulation des fonctions dlopen/dlclose/dlsym/dlerror
  - [x] Tester le chargement/déchargement basique des bibliothèques

- [ ] **Méryl**
  - [x] Définir les interfaces IDisplayModule et IGameModule
  - [x] Préparer la structure des bibliothèques graphiques

### Jour 3-5: Core et première implémentation
- [ ] **Noge**
  - [x] Développer la classe du core du programme
  - [x] Implémenter la logique du menu principal
  - [x] Développer la détection des bibliothèques dans ./lib/

- [ ] **Christian**
  - [x] Créer le système de gestion des scores
  - [x] Implémenter l'architecture pour les entrées clavier
  - [ ] Mettre en place le système de changement de contexte

- [ ] **Méryl**
  - [x] Commencer l'implémentation de NCurses
  - [x] Définir l'interface utilisateur du menu (Noge)

## Semaine 2: Implémentation des bibliothèques

### Jour 6-8: Bibliothèques graphiques
- [ ] **Noge**
  - [x] Terminer l'implémentation de NCurses
  - [x] Commencer SDL2 (initialisation et rendu basique)

- [ ] **Christian**
  - [x] Continuer l'implémentation de SDL2
  - [x] Commencer SFML (initialisation)

- [ ] **Méryl**
  - [x] Terminer l'implémentation de SFML
  - [x] Tester les trois bibliothèques graphiques
  - [ ] Corriger les bugs d'affichage

### Jour 9-11: Jeux
- [ ] **Noge**
  - [x] Implémenter Snake (logique du jeu)
  - [x] Créer les assets pour Snake
  - [ ] Tester Snake avec les bibliothèques graphiques

- [ ] **Christian**
  - [ ] Implémenter Nibbler (logique du jeu)
  - [ ] Créer les assets pour Nibbler
  - [ ] Tester Nibbler avec les bibliothèques graphiques

- [ ] **Méryl**
  - [x] Commencer la documentation technique (via un site web sur un autre repo)
  - [ ] Développer les tests pour valider les jeux
  - [ ] Aider sur l'implémentation des jeux

## Semaine 3: Finalisation et tests

### Jour 12-14: Tests et debug
- [ ] **Noge**
  - [ ] Tester l'intégration des jeux avec les bibliothèques graphiques
  - [ ] Corriger les bugs d'interaction
  - [ ] Optimiser les performances des jeux

- [ ] **Christian**
  - [ ] Finaliser le système de changement de bibliothèque en temps réel
  - [ ] Tester la robustesse du système de chargement
  - [ ] Implémenter les tests unitaires

- [ ] **Méryl**
  - [ ] Finaliser la documentation
  - [ ] Tester la compatibilité entre les systèmes
  - [ ] Préparer la démo du projet

### Jour 15: Collaboration interface
- [ ] **Équipe**
  - [ ] Rencontrer une autre équipe pour la collaboration d'interface
  - [ ] Partager et documenter les interfaces communes
  - [ ] Tester la compatibilité des jeux/bibliothèques avec l'autre équipe

### Jour 16-17: Polissage
- [ ] **Noge**
  - [ ] Optimiser les performances
  - [ ] Corriger les derniers bugs graphiques
  - [ ] Améliorer l'UX du menu principal

- [ ] **Christian**
  - [ ] Finaliser l'interface utilisateur
  - [ ] Corriger les bugs de chargement/déchargement
  - [ ] Améliorer les transitions entre bibliothèques

- [ ] **Méryl**
  - [ ] Vérifier la robustesse et les fuites mémoire
  - [ ] Tester toutes les combinaisons possibles
  - [ ] Finaliser les tests

### Jour 18: Documentation et finalisation
- [ ] **Équipe**
  - [ ] Finaliser la documentation technique
  - [ ] Réunion finale pour vérification
  - [ ] Préparer la livraison finale
  - [ ] S'assurer que toutes les règles du projet sont respectées

## Légende
- ⏳ À faire
- 🔄 En cours
- ✅ Terminé