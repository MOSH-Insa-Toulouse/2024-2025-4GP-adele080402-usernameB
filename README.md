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

## Création du PCB
### KiCad

Pour commencer le projet, nous avons dû apprivoiser le logiciel KiCad. Nous avons eu du mal à assimiler les différentes choses à faire mais nous avons finalement réussi à imprimer notre PCB sans embûches. 
Tout d'abord, nous avons dû reprendre le circuit que nous avions réalisé sur LTSpice qui simulait le circuit final. (INS2RER UNE PHOTO)
Nous avons pris ce modèle pour réaliser la partie schématique sur KiCad. Nous avons modéliser le circuit amplificateur, ainsi que le potentiomètre digital, l'encodeur rotatoire et l'écran OLED. 
(INSERER UNE PHOTO)

Ensuite, lorsque nous avons terminé le schématique, nous avons pu passer à l'organisation des éléments du PCB. Après avoir créé les empreintes et importer les bons modèles 3D des différents éléments, nous avons dû disposer de manière la plus optimale ces derniers. Cette étape a été un peu longue et nous avons dû recommencer plusieurs fois, mais nous avons réussi à réaliser notre PCB avec seulement 3 vias. Nous avons disposé un plan de masse afin de simplifier le circuit. 
Une fois validé par Cathy et M. Grisolia, nous avons pu passer à l'impression.

### Impression du PCB

Pour imprimer le PCB, nous avons d'abord dû télécharger le fichier .gerber. Nous avons envoyé tout nos fichiers KiCad à Cathy qui nous a donné rendez vous au GEI. Là-bas, elle nous a expliqué toute la procédure.
Une fois la plaquette dessinée, nous sommes allés percer la plaque (les diamètres sont de 0,8mm pour les composants, et 1mm pour les pins de l'arduino). Ensuite, nous avons soudé tous les composants. Cette partie était assez rapide.

## Code Arduino

## Application Android