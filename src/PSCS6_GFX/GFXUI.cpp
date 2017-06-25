// ADOBE SYSTEMS INCORPORATED
// Copyright  1993 - 2002 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this 
// file in accordance with the terms of the Adobe license agreement
// accompanying it.  If you have received this file from a source
// other than Adobe, then your use, modification, or distribution
// of it requires the prior written permission of Adobe.
//-------------------------------------------------------------------
/*
	File: SimpleFormatUI.cpp

*/

#define IDC_OK 1
#define IDC_CANCEL 2

#include <windows.h>
#include <Commctrl.h>
#include "GFX-sym.h"
#include "GFX.h"
#include "PIUI.h"

#include "GFXLib.h"
extern GFXLib gfx;

class GFXSettingsDialog : public PIDialog
{
private:
	FormatRecord *_frecord;
	virtual void Init(void);
	virtual void Notify(int32 item);
public:
	GFXSettingsDialog(FormatRecord *frecord) : PIDialog()
	{
		_frecord = frecord;
		gfx.SetSize(_frecord->imageSize32.h, _frecord->imageSize32.v);
	}
	~GFXSettingsDialog()
	{
		
	}
};

bool DoUI (FormatRecord *frecord)
{
	GFXSettingsDialog dialog(frecord);
	return dialog.Modal(gPluginRef, NULL, 16050) == IDC_OK ? true : false;
}

void GFXSettingsDialog::Init(void)
{
	char buf[10];
	HWND ctrlComboBox_mode = GetDlgItem(GetDialog(), IDC_MODE);
	ComboBox_AddString(ctrlComboBox_mode, "Undefined");
	ComboBox_AddString(ctrlComboBox_mode, "Monochrome");
	ComboBox_AddString(ctrlComboBox_mode, "16 colors");
	ComboBox_AddString(ctrlComboBox_mode, "256 colors");
	ComboBox_AddString(ctrlComboBox_mode, "16-bit");
	ComboBox_AddString(ctrlComboBox_mode, "24-bit");
	ComboBox_AddString(ctrlComboBox_mode, "32-bit");

	itoa(LOWORD(gfx.GetSize()), buf, 10);
	HWND ctrlEdit_width = GetDlgItem(GetDialog(), IDC_WIDTH);
	Edit_SetText(ctrlEdit_width, buf);

	itoa(HIWORD(gfx.GetSize()), buf, 10);
	HWND ctrlEdit_height = GetDlgItem(GetDialog(), IDC_HEIGHT);
	Edit_SetText(ctrlEdit_height, buf);
}

void GFXSettingsDialog::Notify(int32 item)
{
	switch(item)
	{
	case IDC_OK: // Ok
		break;
	case IDC_CANCEL: // Annulla
		break;
	case IDC_CHECK_COMPRESSED:
		gfx.SetFlagCompressed(SendMessage((HWND)GetDlgItem(GetDialog(), item), BM_GETCHECK, 0, 0) == BST_CHECKED ? true : false);
		break;
	case IDC_CHECK_INTERNALPALETTE:
		gfx.SetFlagInternalPalette(SendMessage((HWND)GetDlgItem(GetDialog(), item), BM_GETCHECK, 0, 0) == BST_CHECKED ? true : false);
		break;
	case IDC_MODE:
		gfx.SetGFXMode((GFXMode)ComboBox_GetCurSel((HWND)GetDlgItem(GetDialog(), item)));
		break;
	case IDC_RESOLUTION:
		gfx.SetResolution((char)SendMessage((HWND)GetDlgItem(GetDialog(), item), UDM_GETPOS, 0, 0));
		break;
	case IDC_DEST:
		gfx.SetDestination((unsigned char)SendMessage((HWND)GetDlgItem(GetDialog(), item), UDM_GETPOS, 0, 0));
		break;
	case IDC_TEXCOUNT:
		gfx.SetTextureCount((unsigned char)SendMessage((HWND)GetDlgItem(GetDialog(), item), UDM_GETPOS, 0, 0));
		break;
	}
}