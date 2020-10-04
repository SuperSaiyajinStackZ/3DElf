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
	Zeichne den Splash-Screen.
*/
static void Draw() {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
	C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));

	Gui::ScreenDraw(Top);
	GFX::DrawSprite(sprites_dev_by_idx, 0, 0);
	Gui::ScreenDraw(Bottom);
	GFX::DrawSprite(sprites_universal_core_idx, 0, 0);
	C3D_FrameEnd(0);
}

/*
	Zeige den Splash-Screen.
*/
void Overlays::SplashOverlay() {
	int delay = 255;
	bool doOut = false;

	while(!doOut) {
		Draw();

		hidScanInput();

		if (hidKeysDown()) doOut = true;

		/* Falls der Delay größer als 0 ist, reduziere es jede frame. */
		if (delay > 0) {
			delay--;

			/* Falls Delay == 0, verlasse das Overlay. */
			if (delay == 0) doOut = true;
		}
	}
}