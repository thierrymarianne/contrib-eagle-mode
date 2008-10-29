//------------------------------------------------------------------------------
// emDirEntryPanel.h
//
// Copyright (C) 2004-2008 Oliver Hamann.
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

#ifndef emDirEntryPanel_h
#define emDirEntryPanel_h

#ifndef emVarModel_h
#include <emCore/emVarModel.h>
#endif

#ifndef emPanel_h
#include <emCore/emPanel.h>
#endif

#ifndef emDirEntry_h
#include <emFileMan/emDirEntry.h>
#endif

#ifndef emFileManModel_h
#include <emFileMan/emFileManModel.h>
#endif


class emDirEntryPanel : public emPanel {

public:

	emDirEntryPanel(ParentArg parent, const emString & name,
	                const emDirEntry & dirEntry);

	virtual ~emDirEntryPanel();

	const emDirEntry & GetDirEntry() const;

	void UpdateDirEntry(const emDirEntry & dirEntry);
		// Must have same path.

	virtual emString GetTitle();

protected:

	virtual bool Cycle();

	virtual void Notice(NoticeFlags flags);

	virtual void Input(emInputEvent & event, const emInputState & state,
	                   double mx, double my);

	virtual bool IsOpaque();

	virtual void Paint(const emPainter & painter, emColor canvasColor);

	virtual emPanel * CreateControlPanel(ParentArg parent,
	                                     const emString & name);

private:

	struct SharedStuff {
		emRef<emFileManModel> FileMan;
		emImage InnerBorderImage;
		emImage OuterBorderImage;
	};

	void UpdateBgColor();

	void Select(bool shift, bool ctrl);
	void SelectSolely();
	void RunDefaultCommand();

	static void FormatTime(time_t t, char * buf);

	static const emString ContentName;
	static const emString AltName;
	static const double HeightFactor;
	static const double LayoutFrame;
	static const double LayoutTitleX;
	static const double LayoutTitleY;
	static const double LayoutTitleW;
	static const double LayoutTitleH;
	static const double LayoutInfoX;
	static const double LayoutInfoY;
	static const double LayoutInfoW;
	static const double LayoutInfoH;
	static const double LayoutPathX;
	static const double LayoutPathY;
	static const double LayoutPathW;
	static const double LayoutPathH;
	static const double MinAltVW;
	static const double LayoutAltX;
	static const double LayoutAltY;
	static const double LayoutAltW;
	static const double LayoutAltH;
	static const double MinContentVW;
	static const double LayoutContentFrame;
	static const double LayoutContentX;
	static const double LayoutContentY;
	static const double LayoutContentW;
	static const double LayoutContentH;
	static const emColor ColorBGNormal;
	static const emColor ColorBGSrc;
	static const emColor ColorBGTgt;
	static const emColor ColorNameNormal;
	static const emColor ColorNameExe;
	static const emColor ColorNameDir;
	static const emColor ColorNameFifo;
	static const emColor ColorNameBlk;
	static const emColor ColorNameChr;
	static const emColor ColorNameSock;
	static const emColor ColorNameOther;
	static const emColor ColorSymLink;
	static const emColor ColorInfo;
	static const emColor ColorInfoLabel;
	static const emColor ColorPath;

	emRef<emVarModel<SharedStuff> > SharedVar;
	emDirEntry DirEntry;
	emColor BgColor;
};

inline const emDirEntry & emDirEntryPanel::GetDirEntry() const
{
	return DirEntry;
}


#endif
