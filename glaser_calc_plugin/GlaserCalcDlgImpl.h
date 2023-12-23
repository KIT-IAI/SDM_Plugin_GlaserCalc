#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "GlaserCalcDlg.h"
#include "GlaserCalc.h"
#include "GlaserData.h"
#include <LiveLogFeature.hpp>

///////////////////////////////////////////////////////////////////////////

class MyApp : public wxApp
{
  public:
    virtual bool OnInit();
    virtual int OnExit();
};

///////////////////////////////////////////////////////////////////////////

class GlaserCalcDlgImpl : public GlaserCalcDlg
{
  public:
	  GlaserCalcDlgImpl(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(390, 977), long style = wxDEFAULT_DIALOG_STYLE);
    ~GlaserCalcDlgImpl();

  public:
    void setGlaserCalc(GlaserCalc& glaserCalc) { m_pGlaserCalc = &glaserCalc; }
    void updateValues();
    ParameterData* getCurrentParameterData();

  private:
    void createLookup(std::vector<LayerData>& layers);
    void updateParameterFields(ParameterData* pParameter);

  private:
    virtual void OnInitDialog(wxInitDialogEvent& event);
    virtual void OnGridCmdCellChanged(wxGridEvent& event);
    virtual void OnParameterChoice(wxCommandEvent& event);
    virtual void OnPhiInsideKillFocus(wxFocusEvent& event);
    virtual void OnPhiOutsideKillFocus(wxFocusEvent& event);
    virtual void OnThetaInsideKillFocus(wxFocusEvent& event);
    virtual void OnThetaOutsideKillFocus(wxFocusEvent& event);
    virtual void OnPsInsideKillFocus(wxFocusEvent& event);
    virtual void OnPsOutsideKillFocus(wxFocusEvent& event);

  private:
    GlaserCalc* m_pGlaserCalc = nullptr;
    sdm::plugin::LiveLogInterface* m_pLoggerInterface = nullptr;
    std::map<std::pair<int, int>, double*> m_valueLookUp;

    float m_PhiInside = 0.0;
    float m_PhiOutside = 0.0;
    float m_ThetaInside = 0.0;
    float m_ThetaOutside = 0.0;
    float m_PsInside = 0.0;
    float m_PsOutside = 0.0;
    float m_uValue = 0.0;
    float m_mT = 0.0;
    float m_mV = 0.0;
};
