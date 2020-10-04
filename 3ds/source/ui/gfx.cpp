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
	Dies beinhaltet alle Kartenfarben in Rot, Gelb, Grün und Blau.

	Dies kann ebenfalls modifiziert werden, für Farb-Mods.
*/
constexpr uint32_t CardColors[4] = {
	C2D_Color32(222, 0, 0, 255),
	C2D_Color32(222, 222, 0, 255),
	C2D_Color32(0, 222, 0, 255),
	C2D_Color32(0, 0, 222, 255)
};

/*
	Zeichne eine basis für den Top Screen.
*/
void GFX::DrawBaseTop() {
	Gui::ScreenDraw(Top);
	Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 180, 180, 255));
}

/*
	Zeichne eine basis für den Touch Screen.
*/
void GFX::DrawBaseBottom() {
	Gui::ScreenDraw(Bottom);
	Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 180, 180, 255));
}

/*
	Zeichne einen Karten-outline.

	int xPos: X Position.
	int yPos: Y Position.
	float Width: Die Breite der Karte.
	float Height: Die Höhe der Karte.
	u32 color: Die Farbe als einen uint32_t / C2D_Color32(r, g, b, a) format.
*/
void GFX::DrawCardOutline(int xPos, int yPos, float Width, float Height, uint32_t color) {
	static constexpr int w = 5; // Breite des outline's.
	C2D_DrawRectSolid(xPos, yPos, 0.5, Width, Height, C2D_Color32(255, 255, 255, 255));

	C2D_DrawRectSolid(xPos, yPos, 0.5, Width, w, color); // top.

	C2D_DrawRectSolid(xPos, yPos + w, 0.5, w, Height - 2 * w, color); // left.

	C2D_DrawRectSolid(xPos + Width - w, yPos + w, 0.5, w, Height - 2 * w, color); // right.

	C2D_DrawRectSolid(xPos, yPos + Height - w, 0.5, Width, w, color); // bottom.
}

/*
	Zeichne eine Karte von einem Kartenstrukt.

	CardStruct CS: Der Kartenstrukt.
	int x: X Position.
	int y: Y Position.
	float xSize: Die Breite der Karte.
	float ySize: Die Höhe der Karte.
	bool top: Ob auf dem Top (true) oder Touch (false) screen. Dies wird verwendet für den Text auf der Karte.
*/
void GFX::DrawCard(CardStruct CS, int x, int y, float xSize, float ySize, bool top) {
	if (CS.CT == CardType::NUMBER_EMPTY || CS.CC == CardColor::COLOR_EMPTY) return;

	DrawCardOutline(x, y, xSize, ySize, CardColors[(uint8_t)CS.CC - 1]);
	Gui::DrawStringCentered(x - (top ? 200 : 160) + (xSize / 2), y + (ySize / 2) - 10, 0.8f, C2D_Color32(0, 0, 0, 255),
							std::to_string((uint8_t)CS.CT));
}


/*
	Zeichne eine Karte mit einem KartenTyp und einer Kartenfarbe.

	CardType CT: Der Kartentyp.
	CardColor CC: Die Kartenfarbe.
	int x: X Position.
	int y: Y Position.
	float xSize: Die Breite der Karte.
	float ySize: Die Höhe der Karte.
	bool top: Ob auf dem Top (true) oder Touch (false) screen. Dies wird verwendet für den Text auf der Karte.
*/
void GFX::DrawCard2(CardType CT, CardColor CC, int x, int y, float xSize, float ySize, bool top) {
	if (CT == CardType::NUMBER_EMPTY || CC == CardColor::COLOR_EMPTY) return;

	DrawCardOutline(x, y, xSize, ySize, CardColors[(uint8_t)CC - 1]);

	Gui::DrawStringCentered(x - (top ? 200 : 160) + (xSize / 2), y + (ySize / 2) - 10, 0.8f, C2D_Color32(0, 0, 0, 255),
							std::to_string((uint8_t)CT));
}

/*
	Zeichne einen Sprite von der sprites spritesheet.

	int index: Sprite Index.
	int x: X Position.
	int y: Y Position.
	float ScaleX: Breiten-Skalierung.
	float ScaleY: Höhen-Skalierung.
*/

void GFX::DrawSprite(int index, int x, int y, float ScaleX, float ScaleY) {
	Gui::DrawSprite(sprites, index, x, y, ScaleX, ScaleY);
}