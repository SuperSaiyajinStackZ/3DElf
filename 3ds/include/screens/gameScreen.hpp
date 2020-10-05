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

#ifndef _3DELF_GAME_SCREEN_HPP
#define _3DELF_GAME_SCREEN_HPP

#include "common.hpp"
#include "game.hpp"
#include "structs.hpp"

#include <vector>

class GameScreen : public Screen {
public:
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
	GameScreen(uint8_t pAmount = 2);
private:
	/* Zeichen-Utilities. */
	void DrawPlayerCards(void) const;
	void DrawTable(void) const;

	/* Logik-Utilities. */
	void pageHandle(bool fw);
	std::pair<bool, bool> DoPlayMove();
	bool checkPlay();
	void AILogic();
	void NextPHandle();
	bool checkSpecificCard(CardType CT, CardColor CC) const;
	void forceElevenCheck();

	std::unique_ptr<Game> currentGame = nullptr; // Der Spiel-Zeiger.
	bool forcePlay = true, forceEleven = false, isSub = false;
	int subSel = 0;

	const std::vector<Structs::ButtonPos> CardPos = {
		{ 20 + (0 * 60), 25, 40, 60 },
		{ 20 + (1 * 60), 25, 40, 60 },
		{ 20 + (2 * 60), 25, 40, 60 },
		{ 20 + (3 * 60), 25, 40, 60 },
		{ 20 + (4 * 60), 25, 40, 60 },

		{ 20 + (0 * 60), 95, 40, 60 },
		{ 20 + (1 * 60), 95, 40, 60 },
		{ 20 + (2 * 60), 95, 40, 60 },
		{ 20 + (3 * 60), 95, 40, 60 },
		{ 20 + (4 * 60), 95, 40, 60 },

		{ 20 + (0 * 60), 165, 40, 60 },
		{ 20 + (1 * 60), 165, 40, 60 },
		{ 20 + (2 * 60), 165, 40, 60 },
		{ 20 + (3 * 60), 165, 40, 60 },
		{ 20 + (4 * 60), 165, 40, 60 }
	};

	const std::vector<Structs::ButtonPos> subBtn = {
		{ 90, 10, 140, 40 },
		{ 90, 55, 140, 40 },
		{ 90, 100, 140, 40 },
		{ 90, 145, 140, 40 },
		{ 90, 190, 140, 40 }
	};

};

#endif