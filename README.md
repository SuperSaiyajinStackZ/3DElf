# 3DElf
<p align="center">
	<a href="https://github.com/SuperSaiyajinStackZ/3DElf/releases/latest"><img src="https://github.com/SuperSaiyajinStackZ/3DElf/blob/main/3ds/app/banner.png"></a><br>
	<b>3DElf ist ein 'Work in progress' `Elfer raus!` klon für den Nintendo 3DS.</b><br>
</p>

3DElf's Core wurde geschrieben von [SuperSaiyajinStackZ](https://github.com/SuperSaiyajinStackZ).

3DElf wird ein Teil von [StackGames](https://github.com/SuperSaiyajinStackZ/Stack-Game-Template) in der Zukunft werden.

Für eine Beschreibung zu `Elfer raus!` siehe [diesen Eintrag von Wikipedia](https://de.wikipedia.org/wiki/Elfer_raus!).

## Screenshots

Hier findest du ein paar Screenshots zum aktuellen Fortschritt.

### Credits Overlay
![](https://github.com/SuperSaiyajinStackZ/3DElf/blob/main/screenshots/credits_en.png)

### Regeln Overlay
![](https://github.com/SuperSaiyajinStackZ/3DElf/blob/main/screenshots/rules_en.png)

### Spiel Screen
![](https://github.com/SuperSaiyajinStackZ/3DElf/blob/main/screenshots/instructions_en.png) ![](https://github.com/SuperSaiyajinStackZ/3DElf/blob/main/screenshots/game_screen_en.png)  ![](https://github.com/SuperSaiyajinStackZ/3DElf/blob/main/screenshots/sub_menu_en.png)

### Splash Overlay
![](https://github.com/SuperSaiyajinStackZ/3DElf/blob/main/screenshots/dev_by.png)

### Sprachauswahl Overlay
![](https://github.com/SuperSaiyajinStackZ/3DElf/blob/main/screenshots/language_overlay_en.png)


## Dinge, welche noch geplant sind bis v0.1.0:
- [x] Füge eine Konfiguration hinzu für die Sprache etc, damit sie gespeichert werden können. (Die Konfigurations-Datei ist `Config.json` in `sdmc:/3ds/3DElf/`).
- [x] Füge eine Option hinzu, um den Computer im Unter-Menü zu de/aktivieren.
- [x] Füge eine Option hinzu, um die Spieleranzahl im Unter-Menü zu verändern.
- [x] Zeige die Anzahl der Karten von allen Spielern irgendwo im Spiel-Screen an. (Wird nun im Unter-Menü angezeigt).
- [x] Füge eine Option hinzu, um ein Spiel im Unter-Menü von vorne zu beginnen.
- [x] Eventuelle Verbesserungen des Spiel-Cores und der Anwendung.

## Kompilieren
### Die Umgebung aufsetzen

Um 3DElf vom quellcode zu kompilieren, musst du deine Umgebung mit devkitARM, Libctru, Citro2D und Citro3D aufsetzen. Folge devkitPro's [Getting Started](https://devkitpro.org/wiki/Getting_Started) Seite um pacman zu installieren, dann führe `(sudo dkp-)pacman -S devkitARM libctru citro2d citro3d` aus. Du wirst ebenfalls [bannertool](https://github.com/Steveice10/bannertool/releases/latest) und [makerom](https://github.com/profi200/Project_CTR/releases/latest) im `3ds` Ordner benötigen.

### Klonen der Repository

Um den quellcode herunterzuladen, musst du dies mit submodulen klonen, das kann gemacht werden in dem du folgendes ausführst:
```
git clone --recursive https://github.com/SuperSaiyajinStackZ/3DElf.git
```
Oder falls du es bereits geklont hast:
```
git submodule update --init --recursive
```
um alle submodule zu aktualisieren.


Danach führe einfach `make` im `3ds` Ordner aus.

## Credits
### Haupt-Entwicklers
- [SuperSaiyajinStackZ](https://github.com/SuperSaiyajinStackZ): Haupt-Entwickler von 3DElf.

### Andere
- [devkitPro](https://github.com/devkitPro): Für devkitARM, Libctru, Citro2D & Citro3D.
- [Universal-Team](https://github.com/Universal-Team): Für Universal-Core.