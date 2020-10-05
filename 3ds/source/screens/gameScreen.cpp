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

#include "gameScreen.hpp"

extern bool exiting;
extern bool touching(touchPosition touch, Structs::ButtonPos button);
#define MAX_CARDS 15

/*
	Initialisiere den Spiel-Screen.

	uint8_t pAmount: Die Spieleranzahl.
*/
GameScreen::GameScreen(uint8_t pAmount) {
	CoreHelper::GenerateSeed();
	this->currentGame = std::make_unique<Game>(pAmount);
	this->useAI = Msg::promptMsg(Lang::get("PLAY_AGAINST_COMPUTER"));

	this->forceElevenCheck();
}

/*
	Zeigt die Spielerkarten an.
*/
void GameScreen::DrawPlayerCards(void) const {
	uint8_t index2 = 0;
	for (uint8_t i = 0 + (this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * MAX_CARDS);
		i < this->currentGame->GetPlayerHandSize(this->currentGame->GetCurrentPlayer()); i++) {
		index2++;

		/* Falls der Kartenindex 15 oder kleiner ist. */
		if (index2 < MAX_CARDS + 1) {
			GFX::DrawCard(this->currentGame->GetPlayerCard(this->currentGame->GetCurrentPlayer(), i),
				CardPos[index2 - 1].x, CardPos[index2 - 1].y,
				CardPos[index2 - 1].w, CardPos[index2 - 1].h, false);
		}
	}

	/* Selektor part. */
	if (this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) < MAX_CARDS) {
		if (this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) < MAX_CARDS + 1) {
			Gui::drawAnimatedSelector(CardPos[this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer())].x,
				CardPos[this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer())].y,
				CardPos[this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer())].w,
				CardPos[this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer())].h,
					.020f, C2D_Color32(0, 0, 0, 255));
		}

	} else {
		if (index2 < MAX_CARDS + 1) {
			Gui::drawAnimatedSelector(CardPos[this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) - (this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * MAX_CARDS)].x,
				CardPos[this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) - (this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * MAX_CARDS)].y,
				CardPos[this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) - (this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * MAX_CARDS)].w,
				CardPos[this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) - (this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * MAX_CARDS)].h,
				.020f, C2D_Color32(0, 0, 0, 255));
		}
	}
}

/*
	Zeige die Tischkarten an.
*/
void GameScreen::DrawTable(void) const {
	std::pair<CardType, CardType> tempCards = { CardType::NUMBER_EMPTY, CardType::NUMBER_EMPTY };

	/* Rot als erstes. */
	tempCards = this->currentGame->getTableCard(CardColor::COLOR_RED);

	if (tempCards.first != CardType::NUMBER_EMPTY) {
		GFX::DrawCard2(CardType::NUMBER_11, CardColor::COLOR_RED, 175, 30, 40, 40, true);

		if (tempCards.first != CardType::NUMBER_11) {
			GFX::DrawCard2(tempCards.first, CardColor::COLOR_RED, 125, 30, 40, 40, true);
		}

		if (tempCards.second != CardType::NUMBER_11) {
			GFX::DrawCard2(tempCards.second, CardColor::COLOR_RED, 225, 30, 40, 40, true);
		}
	}

	/* Gelb als zweites. */
	tempCards = this->currentGame->getTableCard(CardColor::COLOR_YELLOW);

	if (tempCards.first != CardType::NUMBER_EMPTY) {
		GFX::DrawCard2(CardType::NUMBER_11, CardColor::COLOR_YELLOW, 175, 75, 40, 40, true);

		if (tempCards.first != CardType::NUMBER_11) {
			GFX::DrawCard2(tempCards.first, CardColor::COLOR_YELLOW, 125, 75, 40, 40, true);
		}

		if (tempCards.second != CardType::NUMBER_11) {
			GFX::DrawCard2(tempCards.second, CardColor::COLOR_YELLOW, 225, 75, 40, 40, true);
		}
	}

	/* Grün als drittes. */
	tempCards = this->currentGame->getTableCard(CardColor::COLOR_GREEN);

	if (tempCards.first != CardType::NUMBER_EMPTY) {
		GFX::DrawCard2(CardType::NUMBER_11, CardColor::COLOR_GREEN, 175, 120, 40, 40, true);

		if (tempCards.first != CardType::NUMBER_11) {
			GFX::DrawCard2(tempCards.first, CardColor::COLOR_GREEN, 125, 120, 40, 40, true);
		}

		if (tempCards.second != CardType::NUMBER_11) {
			GFX::DrawCard2(tempCards.second, CardColor::COLOR_GREEN, 225, 120, 40, 40, true);
		}
	}

	/* Blau als letztes. */
	tempCards = this->currentGame->getTableCard(CardColor::COLOR_BLUE);

	if (tempCards.first != CardType::NUMBER_EMPTY) {
		GFX::DrawCard2(CardType::NUMBER_11, CardColor::COLOR_BLUE, 175, 165, 40, 40, true);

		if (tempCards.first != CardType::NUMBER_11) {
			GFX::DrawCard2(tempCards.first, CardColor::COLOR_BLUE, 125, 165, 40, 40, true);
		}

		if (tempCards.second != CardType::NUMBER_11) {
			GFX::DrawCard2(tempCards.second, CardColor::COLOR_BLUE, 225, 165, 40, 40, true);
		}
	}
}

/*
	Der Haupt-Zeichnung's teil.
*/
void GameScreen::Draw(void) const {
	if (!this->isSub) {
		GFX::DrawBaseTop();
		Gui::Draw_Rect(0, 0, 400, 25, C2D_Color32(0, 130, 130, 255));
		Gui::Draw_Rect(0, 215, 400, 25, C2D_Color32(0, 130, 130, 255));
		this->DrawTable();
		GFX::DrawBaseBottom();
		this->DrawPlayerCards();

	} else {
		GFX::DrawBaseTop();
		Gui::Draw_Rect(0, 0, 400, 25, C2D_Color32(0, 130, 130, 255));
		Gui::Draw_Rect(0, 215, 400, 25, C2D_Color32(0, 130, 130, 255));
		Gui::DrawStringCentered(0, 1, 0.7f, C2D_Color32(255, 255, 255, 255), Lang::get("GAME_PAUSED"));
		Gui::DrawStringCentered(0, 215, 0.7f, C2D_Color32(255, 255, 255, 255), Lang::get("B_BACK"), 390);
		GFX::DrawBaseBottom();

		for (int i = 0; i < 4; i++) {
			if (this->subSel == i) Gui::drawAnimatedSelector(this->subBtn[i].x, this->subBtn[i].y, 140, 40, .030f, C2D_Color32(0, 222, 222, 255), C2D_Color32(0, 130, 130, 255));
			else Gui::Draw_Rect(this->subBtn[i].x, this->subBtn[i].y, this->subBtn[i].w, this->subBtn[i].h, C2D_Color32(0, 130, 130, 255));
		}

		Gui::DrawStringCentered(0, this->subBtn[0].y + 10, 0.6f, C2D_Color32(255, 255, 255, 255), Lang::get("LOAD_GAME"));
		Gui::DrawStringCentered(0, this->subBtn[1].y + 10, 0.6f, C2D_Color32(255, 255, 255, 255), Lang::get("SAVE_GAME"));
		Gui::DrawStringCentered(0, this->subBtn[2].y + 10, 0.6f, C2D_Color32(255, 255, 255, 255), Lang::get("EXIT_GAME"));
		Gui::DrawStringCentered(0, this->subBtn[3].y + 10, 0.6f, C2D_Color32(255, 255, 255, 255), Lang::get("SHOW_RULES"));
	}
}

/*
	Handle die Seiten logik.

	bool fw: Vorwärts (true), Rückwärts (false).
*/
void GameScreen::pageHandle(bool fw) {
	/* Falls Vorwärts | forward. */
	if (fw) {
		if (15 + ((this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * 15)) <
			this->currentGame->GetPlayerHandSize(this->currentGame->GetCurrentPlayer())) {

			this->currentGame->SetPageIndex(this->currentGame->GetCurrentPlayer(),
				this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) + 1);

			this->currentGame->SetCardIndex(this->currentGame->GetCurrentPlayer(),
				this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * 15);
		}

	/* Ansonsten Rückwärts | backward. */
	} else {
		if (this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) > 0) {

			this->currentGame->SetPageIndex(this->currentGame->GetCurrentPlayer(),
			this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) - 1);

			this->currentGame->SetCardIndex(this->currentGame->GetCurrentPlayer(),
				this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * 15);
		}
	}
}

/*
	Die HauptLogik des Spiel-Screen's.
*/
void GameScreen::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	/* Falls im Unter-Menü. */
	if (this->isSub) {
		if (hDown & KEY_B) this->isSub = false;

		if (hDown & KEY_DOWN) {
			if (this->subSel < 3) this->subSel++;
		}

		if (hDown & KEY_UP) {
			if (this->subSel > 0) this->subSel--;
		}

		if (hDown & KEY_A) {
			switch(this->subSel) {
				case 0:
					if (Msg::promptMsg(Lang::get("LOAD_FROM_FILE_PROMPT"))) {
						this->currentGame->LoadGameFromFile();
						if (this->currentGame->validLoaded()) {
							Msg::DisplayMsg(Lang::get("PREPARE_GAME"));
							this->currentGame->convertDataToGame();
							this->forceElevenCheck(); // Setze den Check hier.

							if (this->currentGame->GetDrawAmount() == 3) {
								this->forcePlay = false; // Weil wir bereits 3 mal gezogen haben.
							}

							this->isSub = false;

						} else {
							Msg::DisplayWaitMsg(Lang::get("NOT_VALID_GAME"));
							return;
						}
					}
					break;

				case 1:
					if (Msg::promptMsg(Lang::get("SAVE_TO_FILE_PROMPT"))) {
						this->currentGame->SaveToFile(true);
						Msg::DisplayWaitMsg(Lang::get("SAVED_TO_FILE"));
						this->isSub = false;
					}
					break;

				case 2:
					if (Msg::promptMsg(Lang::get("EXIT_GAME_PRMPT"))) {
						exiting = true;
					}
					break;

				case 3:
					Overlays::RulesOverlay();
					break;
			}
		}

		if (hDown & KEY_TOUCH) {
			if (touching(touch, this->subBtn[0])) {
				if (Msg::promptMsg(Lang::get("LOAD_FROM_FILE_PROMPT"))) {
					this->currentGame->LoadGameFromFile();
					if (this->currentGame->validLoaded()) {
						Msg::DisplayMsg(Lang::get("PREPARE_GAME"));
						this->currentGame->convertDataToGame();
						this->forceElevenCheck(); // Setze den Check hier.

						if (this->currentGame->GetDrawAmount() == 3) {
							this->forcePlay = false; // Weil wir bereits 3 mal gezogen haben.
						}

						this->isSub = false;

					} else {
						Msg::DisplayWaitMsg(Lang::get("NOT_VALID_GAME"));
						return;
					}
				}

			} else if (touching(touch, this->subBtn[1])) {
				if (Msg::promptMsg(Lang::get("SAVE_TO_FILE_PROMPT"))) {
					this->currentGame->SaveToFile(true);
					Msg::DisplayWaitMsg(Lang::get("SAVED_TO_FILE"));
					this->isSub = false;
				}

			} else if (touching(touch, this->subBtn[2])) {
				if (Msg::promptMsg(Lang::get("EXIT_GAME_PRMPT"))) {
					exiting = true;
				}

			} else if (touching(touch, this->subBtn[3])) {
				Overlays::RulesOverlay();
			}
		}

	/* Falls im Spiel. */
	} else {
		if (this->currentGame->GetCurrentPlayer() != 0) {
			if (this->useAI) {
				this->AILogic();
			}
		}

		/* Navigation nach Rechts. */
		if (hDown & KEY_RIGHT) {
			if (this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) + 1 <
				this->currentGame->GetPlayerHandSize(this->currentGame->GetCurrentPlayer())) {

				switch(this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer())) {
					case 4:
					case 9:
					case 14:
					case 29:
					case 34:
					case 39:
					case 44:
					case 49:
					case 54:
					case 59:
					case 64:
					case 69:
					case 74:
						return;
				}

				this->currentGame->SetCardIndex(this->currentGame->GetCurrentPlayer(),
					this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) + 1);
			}
		}

		/* Navigation nach Links. */
		if (hDown & KEY_LEFT) {
			if (this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) - 1 >= 0) {

				switch(this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer())) {
					case 0:
					case 5:
					case 10:
					case 15:
					case 20:
					case 25:
					case 30:
					case 35:
					case 40:
					case 45:
					case 50:
					case 55:
					case 60:
					case 65:
					case 70:
					case 75:
					case 80:
						return;
				}

				this->currentGame->SetCardIndex(this->currentGame->GetCurrentPlayer(),
					this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) - 1);
			}
		}

		/* Navigation zur nächsten Seite. */
		if (hDown & KEY_R) {
			this->pageHandle(true);
		}

		/* Navigation zur vorherigen Seite. */
		if (hDown & KEY_L) {
			this->pageHandle(false);
		}

		/* Navigation nach Unten. */
		if (hDown & KEY_DOWN) {
			if (this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) + 5 <
				this->currentGame->GetPlayerHandSize(this->currentGame->GetCurrentPlayer())) {

				if (this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) + 5 <
					15 + (this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * 15)) {

					this->currentGame->SetCardIndex(this->currentGame->GetCurrentPlayer(),
						this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) + 5);
				}
			}
		}

		/* Navigation nach Oben. */
		if (hDown & KEY_UP) {
			if ((this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) - 5) >= 0) {

				if ((this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) - 5) >=
				(0 + this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * 15)) {

					this->currentGame->SetCardIndex(this->currentGame->GetCurrentPlayer(),
						this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) - 5);
				}
			}
		}

		/* Spiel-Logik. */
		if (hDown & KEY_A) {
			if (!this->DoPlayMove().second) {
				if (!exiting) this->NextPHandle();
			}
		}

		/* Touch Berührung's Logik und spiel. */
		if (hDown & KEY_TOUCH) {
			for (int i = 0; i < 15; i++) {
				if (touching(touch, this->CardPos[i])) {
					if (i + (this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * 15) <
						this->currentGame->GetPlayerHandSize(this->currentGame->GetCurrentPlayer())) {

							this->currentGame->SetCardIndex(this->currentGame->GetCurrentPlayer(),
								i + (this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * 15));

							if (!this->DoPlayMove().second) {
								if (!exiting) this->NextPHandle();
							}
					}
				}
			}
		}

		/* Karten-Zieh Logik. */
		if (hDown & KEY_X) {
			if (this->forceEleven) {
				Msg::DisplayWaitMsg(Lang::get("FORCE_ELEVEN"));
				return;
			}

			if (this->currentGame->GetDeckSize() > 0) {
				if (this->currentGame->GetDrawAmount() < 3) {
					this->currentGame->AddPlayerCard(this->currentGame->GetCurrentPlayer());
					this->forceElevenCheck();

					if (this->currentGame->GetDrawAmount() == 3) {
						this->forcePlay = false; // Weil wir bereits 3 mal gezogen haben.

						if (!this->checkPlay()) {
							this->NextPHandle();
						}
					}

				} else {
					Msg::DisplayWaitMsg(Lang::get("ONLY_3_CARDS"));
				}

			} else {
				Msg::DisplayWaitMsg(Lang::get("DECK_ALREADY_EMPTY"));
			}
		}

		/* Spieler-Wechsel Logik. */
		if (hDown & KEY_Y) {
			if (this->forceEleven) {
				Msg::DisplayWaitMsg(Lang::get("FORCE_ELEVEN"));
				return;
			}

			if (this->currentGame->GetDeckSize() > 0) {
				if (this->forcePlay) {
					Msg::DisplayWaitMsg(Lang::get("GAME_PRMPT_1"));
					return;
				}

			} else {
				if (this->forcePlay) {
					if (this->checkPlay()) {
						Msg::DisplayWaitMsg(Lang::get("GAME_PRMPT_2"));
						return;
					}
				}
			}

			this->NextPHandle();
		}

		if (hHeld & KEY_SELECT) {
			Msg::HelperBox(Lang::get("GAME_INSTR"));
		}

		if (hDown & KEY_START) this->isSub = true;
	}
}

void GameScreen::NextPHandle() {
	/* Nächster Spieler handle. */
	if (this->currentGame->GetCurrentPlayer() < this->currentGame->GetPlayerAmount() - 1) {
		char msg[100];
		snprintf(msg, sizeof(msg), Lang::get("NEXT_PLAYER").c_str(), this->currentGame->GetCurrentPlayer() + 1, this->currentGame->GetCurrentPlayer() + 2);
		Msg::DisplayWaitMsg(msg);

		this->currentGame->SetCurrentPlayer(this->currentGame->GetCurrentPlayer() + 1);
		this->currentGame->ResetDrawAmount();
		this->forceElevenCheck();
		this->forcePlay = true;

	} else {
		char msg[100];
		snprintf(msg, sizeof(msg), Lang::get("NEXT_PLAYER").c_str(), this->currentGame->GetCurrentPlayer() + 1, 1);
		Msg::DisplayWaitMsg(msg);

		this->currentGame->SetCurrentPlayer(0);
		this->currentGame->ResetDrawAmount();
		this->forceElevenCheck();
		this->forcePlay = true;
	}
}

/*
	Die Haupt-Spiel Logik.

	wiedergibt einen std::pair aus booleans mit:
	first: Ob die Karte gültig war.
	second: Ob der Spieler noch spielen kann.
*/
std::pair<bool, bool> GameScreen::DoPlayMove() {
	std::pair<bool, bool> results = { false, true };

	const CardStruct CS = this->currentGame->GetPlayerCard(this->currentGame->GetCurrentPlayer(), this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()));
	const bool isUpper = (uint8_t)CS.CT >= 12 ? true : false; // 12 + wäre die obere Karte.

	if (this->currentGame->CanPlay(CS.CC, isUpper, CS.CT)) {
		results.first = true;
		this->currentGame->RemovePlayerCard(this->currentGame->GetCurrentPlayer(), this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()));
		this->currentGame->SetCard(CS.CC, isUpper, CS.CT);

		this->forcePlay = false; // Wir sind nicht mehr gezwungen hier in dem fall.

		/* Falls der Index größer als die anzahl der Karten der Hand ist.. gehe zur ersten position der ersten seite. */
		if (this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer() > this->currentGame->GetPlayerHandSize(this->currentGame->GetCurrentPlayer() - 1))) {
			this->currentGame->SetCardIndex(this->currentGame->GetCurrentPlayer(), 0);
			this->currentGame->SetPageIndex(this->currentGame->GetCurrentPlayer(), 0);
		}

		/* 0 Karten auf der Hand -- Gewonnen. */
		if (this->currentGame->GetPlayerHandSize(this->currentGame->GetCurrentPlayer()) == 0) {
			char msg[100];
			snprintf(msg, sizeof(msg), Lang::get("PLAYER_WON").c_str(), this->currentGame->GetCurrentPlayer() + 1);
			Msg::DisplayWaitMsg(msg);

			exiting = true;
			return { false, false };
		}

		this->forceElevenCheck();

		results.second = this->checkPlay();
	}

	return results;
}

/*
	Überprüfe, ob ein Spieler spielen kann.
*/
bool GameScreen::checkPlay() {
	for (uint8_t i = 0; i < this->currentGame->GetPlayerHandSize(this->currentGame->GetCurrentPlayer()); i++) {
		const CardStruct CS = this->currentGame->GetPlayerCard(this->currentGame->GetCurrentPlayer(), i);
		const bool isUpper = (uint8_t)CS.CT >= 12 ? true : false; // 12 + wäre die obere Karte.

		if (this->currentGame->CanPlay(CS.CC, isUpper, CS.CT)) {
			return true; // Weil wir fortfahren können --> Beende die runde nicht!
		}
	}

	return false;
}

/*
	Überprüfe, ob eine bestimmte Karte gespielt werden kann von der Spielerhand.

	CardType CT: Der Kartentyp, welcher überprüft werden soll.
	CardColor CC: Die Kartenfarbe, welche überprüft werden soll.
*/
bool GameScreen::checkSpecificCard(CardType CT, CardColor CC) const {
	for (uint8_t i = 0; i < this->currentGame->GetPlayerHandSize(this->currentGame->GetCurrentPlayer()); i++) {
		const CardStruct CS = this->currentGame->GetPlayerCard(this->currentGame->GetCurrentPlayer(), i);

		if ((CS.CT == CT) && (CS.CC == CC)) return true;
	}

	return false;
}

/*
	Gegner Logik hier.
*/
void GameScreen::AILogic() {
	bool doOut = false;
	bool canPlay = false;

	while(!doOut) {
		for (uint8_t i = 0; i < this->currentGame->GetPlayerHandSize(this->currentGame->GetCurrentPlayer()); i++) {
			const CardStruct CS = this->currentGame->GetPlayerCard(this->currentGame->GetCurrentPlayer(), i);
			const bool isUpper = (uint8_t)CS.CT >= 12 ? true : false; // 12 + wäre die obere Karte.

			if (this->currentGame->CanPlay(CS.CC, isUpper, CS.CT)) {
				this->currentGame->SetCardIndex(this->currentGame->GetCurrentPlayer(), i);
				canPlay = true;
				break;
			}
		}

		if (canPlay) {
			if (!this->DoPlayMove().second) {
				doOut = true;
			}
		}

		if (!canPlay) {
			if (this->currentGame->GetDeckSize() > 0) {
				if (this->currentGame->GetDrawAmount() < 3) {
					this->currentGame->AddPlayerCard(this->currentGame->GetCurrentPlayer());

					if (this->currentGame->GetDrawAmount() == 3) {
						this->forcePlay = false; // Weil wir bereits 3 mal gezogen haben.
						doOut = true;
					}
				}
			}
		}
	}

	if (!exiting) this->NextPHandle();
}

/*
	Falls eine 11 auf der Spielerhand existiert, zwinge diese karte.
*/
void GameScreen::forceElevenCheck() {
	this->forceEleven = false;

	/* Überprüfe Rote Karte zuerst. */
	if (this->currentGame->getTableCard(CardColor::COLOR_RED).first == CardType::NUMBER_EMPTY) {
		if (this->checkSpecificCard(CardType::NUMBER_11, CardColor::COLOR_RED)) {
			//Msg::DisplayWaitMsg("Rote Elf wurde gezwungen.");
			this->forceEleven = true;
			return;
		}
	}

	/* Dann überprüfe Gelb. */
	if (this->currentGame->getTableCard(CardColor::COLOR_YELLOW).first == CardType::NUMBER_EMPTY) {
		if (this->checkSpecificCard(CardType::NUMBER_11, CardColor::COLOR_YELLOW)) {
			//Msg::DisplayWaitMsg("Gelbe Elf wurde gezwungen.");
			this->forceEleven = true;
			return;
		}
	}

	/* Dann überprüfe Grün. */
	if (this->currentGame->getTableCard(CardColor::COLOR_GREEN).first == CardType::NUMBER_EMPTY) {
		if (this->checkSpecificCard(CardType::NUMBER_11, CardColor::COLOR_GREEN)) {
			//Msg::DisplayWaitMsg("Grüne Elf wurde gezwungen.");
			this->forceEleven = true;
			return;
		}
	}

	/* Und als letztes... überprüfe Blau. */
	if (this->currentGame->getTableCard(CardColor::COLOR_BLUE).first == CardType::NUMBER_EMPTY) {
		if (this->checkSpecificCard(CardType::NUMBER_11, CardColor::COLOR_BLUE)) {
			//Msg::DisplayWaitMsg("Blaue Elf wurde gezwungen.");
			this->forceEleven = true;
			return;
		}
	}
}