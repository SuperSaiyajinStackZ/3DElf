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

#include "gfx.hpp"

extern C2D_SpriteSheet sprites;

/*
	Wiedergibt einen uint32_t mit der Karten-Outline Farbe.

	CardColor CL: Die Kartenfarbe.
*/
static const uint32_t ReturnCardColor(CardColor CL) {
	switch(CL) {
		case CardColor::COLOR_EMPTY:
			return NO_COLOR;

		case CardColor::COLOR_1:
			return RED_CARD;

		case CardColor::COLOR_2:
			return YELLOW_CARD;

		case CardColor::COLOR_3:
			return GREEN_CARD;

		case CardColor::COLOR_4:
			return BLUE_CARD;
	}

	return NO_COLOR;
}

/*
	Zeichne eine basis für den Top Screen.
*/
void GFX::DrawBaseTop() {
	Gui::ScreenDraw(Top);
	Gui::Draw_Rect(0, 0, 400, 240, BG_COLOR);
}

/*
	Zeichne eine basis für den Touch Screen.
*/
void GFX::DrawBaseBottom() {
	Gui::ScreenDraw(Bottom);
	Gui::Draw_Rect(0, 0, 320, 240, BG_COLOR);
}

/*
	Zeichne einen Karten-outline.

	int x: Die X Position der Karte.
	int y: Die Y Position der Karte.
	float Width: Die Breite der Karte.
	float Height: Die Höhe der Karte.
	u32 color: Die Outline Farbe als einen uint32_t / C2D_Color32(r, g, b, a) format.
	const int pow: Die Stärke des Outlines.
	bool playable: Ob die Karte gespielt werden kann.
*/
void GFX::DrawCardOutline(int xPos, int yPos, float Width, float Height, uint32_t color, const int pow, bool playable) {
	/* Die Mitte. */
	Gui::Draw_Rect(xPos + pow, yPos + pow, Width - pow, Height - pow, CARD_MIDDLE_COLOR);

	/* Oberes Outline. */
	Gui::Draw_Rect(xPos, yPos, Width, pow, color);

	/* Rechtes Outline. */
	Gui::Draw_Rect(xPos + Width - pow, yPos, pow, Height, color);

	/* Unteres Outline. */
	Gui::Draw_Rect(xPos, yPos + Height - pow, Width, pow, color);

	/* Linkes Outline. */
	Gui::Draw_Rect(xPos, yPos, pow, Height, color);

	/* Falls die Karte nicht gespielt werden kann, blende die Karte etwas aus. */
	if (!playable) Gui::Draw_Rect(xPos, yPos, Width, Height, CARD_DIM_COLOR);
}

/*
	Zeichne eine Karte von einem Kartenstrukt.

	CardStruct CS: Der Kartenstrukt.
	int x: Die X Position der Karte.
	int y: Die Y Position der Karte.
	int w: Die Breite der Karte.
	int h: Die Höhe der Karte.
	int pow: Die Stärke des Outlines.
	bool playable: Ob die Karte gespielt werden kann.
*/
void GFX::DrawCardStruct(CardStruct CS, int x, int y, int w, int h, int pow, bool playable) {
	if (CS.CT == CardType::NUMBER_EMPTY || CS.CC == CardColor::COLOR_EMPTY) return;

	DrawCardOutline(x, y, w, h, ReturnCardColor(CS.CC), pow, playable);

	const int wMax = w - (pow * 2) / 2;
	const int hMax = h - (pow * 2) / 2;

	Gui::DrawString(x + pow + ((wMax) - Gui::GetStringWidth(0.8, std::to_string((uint8_t)CS.CT))) / 2 - (pow / 2),
					y + pow + ((hMax) - Gui::GetStringHeight(0.8, std::to_string((uint8_t)CS.CT))) / 2 - (pow / 2),
					0.8, CARD_NUMB_COLOR, std::to_string((uint8_t)CS.CT), wMax, hMax);
}

/*
	Zeichne eine Karte von einem Kartentypen und Kartenfarbe.

	CardType CT: Der Kartentyp.
	CardColor CC: Die Kartenfarbe.
	int x: Die X Position der Karte.
	int y: Die Y Position der Karte.
	int w: Die Breite der Karte.
	int h: Die Höhe der Karte.
	int pow: Die Stärke des Outlines.
	bool valid: Ob die Karte gespielt werden kann.
*/
void GFX::DrawCardSeparate(CardType CT, CardColor CC, int x, int y, int w, int h, int pow, bool playable) {
	if (CT == CardType::NUMBER_EMPTY || CC == CardColor::COLOR_EMPTY) return;

	DrawCardOutline(x, y, w, h, ReturnCardColor(CC), 4, playable);

	const int wMax = w - (pow * 2) / 2;
	const int hMax = h - (pow * 2) / 2;

	Gui::DrawString(x + pow + ((wMax) - Gui::GetStringWidth(0.8, std::to_string((uint8_t)CT))) / 2 - (pow / 2),
					y + pow + ((hMax) - Gui::GetStringHeight(0.8, std::to_string((uint8_t)CT))) / 2 - (pow / 2),
					0.8, CARD_NUMB_COLOR, std::to_string((uint8_t)CT), wMax, hMax);
}

/*
	Zeichne einen Sprite von der sprites spritesheet.

	int index: Der index des Sprites.
	int x: Die X Position des Sprites.
	int y: Die Y Position des Sprites.
	float ScaleX: Breiten-Skalierung.
	float ScaleY: Höhen-Skalierung.
*/
void GFX::DrawSprite(int index, int x, int y, float ScaleX, float ScaleY) {
	Gui::DrawSprite(sprites, index, x, y, ScaleX, ScaleY);
}