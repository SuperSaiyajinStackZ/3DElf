/*
	Diese Datei ist Teil von 3DElf.
	Copyright (C) 2020-2021 bei SuperSaiyajinStackZ.

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

#include "common.hpp"
#include "gfx.hpp"

static void Draw() {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
	C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));

	GFX::DrawBaseTop();
	Gui::Draw_Rect(0, 0, 400, 25, BAR_COLOR);
	Gui::Draw_Rect(0, 215, 400, 25, BAR_COLOR);

	GFX::DrawCardStruct({ CardType::NUMBER_11, CardColor::COLOR_1 }, 40, 80, 40, 60, 5, true);
	GFX::DrawCardStruct({ CardType::NUMBER_11, CardColor::COLOR_2 }, 135, 80, 40, 60, 5, true);
	GFX::DrawCardStruct({ CardType::NUMBER_11, CardColor::COLOR_3 }, 230, 80, 40, 60, 5, true);
	GFX::DrawCardStruct({ CardType::NUMBER_11, CardColor::COLOR_4 }, 325, 80, 40, 60, 5, true);

	Gui::DrawStringCentered(0, 1, 0.6f, TEXT_COLOR, Lang::get("PLAY_ORDER"), 390);
	Gui::DrawStringCentered(0, 217, 0.6f, TEXT_COLOR, Lang::get("A_CONTINUE"), 390);

	GFX::DrawBaseBottom();
	Gui::Draw_Rect(0, 0, 320, 25, BAR_COLOR);
	Gui::Draw_Rect(0, 215, 320, 25, BAR_COLOR);
	C3D_FrameEnd(0);
}

void Overlays::CardOrderOverlay() {
	bool doOut = false;

	while(!doOut) {
		Draw();

		hidScanInput();

		if (hidKeysDown() & KEY_A) doOut = true;
	}
}