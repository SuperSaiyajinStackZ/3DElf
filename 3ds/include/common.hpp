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

#ifndef _3DELF_COMMON_HPP
#define _3DELF_COMMON_HPP

#define PLAYER_CARD_OUTLINE_SIZE 5
#define TABLE_CARD_OUTLINE_SIZE 4

/* Hier sind alle notwendigen Headers gelistet. */
#include "gfx.hpp"
#include "kbd.hpp"
#include "lang.hpp"
#include "msg.hpp"
#include "overlay.hpp"
#include "screenCommon.hpp"
#include "settings.hpp"
#include <3ds.h>

extern std::unique_ptr<Settings> konfiguration;

#endif