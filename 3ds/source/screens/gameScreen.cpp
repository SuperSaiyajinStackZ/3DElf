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

#include "gameScreen.hpp"

extern uint8_t fadeAlpha;
extern bool exiting;
extern bool touching(touchPosition touch, Structs::ButtonPos button);
#define MAX_CARDS 15

/*
	Initialisiere den Spiel-Screen.
*/
GameScreen::GameScreen() {
	CoreHelper::GenerateSeed();

	const uint8_t pAmount = KBD::SetAmount(6, Lang::get("ENTER_PLAYERAMOUNT"), 2);
	this->currentGame = std::make_unique<Game>(pAmount);
	this->currentGame->SetAI(Msg::promptMsg(Lang::get("PLAY_AGAINST_COMPUTER")));
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
			GFX::DrawCardStruct(this->currentGame->GetPlayerCard(this->currentGame->GetCurrentPlayer(), i),
				this->CardPos[index2 - 1].x, this->CardPos[index2 - 1].y,
				this->CardPos[index2 - 1].w, this->CardPos[index2 - 1].h, PLAYER_CARD_OUTLINE_SIZE,
				this->currentGame->Playable(this->currentGame->GetCurrentPlayer(), i));
		}
	}

	/* Selektor part. */
	if (this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) < MAX_CARDS) {
		if (this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) < MAX_CARDS + 1) {
			Gui::drawAnimatedSelector(this->CardPos[this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer())].x,
				this->CardPos[this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer())].y,
				this->CardPos[this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer())].w,
				this->CardPos[this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer())].h,
					.020f, CARD_SLT_COLOR);
		}

	} else {
		if (index2 < MAX_CARDS + 1) {
			Gui::drawAnimatedSelector(this->CardPos[this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) - (this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * MAX_CARDS)].x,
				this->CardPos[this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) - (this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * MAX_CARDS)].y,
				this->CardPos[this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) - (this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * MAX_CARDS)].w,
				this->CardPos[this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) - (this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * MAX_CARDS)].h,
				.020f, CARD_SLT_COLOR);
		}
	}
}

/*
	Zeige die Tischkarten an.
*/
void GameScreen::DrawTable(void) const {
	std::pair<CardType, CardType> tempCards = { CardType::NUMBER_EMPTY, CardType::NUMBER_EMPTY };

	/* Rot als erstes. */
	tempCards = this->currentGame->getTableCard(CardColor::COLOR_1);

	if (tempCards.first != CardType::NUMBER_EMPTY) {
		GFX::DrawCardSeparate(CardType::NUMBER_11, CardColor::COLOR_1, 175, 30);

		if (tempCards.first != CardType::NUMBER_11) GFX::DrawCardSeparate(tempCards.first, CardColor::COLOR_1, 125, 30);
		if (tempCards.second != CardType::NUMBER_11) GFX::DrawCardSeparate(tempCards.second, CardColor::COLOR_1, 225, 30);
	}

	/* Gelb als zweites. */
	tempCards = this->currentGame->getTableCard(CardColor::COLOR_2);

	if (tempCards.first != CardType::NUMBER_EMPTY) {
		GFX::DrawCardSeparate(CardType::NUMBER_11, CardColor::COLOR_2, 175, 75);

		if (tempCards.first != CardType::NUMBER_11) GFX::DrawCardSeparate(tempCards.first, CardColor::COLOR_2, 125, 75);
		if (tempCards.second != CardType::NUMBER_11) GFX::DrawCardSeparate(tempCards.second, CardColor::COLOR_2, 225, 75);
	}

	/* Grün als drittes. */
	tempCards = this->currentGame->getTableCard(CardColor::COLOR_3);

	if (tempCards.first != CardType::NUMBER_EMPTY) {
		GFX::DrawCardSeparate(CardType::NUMBER_11, CardColor::COLOR_3, 175, 120);

		if (tempCards.first != CardType::NUMBER_11) GFX::DrawCardSeparate(tempCards.first, CardColor::COLOR_3, 125, 120);
		if (tempCards.second != CardType::NUMBER_11) GFX::DrawCardSeparate(tempCards.second, CardColor::COLOR_3, 225, 120);
	}

	/* Blau als letztes. */
	tempCards = this->currentGame->getTableCard(CardColor::COLOR_4);

	if (tempCards.first != CardType::NUMBER_EMPTY) {
		GFX::DrawCardSeparate(CardType::NUMBER_11, CardColor::COLOR_4, 175, 165);

		if (tempCards.first != CardType::NUMBER_11) GFX::DrawCardSeparate(tempCards.first, CardColor::COLOR_4, 125, 165);
		if (tempCards.second != CardType::NUMBER_11) GFX::DrawCardSeparate(tempCards.second, CardColor::COLOR_4, 225, 165);
	}
}

/* Zeige das Spiel. */
void GameScreen::ShowGame(void) const {
	GFX::DrawBaseTop();
	Gui::Draw_Rect(0, 0, 400, 25, BAR_COLOR);
	Gui::Draw_Rect(0, 215, 400, 25, BAR_COLOR);
	Gui::DrawStringCentered(0, 1, 0.7f, TEXT_COLOR, Lang::get("GAME_SCREEN"));
	Gui::DrawStringCentered(0, 218, 0.6f, TEXT_COLOR, Lang::get("SELECT_INSTRUCTIONS"), 390);
	this->DrawTable();
	if (fadeAlpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, fadeAlpha));

	GFX::DrawBaseBottom();
	this->DrawPlayerCards();
	if (fadeAlpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, fadeAlpha));
}

/* Zeige das Unter-Menü. */
void GameScreen::ShowSub(void) const {
	GFX::DrawBaseTop();
	Gui::Draw_Rect(0, 0, 400, 25, BAR_COLOR);
	Gui::Draw_Rect(0, 215, 400, 25, BAR_COLOR);
	Gui::DrawStringCentered(0, 1, 0.7f, TEXT_COLOR, Lang::get("GAME_PAUSED"));

	/* Zeige Spiel-Informationen an. */
	Gui::DrawStringCentered(0, 30, 0.6f, TEXT_COLOR, Lang::get("COMPUTER_USED") + ": " +
							(this->currentGame->GetAI() ? Lang::get("YES") : Lang::get("NO")), 390);

	Gui::DrawStringCentered(0, 45, 0.6f, TEXT_COLOR, Lang::get("PLAYER_AMOUNT") + ": " +
							std::to_string(this->currentGame->GetPlayerAmount()), 390);

	Gui::DrawStringCentered(0, 60, 0.6f, TEXT_COLOR, Lang::get("CARD_DECK_REMAINING") + ": " +
							std::to_string(this->currentGame->GetDeckSize()), 390);

	Gui::DrawStringCentered(0, 75, 0.6f, TEXT_COLOR, Lang::get("CURRENT_PLAYER") +
							std::to_string(this->currentGame->GetCurrentPlayer() + 1), 390);

	for (uint8_t i = 0; i < this->currentGame->GetPlayerAmount(); i++) {
		Gui::DrawStringCentered(0, 100 + (i * 18), 0.6f, TEXT_COLOR, Lang::get("PLAYER") + " " +
		std::to_string(i + 1) + " " + Lang::get("CARD_AMOUNT") + ": " + std::to_string(this->currentGame->GetPlayerHandSize(i)), 390);
	}

	Gui::DrawStringCentered(0, 218, 0.6f, TEXT_COLOR, Lang::get("B_BACK"), 390);
	if (fadeAlpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, fadeAlpha));

	GFX::DrawBaseBottom();

	for (int i = 0; i < 10; i++) {
		if (this->subSel == i) Gui::drawAnimatedSelector(this->subBtn[i].x, this->subBtn[i].y, 140, 40, .030f, BUTTON_SELECTED, BUTTON_UNSELECTED);
		else Gui::Draw_Rect(this->subBtn[i].x, this->subBtn[i].y, this->subBtn[i].w, this->subBtn[i].h, BUTTON_UNSELECTED);
	}

	Gui::DrawStringCentered(-80, this->subBtn[0].y + 10, 0.6f, TEXT_COLOR, Lang::get("LOAD_GAME"), 135);
	Gui::DrawStringCentered(-80, this->subBtn[1].y + 10, 0.6f, TEXT_COLOR, Lang::get("SAVE_GAME"), 135);
	Gui::DrawStringCentered(-80, this->subBtn[2].y + 10, 0.6f, TEXT_COLOR, Lang::get("EXIT_GAME"), 135);
	Gui::DrawStringCentered(-80, this->subBtn[3].y + 10, 0.6f, TEXT_COLOR, Lang::get("SHOW_RULES"), 135);
	Gui::DrawStringCentered(-80, this->subBtn[4].y + 10, 0.6f, TEXT_COLOR, Lang::get("SHOW_CREDITS"), 135);

	Gui::DrawStringCentered(80, this->subBtn[5].y + 10, 0.6f, TEXT_COLOR, Lang::get("CHANGE_LANGUAGE"), 135);
	Gui::DrawStringCentered(80, this->subBtn[6].y + 10, 0.6f, TEXT_COLOR, Lang::get("NEW_GAME"), 135);
	Gui::DrawStringCentered(80, this->subBtn[7].y + 10, 0.6f, TEXT_COLOR, Lang::get("TOGGLE_COMPUTER"), 135);
	Gui::DrawStringCentered(80, this->subBtn[8].y + 10, 0.6f, TEXT_COLOR, Lang::get("PLAYER_AMOUNT"), 135);

	if (fadeAlpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, fadeAlpha));
}

/* Der Haupt-Zeichnung's teil. */
void GameScreen::Draw(void) const {
	if (!this->isSub) this->ShowGame();
	else this->ShowSub();
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

/* Die Unter-Menü Logik. */
void GameScreen::SubLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_B) this->isSub = false;

	if (hDown & KEY_DOWN) {
		if (this->subSel < 4) this->subSel++;
		else if (this->subSel > 4 && this->subSel < 9) this->subSel++;
	}

	if (hDown & KEY_UP) {
		if (this->subSel > 5) this->subSel--;
		else if (this->subSel < 5 && this->subSel > 0) this->subSel--;
	}

	if (hDown & KEY_RIGHT) {
		if (this->subSel < 5) this->subSel += 5;
	}

	if (hDown & KEY_LEFT) {
		if (this->subSel > 4) this->subSel -= 5;
	}

	if (hDown & KEY_A) {
		switch(this->subSel) {
			case 0:
				/* Spiel Laden. */
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
				/* Spiel Speichern. */
				if (Msg::promptMsg(Lang::get("SAVE_TO_FILE_PROMPT"))) {
					Msg::DisplayMsg(Lang::get("SAVING_GAME"));
					this->currentGame->SaveToFile(true);
					Msg::DisplayWaitMsg(Lang::get("SAVED_TO_FILE"));
					this->isSub = false;
				}
				break;

			case 2:
				/* Spiel Beenden. */
				if (Msg::promptMsg(Lang::get("EXIT_GAME_PRMPT"))) {
					exiting = true;
					this->isSub = false;
				}
				break;

			case 3:
				/* Regeln anzeigen. */
				Overlays::RulesOverlay();
				break;

			case 4:
				/* Credits anzeigen. */
				Overlays::CreditsOverlay();
				break;

			case 5:
				/* Sprache ändern. */
				Overlays::LanguageOverlay();
				break;

			case 6:
				/* Spiel Neustarten. */
				if (Msg::promptMsg(Lang::get("NEW_GAME_PRMPT"))) {
					Msg::DisplayMsg(Lang::get("PREPARE_GAME"));
					this->currentGame->InitNewGame(this->currentGame->GetPlayerAmount());
					this->forcePlay = true;
					this->forceElevenCheck(); // Setze den Check hier.
					this->isSub = false;
				}
				break;

			case 7:
				/* Computer De-/Aktivieren. */
				this->currentGame->SetAI(Msg::promptMsg(Lang::get("PLAY_AGAINST_COMPUTER")));
				break;

			case 8:
				/* Spieleranzahl verändern. */
				if (Msg::promptMsg(Lang::get("PLAYERAMOUNT_PRMPT"))) {
					this->currentGame->InitNewGame((uint8_t)KBD::SetAmount(6, Lang::get("ENTER_PLAYERAMOUNT"), this->currentGame->GetPlayerAmount()));
					this->forcePlay = true;
					this->forceElevenCheck(); // Setze den Check hier.
					this->isSub = false;
				}
				break;
		}
	}

	if (hDown & KEY_TOUCH) {
		/* Spiel Laden. */
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

		/* Spiel Speichern. */
		} else if (touching(touch, this->subBtn[1])) {
			if (Msg::promptMsg(Lang::get("SAVE_TO_FILE_PROMPT"))) {
				Msg::DisplayMsg(Lang::get("SAVING_GAME"));
				this->currentGame->SaveToFile(true);
				Msg::DisplayWaitMsg(Lang::get("SAVED_TO_FILE"));
				this->isSub = false;
			}

		/* Spiel Beenden. */
		} else if (touching(touch, this->subBtn[2])) {
			if (Msg::promptMsg(Lang::get("EXIT_GAME_PRMPT"))) {
				exiting = true;
				this->isSub = false;
			}

		/* Regeln anzeigen. */
		} else if (touching(touch, this->subBtn[3])) {
			Overlays::RulesOverlay();

		/* Credits anzeigen. */
		} else if (touching(touch, this->subBtn[4])) {
			Overlays::CreditsOverlay();

		/* Sprache ändern. */
		} else if (touching(touch, this->subBtn[5])) {
			Overlays::LanguageOverlay();

		/* Spiel Neustarten. */
		} else if (touching(touch, this->subBtn[6])) {
			if (Msg::promptMsg(Lang::get("NEW_GAME_PRMPT"))) {
				Msg::DisplayMsg(Lang::get("PREPARE_GAME"));
				this->currentGame->InitNewGame(this->currentGame->GetPlayerAmount());
				this->forcePlay = true;
				this->forceElevenCheck(); // Setze den Check hier.
				this->isSub = false;
			}

		/* Computer De-/Aktivieren. */
		} else if (touching(touch, this->subBtn[7])) {
			this->currentGame->SetAI(Msg::promptMsg(Lang::get("PLAY_AGAINST_COMPUTER")));

		/* Spieleranzahl ändern. */
		} else if (touching(touch, this->subBtn[8])) {
			if (Msg::promptMsg(Lang::get("PLAYERAMOUNT_PRMPT"))) {
				this->currentGame->InitNewGame((uint8_t)KBD::SetAmount(6, Lang::get("ENTER_PLAYERAMOUNT"), this->currentGame->GetPlayerAmount()));
				this->forcePlay = true;
				this->forceElevenCheck(); // Setze den Check hier.
				this->isSub = false;
			}
		}
	}
}

/* Die Spiel-Logik. */
void GameScreen::GameLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (this->currentGame->GetCurrentPlayer() != 0) {
		if (this->currentGame->GetAI()) this->AILogic();
	}

	/* Navigation nach Rechts. */
	if (hDown & KEY_RIGHT) {
		if (this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) + 1 < this->currentGame->GetPlayerHandSize(this->currentGame->GetCurrentPlayer())) {
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

			this->currentGame->SetCardIndex(this->currentGame->GetCurrentPlayer(), this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) + 1);
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

			this->currentGame->SetCardIndex(this->currentGame->GetCurrentPlayer(), this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) - 1);
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
		if (this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) + 5 < this->currentGame->GetPlayerHandSize(this->currentGame->GetCurrentPlayer())) {
			if (this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) + 5 < 15 + (this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * 15)) {
				this->currentGame->SetCardIndex(this->currentGame->GetCurrentPlayer(), this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) + 5);
			}
		}
	}

	/* Navigation nach Oben. */
	if (hDown & KEY_UP) {
		if ((this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) - 5) >= 0) {
			if ((this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) - 5) >= (0 + this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * 15)) {
				this->currentGame->SetCardIndex(this->currentGame->GetCurrentPlayer(), this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) - 5);
			}
		}
	}

	/* Spiel-Logik. */
	if (hDown & KEY_A) {
		/* Überprüfe ob Spielbar. */
		if (this->currentGame->Playable(this->currentGame->GetCurrentPlayer(), this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()))) {
			if (this->forceEleven) {
				/* Checke, ob diese Karte eine 11 ist. */
				if (this->currentGame->GetPlayerCard(this->currentGame->GetCurrentPlayer(), this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer())).CT != CardType::NUMBER_11) {
					Msg::DisplayWaitMsg(Lang::get("FORCE_ELEVEN"));
					return;
				}

				if (!this->checkProper11()) {
					Overlays::CardOrderOverlay();
					return;
				}
			}

			if (!this->DoPlayMove().second) {
				if (!this->gameOver) this->NextPHandle();
			}
		}
	}

	/* Touch Berührung's Logik und spiel. */
	if (hDown & KEY_TOUCH) {
		for (int i = 0; i < 15; i++) {
			if (touching(touch, this->CardPos[i])) {
				if (i + (this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * 15) < this->currentGame->GetPlayerHandSize(this->currentGame->GetCurrentPlayer())) {
					this->currentGame->SetCardIndex(this->currentGame->GetCurrentPlayer(), i + (this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) * 15));
					/* Überprüfe ob Spielbar. */
					if (this->currentGame->Playable(this->currentGame->GetCurrentPlayer(), this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()))) {
						if (this->forceEleven) {
							/* Checke, ob diese Karte eine 11 ist. */
							if (this->currentGame->GetPlayerCard(this->currentGame->GetCurrentPlayer(),
								this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer())).CT != CardType::NUMBER_11) {
									Msg::DisplayWaitMsg(Lang::get("FORCE_ELEVEN"));
									return;
								}

							if (!this->checkProper11()) {
								Overlays::CardOrderOverlay();
								return;
							}
						}

						if (!this->DoPlayMove().second) {
							if (!this->gameOver) this->NextPHandle();
						}
					}
				}
			}
		}
	}

	/* Karten-Zieh Logik. */
	if (hDown & KEY_X) {
		/* Zwinge die 11. */
		if (this->forceEleven) {
			Msg::DisplayWaitMsg(Lang::get("FORCE_ELEVEN"));
			return;
		}

		/* Falls Kartendeck größer als 0 ist. */
		if (this->currentGame->GetDeckSize() > 0) {
			if (this->currentGame->GetDrawAmount() < 3) {
				this->currentGame->AddPlayerCard(this->currentGame->GetCurrentPlayer());
				this->forceElevenCheck();

				/* Wenn wir schon 3 mal gezogen haben, zwinge uns nicht zu spielen. */
				if (this->currentGame->GetDrawAmount() == 3) {
					this->forcePlay = false;

					/* Falls wir nicht können, gehe zum nächsten Spieler. */
					if (!this->checkPlay()) this->NextPHandle();
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

		/* Falls Kartendeck größer als 0 ist. */
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

	if (hHeld & KEY_SELECT) Msg::HelperBox(Lang::get("GAME_INSTR"));

	if (hDown & KEY_START) this->isSub = true; // Gehe zum Unter-Menü.
}

/* Die HauptLogik des Spiel-Screen's. */
void GameScreen::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	/* Falls das Spiel vorbei ist. */
	if (this->gameOver) {
		if (Msg::promptMsg(Lang::get("NEXT_GAME"))) {
			Msg::DisplayMsg(Lang::get("PREPARE_GAME"));
			this->currentGame->InitNewGame(this->currentGame->GetPlayerAmount());
			this->forcePlay = true;
			this->forceElevenCheck(); // Setze den Check hier.
			this->gameOver = false;

		} else {
			exiting = true;
		}
	}

	if (this->isSub) this->SubLogic(hDown, hHeld, touch);
	else this->GameLogic(hDown, hHeld, touch);
}

/*
	Überprüfe, ob die richtige 11 gespielt wurde.

	Die Reihenfolge ist: Rot, Gelb, Grün und Blau.
*/
bool GameScreen::checkProper11() const {
	const CardStruct CS = this->currentGame->GetPlayerCard(this->currentGame->GetCurrentPlayer(), this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()));

	if (CS.CT != CardType::NUMBER_11) return false;

	if (this->checkSpecificCard(CardType::NUMBER_11, CardColor::COLOR_1)) return CS.CC == CardColor::COLOR_1;
	if (this->checkSpecificCard(CardType::NUMBER_11, CardColor::COLOR_2)) return CS.CC == CardColor::COLOR_2;
	if (this->checkSpecificCard(CardType::NUMBER_11, CardColor::COLOR_3)) return CS.CC == CardColor::COLOR_3;
	if (this->checkSpecificCard(CardType::NUMBER_11, CardColor::COLOR_4)) return CS.CC == CardColor::COLOR_4;

	return false;
}

/* Nächster Spieler Handle. */
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

		/* Falls der Karten-Index größer als die Anzahl der Karten ist.. gehe Eins zurück. */
		if (this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) >= this->currentGame->GetPlayerHandSize(this->currentGame->GetCurrentPlayer())) {
			switch(this->currentGame->GetPlayerHandSize(this->currentGame->GetCurrentPlayer())) {
				case 15:
				case 30:
				case 45:
				case 60:
				case 75:
					this->currentGame->SetCardIndex(this->currentGame->GetCurrentPlayer(), (this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) - 1) * 15);
					this->currentGame->SetPageIndex(this->currentGame->GetCurrentPlayer(), this->currentGame->GetPageIndex(this->currentGame->GetCurrentPlayer()) - 1);
					break;

				default:
					this->currentGame->SetCardIndex(this->currentGame->GetCurrentPlayer(), this->currentGame->GetCardIndex(this->currentGame->GetCurrentPlayer()) - 1);
					break;
			}
		}

		/* 0 Karten auf der Hand --> Gewonnen. */
		if (this->currentGame->GetPlayerHandSize(this->currentGame->GetCurrentPlayer()) == 0) {
			this->gameOver = true;
			char msg[100];
			snprintf(msg, sizeof(msg), Lang::get("PLAYER_WON").c_str(), this->currentGame->GetCurrentPlayer() + 1);
			Msg::DisplayWaitMsg(msg);
			return { false, false };
		}

		this->forceElevenCheck();

		results.second = this->checkPlay();
	}

	return results;
}

/* Überprüfe, ob ein Spieler spielen kann. */
bool GameScreen::checkPlay() {
	for (uint8_t i = 0; i < this->currentGame->GetPlayerHandSize(this->currentGame->GetCurrentPlayer()); i++) {
		const CardStruct CS = this->currentGame->GetPlayerCard(this->currentGame->GetCurrentPlayer(), i);
		const bool isUpper = (uint8_t)CS.CT >= 12 ? true : false; // 12 + wäre die obere Karte.

		if (this->currentGame->CanPlay(CS.CC, isUpper, CS.CT)) return true; // Weil wir fortfahren können --> Beende die Runde nicht!
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

/* Gegner Logik hier. */
void GameScreen::AILogic() {
	bool doOut = false, canPlay = false;

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
			if (!this->DoPlayMove().second) doOut = true;
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

	if (!this->gameOver) this->NextPHandle();
}

/* Falls eine 11 auf der Spielerhand existiert, zwinge diese Karte. */
void GameScreen::forceElevenCheck() {
	this->forceEleven = false;

	/* Überprüfe Rote Karte zuerst. */
	if (this->currentGame->getTableCard(CardColor::COLOR_1).first == CardType::NUMBER_EMPTY) {
		if (this->checkSpecificCard(CardType::NUMBER_11, CardColor::COLOR_1)) {
			//Msg::DisplayWaitMsg("Rote Elf wurde gezwungen.");
			this->forceEleven = true;
			return;
		}
	}

	/* Dann überprüfe Gelb. */
	if (this->currentGame->getTableCard(CardColor::COLOR_2).first == CardType::NUMBER_EMPTY) {
		if (this->checkSpecificCard(CardType::NUMBER_11, CardColor::COLOR_2)) {
			//Msg::DisplayWaitMsg("Gelbe Elf wurde gezwungen.");
			this->forceEleven = true;
			return;
		}
	}

	/* Dann überprüfe Grün. */
	if (this->currentGame->getTableCard(CardColor::COLOR_3).first == CardType::NUMBER_EMPTY) {
		if (this->checkSpecificCard(CardType::NUMBER_11, CardColor::COLOR_3)) {
			//Msg::DisplayWaitMsg("Grüne Elf wurde gezwungen.");
			this->forceEleven = true;
			return;
		}
	}

	/* Und als letztes... überprüfe Blau. */
	if (this->currentGame->getTableCard(CardColor::COLOR_4).first == CardType::NUMBER_EMPTY) {
		if (this->checkSpecificCard(CardType::NUMBER_11, CardColor::COLOR_4)) {
			//Msg::DisplayWaitMsg("Blaue Elf wurde gezwungen.");
			this->forceEleven = true;
			return;
		}
	}
}