#include "GlaserCalcDlgImpl.h"
#include "GlaserData.h"
#include <wx/valnum.h>

IMPLEMENT_APP_NO_MAIN(MyApp)

bool MyApp::OnInit()
{
	return true;
}

int MyApp::OnExit()
{
	return 0;
}

///////////////////////////////////////////////////////////////////////////

GlaserCalcDlgImpl::GlaserCalcDlgImpl(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: GlaserCalcDlg(parent, id, title, pos, size, style)
{
	SetSize(wxSize(379, 1026));
	Centre();

	SetDoubleBuffered(true);

  m_grid->SetColFormatFloat(1, -1, 2);
  m_grid->SetColFormatFloat(2, -1, 0);
  m_grid->SetColFormatFloat(3, -1, 2);
  m_grid->SetColFormatFloat(4, -1, 2);
  m_grid->SetColFormatFloat(5, -1, 2);
  m_grid->SetColFormatFloat(6, -1, 2);

  m_PhiInsideCtrl->SetEditable(false);
  m_PhiOutsideCtrl->SetEditable(false);
  m_ThetaInsideCtrl->SetEditable(false);
  m_ThetaOutsideCtrl->SetEditable(false);
  m_PsInsideCtrl->SetEditable(false);
  m_PsOutsideCtrl->SetEditable(false);

  wxFloatingPointValidator<float> floatValidatorPhiInside(1, &m_PhiInside, wxNUM_VAL_ZERO_AS_BLANK);
  floatValidatorPhiInside.SetRange(0, 100);
  m_PhiInsideCtrl->SetValidator(floatValidatorPhiInside);

  wxFloatingPointValidator<float> floatValidatorPhiOutside(1, &m_PhiOutside, wxNUM_VAL_ZERO_AS_BLANK);
  floatValidatorPhiOutside.SetRange(0, 100);
  m_PhiOutsideCtrl->SetValidator(floatValidatorPhiOutside);

  wxFloatingPointValidator<float> floatValidatorThetaInside(1, &m_ThetaInside, wxNUM_VAL_ZERO_AS_BLANK);
  floatValidatorThetaInside.SetRange(-30, 40);
  m_ThetaInsideCtrl->SetValidator(floatValidatorThetaInside);

  wxFloatingPointValidator<float> floatValidatorThetaOutside(1, &m_ThetaOutside, wxNUM_VAL_ZERO_AS_BLANK);
  floatValidatorThetaOutside.SetRange(-30, 40);
  m_ThetaOutsideCtrl->SetValidator(floatValidatorThetaOutside);

  wxFloatingPointValidator<float> floatValidatorPsInside(0, &m_PsInside, wxNUM_VAL_ZERO_AS_BLANK);
  floatValidatorPsInside.SetRange(0, 3000);
  m_PsInsideCtrl->SetValidator(floatValidatorPsInside);

  wxFloatingPointValidator<float> floatValidatorPsOutside(0, &m_PsOutside, wxNUM_VAL_ZERO_AS_BLANK);
  floatValidatorPsOutside.SetRange(0, 3000);
  m_PsOutsideCtrl->SetValidator(floatValidatorPsOutside);
}

GlaserCalcDlgImpl::~GlaserCalcDlgImpl()
{
}

void GlaserCalcDlgImpl::OnGridCmdCellChanged(wxGridEvent& event)
{
	wxString valueStr = m_grid->GetCellValue(event.GetRow(), event.GetCol());

	auto it = m_valueLookUp.find(std::make_pair(event.GetRow(), event.GetCol()));

	double value(0.0);

  if (it != m_valueLookUp.end() && valueStr.ToCDouble(&value))
  {
		*it->second = value;
  }

	m_pGlaserCalc->calc();

	updateValues();
}

void GlaserCalcDlgImpl::OnParameterChoice(wxCommandEvent& event)
{
  updateValues();
}

void GlaserCalcDlgImpl::OnPhiInsideKillFocus(wxFocusEvent& event)
{
  if (m_PhiInsideCtrl->IsEditable())
  {
    int selection = m_ParameterChoice->GetSelection();

    const auto pParameter = getParameter(selection);

    if (pParameter != nullptr)
    {
      pParameter->PhiInside = m_PhiInside;
    }

    TransferDataFromWindow();
  }
  
  updateValues();
}

void GlaserCalcDlgImpl::OnPhiOutsideKillFocus(wxCommandEvent& event)
{
  if (m_PhiOutsideCtrl->IsEditable())
  {
    int selection = m_ParameterChoice->GetSelection();

    const auto pParameter = getParameter(selection);

    if (pParameter != nullptr)
    {
      pParameter->PhiOutside = m_PhiOutside;
    }

    TransferDataFromWindow();
  }

  updateValues();
}

void GlaserCalcDlgImpl::OnThetaInsideKillFocus(wxCommandEvent& event)
{
  if (m_ThetaInsideCtrl->IsEditable())
  {
    int selection = m_ParameterChoice->GetSelection();

    const auto pParameter = getParameter(selection);

    if (pParameter != nullptr)
    {
      pParameter->ThetaInside = m_ThetaInside;
    }

    TransferDataFromWindow();
  }

  updateValues();
}

void GlaserCalcDlgImpl::OnThetaOutsideKillFocus(wxCommandEvent& event)
{
  if (m_ThetaOutsideCtrl->IsEditable())
  {
    int selection = m_ParameterChoice->GetSelection();

    const auto pParameter = getParameter(selection);

    if (pParameter != nullptr)
    {
      pParameter->ThetaOutside = m_ThetaOutside;
    }

    TransferDataFromWindow();
  }

  updateValues();
}

void GlaserCalcDlgImpl::OnPsInsideKillFocus(wxCommandEvent& event)
{
  if (m_PsInsideCtrl->IsEditable())
  {
    int selection = m_ParameterChoice->GetSelection();

    const auto pParameter = getParameter(selection);

    if (pParameter != nullptr)
    {
      pParameter->PsInside = m_PsInside;
    }

    TransferDataFromWindow();
  }

  updateValues();
}

void GlaserCalcDlgImpl::OnPsOutsideKillFocus(wxCommandEvent& event)
{
  if (m_PsOutsideCtrl->IsEditable())
  {
    int selection = m_ParameterChoice->GetSelection();

    const auto pParameter = getParameter(selection);

    if (pParameter != nullptr)
    {
      pParameter->PsOutside = m_PsOutside;
    }

    TransferDataFromWindow();
  }

  updateValues();
}

ParameterData* GlaserCalcDlgImpl::getParameter(int selection)
{
  if (m_pGlaserCalc == nullptr)
  {
    return nullptr;
  }

  auto it = m_pGlaserCalc->getGlaserData().parameterSets.end();

  if (selection == 0)
  {
    it = m_pGlaserCalc->getGlaserData().parameterSets.find(_T("DewPeriod"));
  }
  else if (selection == 1)
  {
    it = m_pGlaserCalc->getGlaserData().parameterSets.find(_T("EvaporationPeriod"));
  }
  else
  {
    it = m_pGlaserCalc->getGlaserData().parameterSets.find(_T("UserDefinedPeriod"));
  }

  if (it != m_pGlaserCalc->getGlaserData().parameterSets.end())
  {
    return &it->second;
  }

  return nullptr;
}

void GlaserCalcDlgImpl::updateParameterFields(ParameterData* pParameter)
{
  if (pParameter == nullptr)
  {
    return;
  }

  if (pParameter->name == L"UserDefinedPeriod")
  {
    m_PhiInsideCtrl->SetEditable(true);
    m_PhiOutsideCtrl->SetEditable(true);
    m_ThetaInsideCtrl->SetEditable(true);
    m_ThetaOutsideCtrl->SetEditable(true);
    m_PsInsideCtrl->SetEditable(true);
    m_PsOutsideCtrl->SetEditable(true);
  }
  else
  {
    m_PhiInsideCtrl->SetEditable(false);
    m_PhiOutsideCtrl->SetEditable(false);
    m_ThetaInsideCtrl->SetEditable(false);
    m_ThetaOutsideCtrl->SetEditable(false);
    m_PsInsideCtrl->SetEditable(false);
    m_PsOutsideCtrl->SetEditable(false);
  }

  m_PhiInside = pParameter->PhiInside;
  m_PhiOutside = pParameter->PhiOutside;
  m_ThetaInside = pParameter->ThetaInside;
  m_ThetaOutside = pParameter->ThetaOutside;
  m_PsInside = pParameter->PsInside;
  m_PsOutside = pParameter->PsOutside;

  TransferDataToWindow();

  Refresh();
}

void GlaserCalcDlgImpl::updateValues()
{
  GlaserData& glaserData = m_pGlaserCalc->getGlaserData();

  int selection = m_ParameterChoice->GetSelection();

  const auto pParameter = getParameter(selection);

  if (pParameter == nullptr)
  {
    return;
  }

  updateParameterFields(pParameter);

  m_GlaserDiagram->setParameterData(pParameter);
  m_GlaserDiagram->setGlaserData(&glaserData);

	createLookup(glaserData.layers);

	m_grid->DeleteRows(0, m_grid->GetNumberRows());

	m_ElementNameCtrl->SetValue(glaserData.elementName);
  m_ElementTypeCtrl->SetValue(glaserData.elementType);

	double R(0.0);
	int row(0);

	for (auto& layer : glaserData.layers)
	{
		m_grid->AppendRows();

		R += layer.R;

		// name
		m_grid->SetCellValue(row, 0, layer.name);
		m_grid->SetReadOnly(row, 0, true);

		// width
		m_grid->SetCellValue(row, 1, wxString::FromDouble(layer.width));

		if (layer.width <= 0.0)
		{
      m_grid->SetCellBackgroundColour(row, 1, *wxRED);
		}

		// mue
		m_grid->SetCellValue(row, 2, wxString::FromDouble(layer.mue));

    if (layer.mue <= 0.0)
    {
      m_grid->SetCellBackgroundColour(row, 2, *wxRED);
    }

		// Sd
		m_grid->SetCellValue(row, 3, wxString::FromDouble(layer.Sd));
		m_grid->SetReadOnly(row, 3, true);
		m_grid->SetCellBackgroundColour(row, 3, wxColor(224,224,224));

		// lambda
		m_grid->SetCellValue(row, 4, wxString::FromDouble(layer.lambda));

    if (layer.lambda <= 0.0)
    {
      m_grid->SetCellBackgroundColour(row, 4, *wxRED);
    }

		// T
		if (!glaserData.results.T.empty())
		{
			m_grid->SetCellValue(row, 5, wxString::FromDouble(glaserData.results.T[row+1]));
		}

    m_grid->SetReadOnly(row, 5, true);
    m_grid->SetCellBackgroundColour(row, 5, wxColor(224, 224, 224));

		// Ps
		if (!glaserData.results.Ps.empty())
		{
			m_grid->SetCellValue(row, 6, wxString::FromDouble(glaserData.results.Ps[row + 1]));
		}

		m_grid->SetReadOnly(row, 6, true);
    m_grid->SetCellBackgroundColour(row, 6, wxColor(224, 224, 224));

		++row;
	}

  R += pParameter->RInside;
  R += pParameter->ROutside;

	m_UValueCtrl->SetValue(wxString::FromDouble(1/R));

	m_grid->AutoSizeColumns();

  m_GlaserDiagram->Refresh();
}


void GlaserCalcDlgImpl::createLookup(std::vector<LayerData>& layers)
{
	m_valueLookUp.clear();

  int row(0);
  for (auto& layer : layers)
  {
		m_valueLookUp.emplace(std::make_pair(row, 1), &layer.width);
		m_valueLookUp.emplace(std::make_pair(row, 2), &layer.mue);
    m_valueLookUp.emplace(std::make_pair(row, 4), &layer.lambda);

    ++row;
  }
}

void GlaserCalcDlgImpl::OnInitDialog(wxInitDialogEvent& event)
{
	DoGetBestClientSize();
	DoGetBestSize();
}
