# PROJET CAPTEUR

## Description du projet

Nous avons réalisé ce projet dans le cadre de l'UF "du capteur au banc de test en open source hardware", en 4ème année de Génie Physique à l'INSA de Toulouse.
Le but de ce projet est de réaliser et tester un capteur low-tech, et d'évaluer son fonctionnement par rapport à un capteur commercialisé. Le capteur concerné s'apparente à une jauge d'extensométrie, réalisée avec du papier une mine de graphite.
Pour ce faire, nous avons réalisé un PCB sur KiCad, que nous avons pu intégrer à une carte arduino UNO afin d'avoir un banc de test complet.

## Livrables

- PCB Shield adapté à l'Arduino Uno
- Code Arduino complet
- Banc de test du capteur
- Application Android fonctionnant par Bluetooth
- Datasheet du capteur

## Matériel utilisé

- Ecran OLED : SSD1306
- Flex sensor
- Capteur Graphène
- Encodeur Rotatoire : KY-040
- Module Bluetooth HC-05
- Ampli Op : LCT-1050
- Potentiomètre Digital : MCP 41050
- Résistances : 1kOhms, 10kOhms, 100kOhms
- Capacités : 2x100nF, 1x1uF

## Simulation du montage sur LTSpice


## Création du PCB
### KiCad

Pour commencer le projet, nous avons dû apprivoiser le logiciel KiCad. Nous avons eu du mal à assimiler les différentes choses à faire mais nous avons finalement réussi à imprimer notre PCB sans embûches. 
Tout d'abord, nous avons dû reprendre le circuit que nous avions réalisé sur LTSpice qui simulait le circuit final. 

Nous avons pris ce modèle pour réaliser la partie schématique sur KiCad. Nous avons modéliser le circuit amplificateur, ainsi que différents dispositifs également présents sur notre PCB : 

- le potentiomètre digital 
(INSERER UNE PHOTO)

- l'encodeur rotatoire
(INSERER UNE PHOTO)

- l'écran OLED
(INSERER UNE PHOTO)

Ensuite, lorsque nous avons terminé le schématique, nous avons pu passer à l'organisation des éléments du PCB. Après avoir créé les empreintes et importer les bons modèles 3D des différents éléments, nous avons dû disposer de manière la plus optimale ces derniers. Cette étape a été un peu longue et nous avons dû recommencer plusieurs fois, mais nous avons réussi à réaliser notre PCB avec seulement 3 vias. Nous avons disposé un plan de masse afin de simplifier le circuit. 
Une fois validé par Cathy et M. Grisolia, nous avons pu passer à l'impression.

### Schéma complet

![Schématique du PCB](https://github.com/user-attachments/assets/20b3bf86-4e35-498b-a52c-529bb1db0f77)

                                            Schématique du PCB

![Routage terminé du PCB](https://github.com/user-attachments/assets/7cc50e52-7f20-4848-a44f-224ce279f040)

                                          Routage terminé du PCB
                                          
![Modèle 3D du PCB (face avant)](https://github.com/user-attachments/assets/e4782bd4-955f-4bdd-8529-4a3dec8962ba)

                                          Modèle 3D du PCB (face avant)
                                            
![Modèle 3D du PCB (face arrière)](https://github.com/user-attachments/assets/bb23b73f-7a47-4d54-8471-7cf950edd41d)

                                          Modèle 3D du PCB (face arrière)
                                            

### Impression du PCB

Pour imprimer le PCB, nous avons d'abord dû télécharger le fichier .gerber. Nous avons envoyé tout nos fichiers KiCad à Cathy qui nous a donné rendez vous au GEI. Là-bas, elle nous a expliqué toute la procédure.
Une fois la plaquette dessinée, nous sommes allés percer la plaque (les diamètres sont de 0,8mm pour les composants, et 1mm pour les pins de l'arduino). Ensuite, nous avons soudé tous les composants. Cette partie était assez rapide.

![image](https://github.com/user-attachments/assets/4790fe7c-b90f-444d-9095-e8fe2a9e6f41)

                                             Fichier Gerber

## Code Arduino

Nous avons ensuite rédigé le code .ino, écrit en C++.
Pour ce faire, nous nous sommes inspirés des codes étudiés durant les TPs/TDs tout au long du deuxième semestre, qui nous ont permis de mieux comprendre comment fonctionnait chaque composant.
Nous avons rédigé les codes de chaque composant indépendamment pour les tester un par un, puis nous avons écrit le code en rajoutant peu à peu les codes fonctionnels et en les reliant les uns aux autres.

Le plus difficile à coder était l'encodeur rotatoire. Nous avons essayé de nombreuses fois, en nous inspirant des codes des années précédentes, ou des codes présents sur internet (https://passionelectronique.fr/encodeur-rotatif-incremental-mecanique/).
Cependant, nous n'avons pas réussi à écrire un code fonctionel qui nous permettait de naviguer entre les menus que nous avions créé. Nous avons décidé de garder les menus pour les différents composants (flex sensor, graphite sensor et potentiomètre digital) dans le code, pour pouvoir y accéder si besoin, et si de prochaines personnes voudraient tenter de rajouter la navigation entre les menus plus tard. 

Nous n'avons malheureusement pas eu le loisir d'être très créative car nous avons passé beaucoup de temps à décortiquer le fonctionnement et l'écriture du code pour chaque composant. Nous avons tout de même souhaité personnaliser notre projet en rajoutant un écran d'acueil à l'initialisation de l'écran OLED, qu'on peut voir sur  la photo ci-dessous. 

                        [INSERER PHOTO ECRAN ACCUEIL]


## Application Android

Pour l'application android, nous


### DATASHEET

Pour écrire la datasheet, nous avons décrit toutes les spécifités de notre capteur, tout en essayant de bien en expliquer son fonctionnement. Nous avons 


### Tests de notre capteur et relevé de valeurs



- HB : marche bien, on a pu effectuer les mesures
- B : résistance bloquée à deux valeurs : 188 et 191 même si on tord dans tous les sens
- 6B : pareil mais bloqué a 650
- 2H ça fluctue trop on n'arrive pas à avoir de données stable

==> On voit que plus le crayon est dur (2H) plus le capteur est sensible et les valeurs fluctuent beaucoup trop
Plus le capteur est gras, moins il est sensible et la resistance reste bloquée aux même valeurs

==> Impossible de relever des données 
