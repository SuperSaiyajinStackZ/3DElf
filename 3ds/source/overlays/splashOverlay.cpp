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

#define _SPLASH_X_LOGO_POS 140
#define _SPLASH_LOGO_INIT_DELAY 50
#define _SPLASH_WAIT_DELAY 200

/*
	Zeichne den Splash-Screen.

	const int &logoPos: Die Position des 3DElf's Logo.
*/
static void Draw(const int &logoPos) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, NO_COLOR);
	C2D_TargetClear(Bottom, NO_COLOR);

	GFX::DrawBaseTop();
	Gui::Draw_Rect(0, 0, 400, 25, BAR_COLOR);
	Gui::Draw_Rect(0, 215, 400, 25, BAR_COLOR);

	Gui::DrawStringCentered(0, 1, 0.7f, TEXT_COLOR, Lang::get("STACKZ_PRESENTS"));
	GFX::DrawSprite(sprites_stackZ_idx, 2, 75);
	if (logoPos < 400) GFX::DrawSprite(sprites_Logo_idx, logoPos, 56);
	Gui::DrawStringCentered(0, 217, 0.7f, TEXT_COLOR, "2020 - 2020", 390);

	GFX::DrawBaseBottom();
	GFX::DrawSprite(sprites_universal_core_idx, 0, 26);

	C3D_FrameEnd(0);
}

/*
	Zeige den Splash-Screen.
*/
void Overlays::SplashOverlay() {
	int delay = _SPLASH_WAIT_DELAY, logoPos = 402, swipeDelay = _SPLASH_LOGO_INIT_DELAY;
	bool doOut = false, swipedIn = false, doSwipe = false;

	while(!doOut) {
		Draw(logoPos);

		hidScanInput();

		if (hidKeysDown()) doOut = true;

		/* Als erstes die Initiale Overlay Verzögerung. */
		if (!swipedIn) {
			if (swipeDelay > 0) {
				swipeDelay--;

				if (swipeDelay == 0) {
					doSwipe = true;
				}
			}
		}

		/* Dann die Logo Animation. */
		if (doSwipe) {
			if (logoPos > _SPLASH_X_LOGO_POS) {
				logoPos--;

				if (logoPos == _SPLASH_X_LOGO_POS) {
					swipedIn = true;
				}
			}
		}

		/* Dann die restliche Logik. */
		if (swipedIn) {
			if (delay > 0) {
				delay--;

				/* Falls Delay == 0, verlasse das Overlay. */
				if (delay == 0) doOut = true;
			}
		}
	}
}