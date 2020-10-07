/*
	Diese Datei ist Teil von 3DElf.
	Copyright (C) 2020 bei SuperSaiyajinStackZ.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Additional Terms 7.b and 7.c of GPLv3 apply to this file:
		* Requiring preservation of specified reasonable legal notices or
		  author attributions in that material or in the Appropriate Legal
		  Notices displayed by works containing it.
		* Prohibiting misrepresentation of the origin of that material,
		  or requiring that modified versions of such material be marked in
		  reasonable ways as different from the original version.
*/

#ifndef _3DELF_GFX_HPP
#define _3DELF_GFX_HPP

#include "common.hpp"
#include "coreHelper.hpp"
#include "sprites.h"
#include <citro2d.h>

/* Definiere die Farben hier. */
#define TEXT_COLOR C2D_Color32(255, 255, 255, 255) // Text Farbe.
#define BAR_COLOR C2D_Color32(0, 130, 130, 255) // Balken Farbe.
#define BG_COLOR C2D_Color32(0, 180, 180, 255) // Hintergrund Farbe.
#define BOX_COLOR C2D_Color32(0, 130, 130, 255) // TextBox Farbe.

#define BUTTON_SELECTED C2D_Color32(0, 222, 222, 255) // Ausgewählte Schaltflächen Farbe.
#define BUTTON_UNSELECTED C2D_Color32(0, 130, 130, 255) // Nicht Ausgewählte Schaltflächen Farbe.

#define DIM_COLOR C2D_Color32(0, 0, 0, 170) // Gedunkelter Bildschirm Farbe.
#define NO_COLOR C2D_Color32(0, 0, 0, 0) // Transparente Farbe.

#define CARD_SLT_COLOR C2D_Color32(0, 0, 0, 255) // Karten-Selektor Farbe.
#define CARD_NUMB_COLOR C2D_Color32(0, 0, 0, 255) // Karten-Nummer Farbe.
#define CARD_DIM_COLOR C2D_Color32(0, 0, 0, 150) // Falls die Karte nicht spielbar ist.
#define CARD_MIDDLE_COLOR C2D_Color32(255, 255, 255, 255) // Karten-Mitte Farbe.

#define RED_CARD C2D_Color32(222, 0, 0, 255) // Rote Karten Farbe.
#define YELLOW_CARD C2D_Color32(222, 222, 0, 255) // Gelbe Karten Farbe.
#define GREEN_CARD C2D_Color32(0, 222, 0, 255) // Grüne Karten Farbe.
#define BLUE_CARD C2D_Color32(0, 0, 222, 255) // Blaue Karten Farbe.

namespace GFX {
	/* Basiszeug. */
	void DrawBaseTop();
	void DrawBaseBottom();

	/* Karten-Outline Zeichnungs-Funktion. */
	void DrawCardOutline(
		int xPos, int yPos, float Width = 60, float Height = 80,
		uint32_t color = NO_COLOR, const int pow = 5,
		bool playable = true
	);

	/* Karten-Outline mit Kartenstrukt Zeichnungs-Funktion. */
	void DrawCardStruct(
		CardStruct CS, int x, int y, int w = 40, int h = 60,
		int pow = PLAYER_CARD_OUTLINE_SIZE,
		bool playable = true
	);

	/* Karten-Outline mit separatem Kartentyp + Kartenfarbe Zeichnungs-Funktion. */
	void DrawCardSeparate(
		CardType CT, CardColor CC, int x, int y, int w = 40, int h = 40,
		int pow = TABLE_CARD_OUTLINE_SIZE,
		bool playable = true
	);

	/* Spritezeug. */
	void DrawSprite(int index, int x, int y, float ScaleX = 1, float ScaleY = 1);
};

#endif