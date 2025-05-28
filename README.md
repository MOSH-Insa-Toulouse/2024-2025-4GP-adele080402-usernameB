# PROJET CAPTEUR

## Sommaire
- [Description du projet](#description-du-projet)
- [Livrables](#livrables)
- [Matériel utilisé](#matériel-utilisé)
- [Simulation du montage sur LTSpice](#simulation-du-montage-sur-ltspice)
- [Création du PCB](#création-du-pcb)  
    -[KiCad](#kicad)  
    -[Schéma complet](#kicad)  
    -[Impression du PCB](#impression-du-pcb)  
- [Code Arduino](#code-arduino)
- [Application Android](#application-android)
- [Datasheet](#datasheet)
- [Tests de notre capteur et relevé de valeurs](#tests-de-notre-capteur-et-relevé-de-valeurs)


## 📍Description du projet

Nous avons réalisé ce projet dans le cadre de l'UF "du capteur au banc de test en open source hardware", en 4ème année de Génie Physique à l'INSA de Toulouse.
Le but de ce projet, basé sur l'article "Pencil Drawn Strain Gauges and Chemiresistors on Paper" (Cheng-Wei Lin, Zhibo Zhao, Jaemyung Kim & Jiaxing Huang), est de réaliser et tester un capteur low-tech, et d'évaluer son fonctionnement par rapport à un capteur commercialisé, afin de voir s'il est lui-même industrialisable. Le capteur concerné s'apparente à une jauge de contrainte, réalisée avec du papier recouvert d'une couche de graphite.
Pour ce faire, nous avons réalisé un PCB à partir du logiciel KiCad, que nous avons pu intégrer à une carte arduino UNO. Cela nous a permis d'effectuer des mesures et de tester notre capteur.

## Livrables

- PCB Shield adapté à l'Arduino Uno
- Code Arduino complet
- Banc de test du capteur
- Application Android fonctionnant par Bluetooth
- Datasheet du capteur

## Matériel utilisé

- Écran OLED : SSD1306
- Flex sensor
- Capteur Graphène
- Encodeur Rotatoire : KY-040
- Module Bluetooth HC-05
- Amplificateur Opérationnel : LCT-1050
- Potentiomètre Digital : MCP 41050
- Résistances : 1kOhms, 10kOhms, 100kOhms
- Capacités : 2x100nF, 1x1uF

## Simulation du montage sur LTSpice

Avant de commencer la réalisation concrète de notre projet, nous avons réalisé le montage qui sera réalisé physiquement sur LTSpice. Cette simulation nous a permis de comprendre comment l'arduino Uno pouvait acquérir les données du capteur. En effet, sans mettre en place un circuit transimpédance, nous ne serions pas en capacité d'acquérir des valeurs de résistance aussi élevées (k-M Ohms), puisque le courant résultant à acquérir avec un générateur 5V est très faible.

![montage avec capteur image](https://github.com/user-attachments/assets/28f1d7cc-1f73-464c-ba3b-776b41706680)


## Création du PCB
### KiCad

Pour commencer le projet, nous avons dû nous familiariser avec le logiciel KiCad. Au début, nous avons eu du mal à assimiler les différentes étapes à effectuer, à cause de la diversité de ces dernières dans le logiciel KiCad. Nous avons finalement réussi à imprimer notre PCB dans les temps et sans problème. 
Premièrement, nous avons dû reprendre le circuit que nous avions réalisé sur LTSpice qui simulait le circuit final. 

Nous avons pris ce modèle pour réaliser la partie schématique sur KiCad. Nous avons modéliser le circuit amplificateur, ainsi que différents dispositifs également présents sur notre PCB : 

- le potentiomètre digital 

- l'encodeur rotatoire

- l'écran OLED

Ensuite, lorsque nous avons terminé le schématique, nous avons pu passer à l'organisation des éléments du PCB. Après avoir créé les empreintes et importer les bons modèles 3D des différents éléments (que l'on peut retrouver dans le dossier KiCad), nous avons dû disposer de manière la plus optimale ces derniers. Cette étape a été un peu longue et nous avons dû recommencer plusieurs fois afin de limiter le nombre de vias et trouver la meilleure organisation possible. Nous avons finalement réussi à réaliser notre PCB avec seulement 3 vias. Nous avons également utilisé un plan de masse afin de simplifier le circuit. 
Une fois validé, nous avons pu passer à l'impression.

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

Pour imprimer le PCB, nous avons dû télécharger le fichier .gerber. Nous avons envoyé tous nos fichiers KiCad à Catherine Crouzet (Cathy), qui nous a donné rendez vous au GEI. Sur place, elle nous a expliqué toute la procédure. Le développement a été fait grâce au masque (fichier Gerber) placé sur une plaquette vierge et passé aux UVs, puis aux bains de développement.
Une fois la plaquette dessinée, nous sommes allées percer la plaquette (les diamètres sont de 0,8mm pour les composants, et 1mm pour les pins de l'Arduino). Ensuite, nous avons soudé tous les composants. Cette partie était relativement rapide.

![image](https://github.com/user-attachments/assets/4790fe7c-b90f-444d-9095-e8fe2a9e6f41)

                                             Fichier Gerber
                                             
![IMG_1794](https://github.com/user-attachments/assets/38ad4882-ad03-4d1a-b34d-351fe466d517)


                                              PCB imprimé
                                              
![PCB-avec-composants-avant](https://github.com/user-attachments/assets/619ce058-29b2-4ae2-ada8-c9c4e57c32f3)


                                      PCB avec les composants soudés
                                              

## Code Arduino

Nous avons ensuite rédigé le code .ino, écrit en C++. [code](./arduino_code_capteur/arduino_code_capteur.ino)
Pour ce faire, nous nous sommes inspirées des codes étudiés durant les TPs/TDs tout au long du deuxième semestre, qui nous ont permis de mieux comprendre comment fonctionnait chaque composant.
Nous avons rédigé les codes de chaque composant indépendamment afin de pouvoir les tester un à un, puis nous avons écrit le code en rajoutant peu à peu les codes fonctionnels et en les reliant les uns aux autres.

Le plus difficile à coder était l'encodeur rotatoire. Nous avons essayé de nombreuses fois, en nous inspirant des codes des années précédentes, ou des codes présents sur internet (https://passionelectronique.fr/encodeur-rotatif-incremental-mecanique/).
Cependant, nous n'avons pas réussi à écrire un code fonctionnel qui nous permettait de naviguer entre les menus que nous avions créés. Nous avons décidé de garder les menus pour les différents composants (flex sensor, graphite sensor et potentiomètre digital) dans le code, pour pouvoir y accéder si besoin, ainsi que si de prochaines personnes voudraient essayer de rajouter la navigation entre les menus. 
Nous avons néanmoins voulu utiliser l'encodeur rotatoire, donc nous avons rajouté une fonction permettant de faire varier la valeur du potentiomètre digital grâce à l'encodeur.

Nous n'avons malheureusement pas eu le loisir d'être très créatives car nous avons passé beaucoup de temps à décortiquer le fonctionnement et l'écriture du code pour chaque composant. Nous avons tout de même souhaité personnaliser notre projet en rajoutant un écran d'accueil à l'initialisation de l'écran OLED, qu'on peut voir sur la photo ci-dessous. 

<img width="883" alt="E´cran_accueil_OLED" src="https://github.com/user-attachments/assets/3309307b-484f-4732-bbc9-c4adbf6e0e1a" />

                                              Écran d'accueil de l'OLED


## Application Android

Pour l'application android, nous avons rencontré de nombreux problèmes au cours de son développement sur MIT App Inventor. Le premier était simplement un problème d'affichage des données récupérer sur le graphique intéractif. Mais par la suite, nous ne pouvions même plus connecter notre téléphone à l'application, ce qui a nettement ralenti le développement de cette dernière, ainsi que son résultat final.
Nous avons finalement une application à laquelle nous pouvons nous connecter, qui récupère les données affichées simultanément sur l'écran OLED, trace un graphique en temps réel, et contient un bouton RESET.


![1748431283830](https://github.com/user-attachments/assets/b79a7662-210c-4c93-ae8a-88739742811e)


                                              Interface de l'application Android



## Datasheet

Pour écrire la datasheet, nous avons décrit toutes les spécifités de notre capteur, tout en essayant de bien en expliquer son fonctionnement. Nous nous sommes basées sur les datasheets que nous avons pu étudier en cours au début du semestre, ainsi que toutes celles utilisées dans le cadre de nos études ou vies personnelles. La datasheet donne également un exemple d'application que l'on a expérimenté  au cours de ce projet.


## Tests de notre capteur et relevé de valeurs


![Capture d'écran 2025-05-22 152802](https://github.com/user-attachments/assets/5ec3c751-0294-42a1-8ead-dd8882eba561)

![Capture d'écran 2025-05-22 152732](https://github.com/user-attachments/assets/c512df0d-f794-4e0d-974d-6224edc2126a)

Pour les relevés de valeur, nous avons rencontré un problème de consistance dans les mesures.
Le banc de test n'étant pas disponible lors de nos relevés de mesure, nous avons dû improviser et tester le capteur avec des objets circulaires dont le diamètre variait suffisamment pour avoir des données pertinentes. Ci-dessous est une photo des objets que nous avons utilisés.

![Banc-de-test](https://github.com/user-attachments/assets/42071f95-ae15-4534-a8f5-408d54358822)


                                        Objets utilisés opur le banc de test et leurs diamètres

                                        
Nous avons essayé de suivre un protocole de mesure afin d'avoir les mesures les plus pertinentes possible. Cependant, nous n'avons pas eu des mesures très satisfaisantes. 
Plus la mine de crayon est dure (2H), plus le capteur va être sensible et les valeurs vont fluctuer significativement, alors même que le capteur est immobile et qu'on n'y applique aucune déformation.
Inversement, plus la mine de crayon est grasse (6B), moins le capteur va être sensible et les valeurs vont rester très stables. On n'observera donc aucun changement de résistance, même en appliquant une forte déformation.

Aussi la manière de déposer le graphite influence beaucoup les valeurs obtenues.

Nous avons réussi à relever des valeurs uniquement pour les mines B et HB. Pour les autres mines testées, les valeurs n'étaient malheureusement pas pertinentes.

- HB : Mine avec laquelle le relevé de données a été concluant en compression mais moins .
- B : Mine avec laquelle le relevé de données a été le plus concluant.
- 6B :Les valeurs de résistance mesurées avec cette mine restent bloquées à une valeur :  à 650(????KOHM OU MOHM?????), même si la déformation appliquée est très importante.
- 2H : Les valeurs de résistance mesurées fluctuent trop, nous ne parvenons pas à avoir de données stables. 
