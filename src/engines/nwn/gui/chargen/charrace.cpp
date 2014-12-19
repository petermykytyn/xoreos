/* xoreos - A reimplementation of BioWare's Aurora engine
 *
 * xoreos is the legal property of its developers, whose names
 * can be found in the AUTHORS file distributed with this source
 * distribution.
 *
 * xoreos is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * xoreos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with xoreos. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file engines/nwn/gui/chargen/charrace.h
 *  The race chooser in NWN CharGen.
 */

#include "aurora/talkman.h"

#include "engines/nwn/types.h"

#include "engines/nwn/gui/widgets/button.h"
#include "engines/nwn/gui/widgets/buttonsgroup.h"
#include "engines/nwn/gui/widgets/editbox.h"

#include "engines/nwn/gui/chargen/charrace.h"

namespace Engines {

namespace NWN {

CharRace::CharRace() {
	load("cg_race");

	// TODO Implement subrace.
	getWidget("SubRaceButton", true)->setDisabled(true);

	// Init buttons and helpbox.
	_buttons = new ButtonsGroup(getEditBox("HelpBox", true));

	uint textID = 251;
	uint titleID = 1985;

	_buttons->addButton(getButton("DwarfButton", true),
	                    TalkMan.getString(titleID), TalkMan.getString(textID));
	_buttons->addButton(getButton("ElfButton", true),
	                    TalkMan.getString(++titleID), TalkMan.getString(++textID));
	_buttons->addButton(getButton("GnomeButton", true),
	                    TalkMan.getString(++titleID), TalkMan.getString(++textID));
	_buttons->addButton(getButton("HalflingButton", true),
	                    TalkMan.getString(++titleID), TalkMan.getString(++textID));
	_buttons->addButton(getButton("HalfElfButton", true),
	                    TalkMan.getString(++titleID), TalkMan.getString(++textID));
	_buttons->addButton(getButton("HalfOrcButton", true),
	                    TalkMan.getString(++titleID), TalkMan.getString(++textID));
	_buttons->addButton(getButton("HumanButton", true),
	                    TalkMan.getString(++titleID), TalkMan.getString(++textID));

	reset();
}

CharRace::~CharRace() {
	delete _buttons;
}

void CharRace::reset() {
	_buttons->setActive(getButton("HumanButton", true));

	getEditBox("HelpBox", true)->setTitle(TalkMan.getString(481));
	getEditBox("HelpBox", true)->setText(TalkMan.getString(485));

	setCharRace(kRaceInvalid);
}

void CharRace::callbackActive(Widget &widget) {
	if (widget.getTag() == "OkButton") {
		setCharRace(_buttons->getChoice());
		_returnCode = 2;
		return;
	}

	if (widget.getTag() == "CancelButton") {
		// Set previous choice if any.
		if (_charChoices.race < kRaceInvalid)
			_buttons->setActive(_charChoices.race);

		_returnCode = 1;
		return;
	}

	_buttons->setActive((WidgetButton *) &widget);
}

} // End of namespace NWN

} // End of namespace Engines