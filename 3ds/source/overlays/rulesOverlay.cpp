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

#include "common.hpp"

/*
	Zeichne den Regeln-Screen.
*/
static void Draw() {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
	C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));

	GFX::DrawBaseTop();
	Gui::Draw_Rect(0, 0, 400, 25, C2D_Color32(0, 130, 130, 255));
	Gui::Draw_Rect(0, 215, 400, 25, C2D_Color32(0, 130, 130, 255));

	Gui::DrawStringCentered(0, 2, 0.7f, C2D_Color32(255, 255, 255, 255), Lang::get("RULES"), 390);
	Gui::DrawStringCentered(0, 30, 0.5f, C2D_Color32(255, 255, 255, 255), Lang::get("RULES_INSTR"), 390, 170);
	Gui::DrawStringCentered(0, 215, 0.7f, C2D_Color32(255, 255, 255, 255), Lang::get("A_CONTINUE"), 390);

	GFX::DrawBaseBottom();
	C3D_FrameEnd(0);
}

/*
	Zeige den Regeln-Screen.
*/
void Overlays::RulesOverlay() {
	bool doOut = false;

	while(!doOut) {
		Draw();

		hidScanInput();

		if (hidKeysDown()) doOut = true;
	}
}