//------------------------------------------------------------------------------
// emMainWindow.h
//
// Copyright (C) 2006-2012 Oliver Hamann.
//
// Homepage: http://eaglemode.sourceforge.net/
//
// This program is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License version 3 as published by the
// Free Software Foundation.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License version 3 for
// more details.
//
// You should have received a copy of the GNU General Public License version 3
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#ifndef emMainWindow_h
#define emMainWindow_h

#ifndef emWindow_h
#include <emCore/emWindow.h>
#endif

#ifndef emBookmarks_h
#include <emMain/emBookmarks.h>
#endif

#ifndef emMainPanel_h
#include <emMain/emMainPanel.h>
#endif


class emMainWindow : public emWindow {

public:

	emMainWindow(emContext & parentContext);
	virtual ~emMainWindow();

	virtual emString GetTitle();

	emMainPanel & GetMainPanel();
	emView & GetControlView();
	emView & GetContentView();

	emMainWindow * Duplicate();

	void ToggleFullscreen();
	void ReloadFiles();
	void ToggleControlView();
	void Close();
	void Quit();

protected:

	virtual bool Cycle();

	virtual void Input(emInputEvent & event, const emInputState & state);

	virtual void DoCustomCheat(const char * func);

private:

	static void RecreateContentPanels(emScreen & screen);
	void CreateControlWindow();

	emRef<emBookmarksModel> BookmarksModel;
	bool ToClose;

	emMainPanel * MainPanel;
	emPanel * ControlPanel;
	emPanel * ContentPanel;
	emCrossPtr<emWindow> ControlWindow;
};

inline emMainPanel & emMainWindow::GetMainPanel()
{
	return *MainPanel;
}

inline emView & emMainWindow::GetControlView()
{
	return MainPanel->GetControlView();
}

inline emView & emMainWindow::GetContentView()
{
	return MainPanel->GetContentView();
}


#endif
