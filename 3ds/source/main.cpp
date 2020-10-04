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
#include "gameScreen.hpp"
#include <3ds.h>
#include <dirent.h>

bool exiting = false;
C2D_SpriteSheet sprites;
touchPosition touch;

/*
	Falls eine bestimmte position berührt wird.. mache etwas.

	touchPosition touch: Die touchPosition variable. In der regel als "touch" angegeben.
	Structs::ButtonPos pos: Der strukt.
*/
bool touching(touchPosition touch, Structs::ButtonPos pos) {
	if (touch.px >= pos.x && touch.px <= (pos.x + pos.w) && touch.py >= pos.y && touch.py <= (pos.y + pos.h)) return true;
	return false;
}

/*
	Initialisiere 3DElf.
*/
static void init() {
	romfsInit();
	gfxInitDefault();
	Gui::init();

	Lang::load(0); // Lade die Übersetzungen.

	mkdir("sdmc:/3ds", 0x777);
	mkdir("sdmc:/3ds/3DElf", 0x777);
	Gui::loadSheet("romfs:/gfx/sprites.t3x", sprites);

	Overlays::SplashOverlay();
	Gui::setScreen(std::make_unique<GameScreen>(), false, true);
}

/*
	Die Hauptfunktion.
*/
int main() {
	init();

	while(aptMainLoop() && !exiting) {
		hidScanInput();
		touchRead(&touch);
		uint32_t hDown = hidKeysDown();
		uint32_t hHeld = hidKeysHeld();

		Gui::clearTextBufs();
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));

		Gui::DrawScreen(true);
		Gui::ScreenLogic(hDown, hHeld, touch, true, true);
		C3D_FrameEnd(0);
	}

	Gui::exit();
	Gui::unloadSheet(sprites);
	romfsExit();
	gfxExit();

	return 0;
}