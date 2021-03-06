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

static void Draw() {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
	C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));

	GFX::DrawBaseTop();
	Gui::Draw_Rect(0, 0, 400, 25, BAR_COLOR);
	Gui::Draw_Rect(0, 215, 400, 25, BAR_COLOR);

	GFX::DrawSprite(sprites_stackZ_idx, 2, 75);
	GFX::DrawSprite(sprites_Logo_idx, 140, 56);

	Gui::DrawStringCentered(0, 1, 0.6f, TEXT_COLOR, Lang::get("CREDITS"));
	Gui::DrawStringCentered(0, 30, 0.6f, TEXT_COLOR, Lang::get("DEV_BY"), 390);
	Gui::DrawStringCentered(0, 217, 0.6f, TEXT_COLOR, Lang::get("CURRENT_VERSION") + std::string(V_STRING), 390);

	GFX::DrawBaseBottom();
	Gui::Draw_Rect(0, 0, 320, 25, BAR_COLOR);
	Gui::Draw_Rect(0, 215, 320, 25, BAR_COLOR);

	Gui::DrawStringCentered(0, 28, 0.7f, TEXT_COLOR, "devkitPro", 310, 0);
	Gui::DrawStringCentered(0, 48, 0.6f, TEXT_COLOR, Lang::get("DEVKITPRO"), 310, 0);
	Gui::DrawStringCentered(0, 78, 0.7f, TEXT_COLOR, "SuperSaiyajinStackZ", 310, 0);
	Gui::DrawStringCentered(0, 98, 0.6f, TEXT_COLOR, Lang::get("DEVELOPING_APP"), 310, 0);
	Gui::DrawStringCentered(0, 128, 0.7f, TEXT_COLOR, "Universal-Team", 310, 0);
	Gui::DrawStringCentered(0, 148, 0.6f, TEXT_COLOR, Lang::get("UNIVERSAL_CORE"), 310, 0);
	C3D_FrameEnd(0);
}

void Overlays::CreditsOverlay() {
	bool doOut = false;

	while(!doOut) {
		Draw();

		hidScanInput();

		if (hidKeysDown()) doOut = true;
	}
}