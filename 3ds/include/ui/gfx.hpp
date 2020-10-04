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

namespace GFX {
	/* Basiszeug. */
	void DrawBaseTop();
	void DrawBaseBottom();

	/* Kartenzeug. */
	void DrawCardOutline(int xPos, int yPos, float Width = 60, float Height = 80, uint32_t color = C2D_Color32(255, 255, 255, 255));
	void DrawCard(CardStruct CS, int x, int y, float xSize = 60, float ySize = 80, bool top = true);
	void DrawCard2(CardType CT, CardColor CC, int x, int y, float xSize = 60, float ySize = 80, bool top = true);

	/* Spritezeug. */
	void DrawSprite(int index, int x, int y, float ScaleX = 1, float ScaleY = 1);
};

#endif