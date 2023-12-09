///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/grid.h>
#include "GlaserDiagram.h"
#include <wx/choice.h>
#include <wx/collpane.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GlaserCalcDlg
///////////////////////////////////////////////////////////////////////////////
class GlaserCalcDlg : public wxDialog
{
	private:

	protected:
		wxStaticText* m_ElementNameText;
		wxTextCtrl* m_ElementNameCtrl;
		wxStaticText* m_ElementTypeText;
		wxTextCtrl* m_ElementTypeCtrl;
		wxGrid* m_grid;
		GlaserDiagram* m_GlaserDiagram;
		wxStaticText* m_UValueText;
		wxTextCtrl* m_UValueCtrl;
		wxCollapsiblePane* m_collapsiblePaneParameter;
		wxChoice* m_ParameterChoice;
		wxStaticText* m_PhiInsideText;
		wxTextCtrl* m_PhiInsideCtrl;
		wxStaticText* m_PhiOutsideText;
		wxTextCtrl* m_PhiOutsideCtrl;
		wxStaticText* m_ThetaInsideText;
		wxTextCtrl* m_ThetaInsideCtrl;
		wxStaticText* m_ThetaOutsideText;
		wxTextCtrl* m_ThetaOutsideCtrl;
		wxStaticText* m_PsInsideText;
		wxTextCtrl* m_PsInsideCtrl;
		wxStaticText* m_PsOutsideText;
		wxTextCtrl* m_PsOutsideCtrl;

		// Virtual event handlers, override them in your derived class
		virtual void OnGridCmdCellChanged( wxGridEvent& event ) { event.Skip(); }
		virtual void OnParameterChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPhiInsideKillFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnPhiOutsideKillFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnThetaInsideKillFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnThetaOutsideKillFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnPsInsideKillFocus( wxFocusEvent& event ) { event.Skip(); }
		virtual void OnPsOutsideKillFocus( wxFocusEvent& event ) { event.Skip(); }


	public:

		GlaserCalcDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 383,680 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP );

		~GlaserCalcDlg();

};

