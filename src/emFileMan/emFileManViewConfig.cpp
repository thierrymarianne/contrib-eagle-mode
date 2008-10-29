//------------------------------------------------------------------------------
// emFileManViewConfig.cpp
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

#include <ctype.h>
#include <emFileMan/emFileManViewConfig.h>


emRef<emFileManViewConfig> emFileManViewConfig::Acquire(emView & view)
{
	EM_IMPL_ACQUIRE_COMMON(emFileManViewConfig,view,"")
}


void emFileManViewConfig::SetSortCriterion(SortCriterionType sc)
{
	if (SortCriterion!=sc) {
		SortCriterion=sc;
		Signal(ChangeSignal);
	}
}


void emFileManViewConfig::SetNameSortingStyle(NameSortingStyleType nss)
{
	if (NameSortingStyle!=nss) {
		NameSortingStyle=nss;
		Signal(ChangeSignal);
	}
}


void emFileManViewConfig::SetSortDirectoriesFirst(bool b)
{
	if (SortDirectoriesFirst!=b) {
		SortDirectoriesFirst=b;
		Signal(ChangeSignal);
	}
}


void emFileManViewConfig::SetShowHiddenFiles(bool b)
{
	if (ShowHiddenFiles!=b) {
		ShowHiddenFiles=b;
		Signal(ChangeSignal);
	}
}


void emFileManViewConfig::SaveAsDefault()
{
	FileManConfig->SortCriterion=SortCriterion;
	FileManConfig->NameSortingStyle=NameSortingStyle;
	FileManConfig->SortDirectoriesFirst=SortDirectoriesFirst;
	FileManConfig->ShowHiddenFiles=ShowHiddenFiles;
	FileManConfig->Save();
}


int emFileManViewConfig::CompareDirEntries(
	const emDirEntry & e1, const emDirEntry & e2
) const
{
	const char * n1, * n2;
	int i, j, k, l, m;

	if (SortDirectoriesFirst) {
		if (e1.IsDirectory()) {
			if (!e2.IsDirectory()) return -1;
		}
		else if (e2.IsDirectory()) return 1;
	}

	switch (SortCriterion) {
		case SORT_BY_ENDING:
			i=CompareNames(
				emGetExtensionInPath(e1.GetName()),
				emGetExtensionInPath(e2.GetName())
			);
			if (i) return i;
			break;
		case SORT_BY_CLASS:
			n1=e1.GetName();
			n2=e2.GetName();
			i=strlen(n1);
			j=strlen(n2);
			do {
				k=i;
				l=j;
				if (i>0) for (i--; i>0; i--) {
					if (isalpha(n1[i])) {
						if (!isalpha(n1[i-1])) break;
						if (NameSortingStyle!=NSS_CASE_INSENSITIVE &&
						    isupper(n1[i]) && !isupper(n1[i-1])) break;
					}
					else if (isdigit(n1[i])) {
						if (!isdigit(n1[i-1])) break;
					}
					else if (isalnum(n1[i-1])) break;
				}
				if (j>0) for (j--; j>0; j--) {
					if (isalpha(n2[j])) {
						if (!isalpha(n2[j-1])) break;
						if (NameSortingStyle!=NSS_CASE_INSENSITIVE &&
						    isupper(n2[j]) && !isupper(n2[j-1])) break;
					}
					else if (isdigit(n2[j])) {
						if (!isdigit(n2[j-1])) break;
					}
					else if (isalnum(n2[j-1])) break;
				}
				k-=i;
				l-=j;
				if (k<l) {
					if (k>0) {
						if (NameSortingStyle==NSS_CASE_INSENSITIVE) m=strncasecmp(n1+i,n2+j,k);
						else m=strncmp(n1+i,n2+j,k);
						if (m) return m;
					}
					return -1;
				}
				if (l>0) {
					if (NameSortingStyle==NSS_CASE_INSENSITIVE) m=strncasecmp(n1+i,n2+j,l);
					else m=strncmp(n1+i,n2+j,l);
					if (m) return m;
				}
				if (k>l) return 1;
			} while (l>0);
			return strcmp(n1,n2);
		case SORT_BY_VERSION:
			n1=e1.GetName();
			n2=e2.GetName();
			i=0;
			if (NameSortingStyle==NSS_CASE_INSENSITIVE) {
				while ((n1[i]==n2[i] || tolower((unsigned char)n1[i])==
				       tolower((unsigned char)n2[i])) && n1[i]) i++;
			}
			else {
				while (n1[i]==n2[i] && n1[i]) i++;
			}
			if ((n1[i]<'0' || n1[i]>'9') && (n2[i]<'0' || n2[i]>'9')) break;
			for (j=i; j>0 && n1[j-1]>='0' && n1[j-1]<='9'; j--);
			if (n1[j]<'0' || n1[j]>'9' || n2[j]<'0' || n2[j]>'9') break;
			if (n1[j]=='0' || n2[j]=='0') {
				if (n1[i]<'0' || n1[i]>'9') return -1;
				if (n2[i]<'0' || n2[i]>'9') return 1;
				return n1[i]-n2[i];
			}
			j=n1[i]-n2[i];
			for (;;i++) {
				if (n1[i]<'0' || n1[i]>'9') {
					if (n2[i]<'0' || n2[i]>'9') break;
					return -1;
				}
				else if (n2[i]<'0' || n2[i]>'9') return 1;
			}
			return j;
		case SORT_BY_DATE:
			if (e1.GetStat()->st_mtime <
			    e2.GetStat()->st_mtime) return -1;
			if (e1.GetStat()->st_mtime >
			    e2.GetStat()->st_mtime) return 1;
			break;
		case SORT_BY_SIZE:
			if (e1.GetStat()->st_size <
			    e2.GetStat()->st_size) return -1;
			if (e1.GetStat()->st_size >
			    e2.GetStat()->st_size) return 1;
			break;
		default:
			break;
	}

	i=CompareNames(e1.GetName(),e2.GetName());
	if (!i) i=strcmp(e1.GetName(),e2.GetName());
	return i;
}


emFileManViewConfig::emFileManViewConfig(
	emContext & context, const emString & name
)
	: emModel(context,name)
{
	FileManConfig=emFileManConfig::Acquire(GetRootContext());

	SortCriterion=(SortCriterionType)FileManConfig->SortCriterion.Get();
	NameSortingStyle=(NameSortingStyleType)FileManConfig->NameSortingStyle.Get();
	SortDirectoriesFirst=FileManConfig->SortDirectoriesFirst.Get();
	ShowHiddenFiles=FileManConfig->ShowHiddenFiles.Get();

	SetMinCommonLifetime(UINT_MAX);
}


emFileManViewConfig::~emFileManViewConfig()
{
}


int emFileManViewConfig::CompareNames(const char * n1, const char * n2) const
{
	switch (NameSortingStyle) {
		default:
			return strcoll(n1,n2);
		case NSS_CASE_SENSITIVE:
			return strcmp(n1,n2);
		case NSS_CASE_INSENSITIVE:
			return strcasecmp(n1,n2);
	}
}
