#include "GlaserDiagram.h"
#include "GlaserData.h"
#include <wx/wx.h>
#include <wx/graphics.h>

GlaserDiagram::GlaserDiagram(wxWindow* parent) : wxControl(parent, wxID_ANY)
{
  Bind(wxEVT_PAINT, &GlaserDiagram::OnPaint, this);
}

void GlaserDiagram::OnPaint(wxPaintEvent& event)
{
  // Create paint DC
  wxPaintDC dc(this);

  // Create graphics context from it
  wxGraphicsContext* pContext = wxGraphicsContext::Create(dc);

  if (pContext)
  {
    wxRect rc = GetClientRect();

    double margin(50.0), marginAxis(30.0);
    const double arrowLength(14), arrowWidth(6);
    const double tickLength(5);

    if (m_pParameter != nullptr)
    {
      double width = std::max(m_pParameter->PsInside, m_pParameter->PsOutside);
      wxSize textSizePs = dc.GetTextExtent(wxString::FromDouble(width));

      marginAxis = std::max(marginAxis, (double)textSizePs.GetWidth()) + tickLength;
    }

    wxPoint2DDouble origin(marginAxis, rc.height - marginAxis);
    double xChartRange = rc.width - marginAxis - margin;
    double yChartRange = rc.height - marginAxis - margin;

    drawCoordAxis(pContext, origin, xChartRange, yChartRange, arrowLength, arrowWidth);
    drawTicks(pContext, origin, xChartRange, yChartRange, tickLength);

    double sumSd(0.0);

    if (m_pGlaserData != nullptr)
    {
      for (auto& layer : m_pGlaserData->layers)
      {
        sumSd += layer.calcSd();
      }

      double range = xChartRange / sumSd;

      double xPos(0.0);

      int i(0);
      double PsXa = origin.m_x, PsYa = origin.m_y - std::min(yChartRange, (yChartRange * m_pParameter->PsInside) / m_pParameter->PsInside);
      double PsXe = 0.0, PsYe = 0.0;

      if (!m_pGlaserData->results.Ps.empty())
      {
        // Internal air -> Internal surface
        PsXe = origin.m_x;
        PsYe = origin.m_y - std::min(yChartRange, (yChartRange * m_pGlaserData->results.Ps[i] / m_pParameter->PsInside));

        pContext->SetPen(*wxRED_PEN);
        pContext->StrokeLine(PsXa, PsYa, PsXe, PsYe);

        PsXa = PsXe;
        PsYa = PsYe;
      }

      // Ps
      pContext->SetPen(*wxRED_PEN);
      pContext->StrokeLine(PsXa, PsYa, PsXe, PsYe);

      for (auto& layer : m_pGlaserData->layers)
      {
        double layerSd = layer.calcSd();

        xPos += range * layerSd;

        if (layerSd > 0.0 && (range * layerSd) < 10) xPos += 10;

        // Sd
        pContext->SetPen(*wxBLUE_PEN);
        pContext->StrokeLine(origin.m_x + xPos, origin.m_y, origin.m_x + xPos, origin.m_y - yChartRange);

        if (!m_pGlaserData->results.T.empty() && !m_pGlaserData->results.Ps.empty())
        {
          //if (layer.Sd > 0.0 && (range * layer.Sd) < 10)
          //if ((Range * Sd[i]) < 10) PsXa = 578 + NewX - 10;

          PsXe = origin.m_x + xPos;
          PsYe = origin.m_y - std::min(yChartRange, (yChartRange * m_pGlaserData->results.Ps[i + 1] / m_pParameter->PsInside));

          // Ps
          pContext->SetPen(*wxRED_PEN);
          pContext->StrokeLine(PsXa, PsYa, PsXe, PsYe);
        }

        ++i;

        PsXa = PsXe;
        PsYa = PsYe;
      }

      if (!m_pGlaserData->results.Ps.empty())
      {
        // Outside surface -> Outside air
        PsYe = origin.m_y - std::min(yChartRange, (yChartRange * m_pParameter->PsOutside / m_pParameter->PsInside));

        pContext->SetPen(*wxRED_PEN);
        pContext->StrokeLine(PsXa, PsYa, PsXe, PsYe);
      }

      // Ps Inside -> Ps Outside
      // Inside : 50% of Ps inside
      // Outside: 80% of Ps outside

      double PsXi = marginAxis;
      double PsYi = origin.m_y - (yChartRange * (m_pParameter->PsInside / 100.0 * 50) / m_pParameter->PsInside);
      double PsXo = marginAxis + xChartRange;
      double PsYo = origin.m_y - (yChartRange * (m_pParameter->PsOutside / 100.0 * 80) / m_pParameter->PsInside);

      // Define a custom line style pattern
      wxDash customPattern[] = { 8, 4 };

      // Create a custom pen with the custom line style
      wxPen customPen(*wxRED, 1, wxPENSTYLE_USER_DASH);
      customPen.SetDashes(2, customPattern);

      //wxPen* penRedDashed = new wxPen(wxColour(255, 0, 0), 1, wxLONG_DASH);
      pContext->SetPen(customPen);
      pContext->StrokeLine(PsXi, PsYi, PsXo, PsYo);
    }

    delete pContext;
  }
}

void GlaserDiagram::drawCoordAxis(wxGraphicsContext* pContext, const wxPoint2DDouble& origin, double xChartRange, double yChartRange, double arrowLength, double arrowWidth)
{
  const double spaceArrow(10);

  // Axis
  pContext->SetPen(*wxBLACK_PEN);
  wxGraphicsPath pathAxis = pContext->CreatePath();
  pContext->StrokeLine(origin.m_x, origin.m_y, origin.m_x + xChartRange + spaceArrow, origin.m_y);
  pContext->StrokeLine(origin.m_x, origin.m_y - yChartRange - spaceArrow, origin.m_x, origin.m_y);

  // Arrow Ps
  wxPoint2DDouble arrowPosPs(origin.m_x, origin.m_y - yChartRange - spaceArrow);
  wxGraphicsPath arrowPs = pContext->CreatePath();
  pContext->SetBrush(wxBrush(wxColour(0, 0, 0), wxBRUSHSTYLE_SOLID));
  arrowPs.MoveToPoint(arrowPosPs);
  arrowPs.AddLineToPoint(arrowPosPs.m_x - arrowWidth/2, arrowPosPs.m_y);
  arrowPs.AddLineToPoint(arrowPosPs.m_x, arrowPosPs.m_y - arrowLength);
  arrowPs.AddLineToPoint(arrowPosPs.m_x + arrowWidth / 2, arrowPosPs.m_y);
  arrowPs.CloseSubpath();
  pContext->FillPath(arrowPs);
  pContext->StrokePath(arrowPs);

  // Arrow Sd
  wxPoint2DDouble arrowPosSd(origin.m_x + xChartRange + spaceArrow, origin.m_y);
  wxGraphicsPath arrowSd = pContext->CreatePath();
  pContext->SetBrush(wxBrush(wxColour(0, 0, 0), wxBRUSHSTYLE_SOLID));
  arrowSd.MoveToPoint(arrowPosSd);
  arrowSd.AddLineToPoint(arrowPosSd.m_x, arrowPosSd.m_y - arrowWidth / 2);
  arrowSd.AddLineToPoint(arrowPosSd.m_x + arrowLength, arrowPosSd.m_y);
  arrowSd.AddLineToPoint(arrowPosSd.m_x, arrowPosSd.m_y + arrowWidth / 2);
  arrowSd.CloseSubpath();
  pContext->FillPath(arrowSd);
  pContext->StrokePath(arrowSd);

  wxPaintDC dc(this);
  wxSize textSizePs = dc.GetTextExtent("Ps");

  pContext->SetFont(*wxNORMAL_FONT, wxColor(*wxBLACK));
  pContext->DrawText(_T("Ps"), arrowPosPs.m_x, arrowPosPs.m_y - arrowLength - textSizePs.y);
  pContext->DrawText(_T("Sd"), arrowPosSd.m_x + arrowLength, arrowPosSd.m_y);
}

void GlaserDiagram::drawTicks(wxGraphicsContext* pContext, const wxPoint2DDouble& origin, double xChartRange, double yChartRange, double tickLength)
{
  if (m_pGlaserData == nullptr)
  {
    return;
  }

  int insideValue = m_pParameter->PsInside;
  int outsideValue = m_pParameter->PsOutside;

  wxPaintDC dc(this);
  wxSize textSizeInsideValue = dc.GetTextExtent(wxString::FromDouble(insideValue));
  wxSize textSizeOutsideValue = dc.GetTextExtent(wxString::FromDouble(outsideValue));

  pContext->SetFont(*wxNORMAL_FONT, wxColor(*wxBLACK));
  pContext->DrawText(wxString::FromDouble(insideValue), origin.m_x - textSizeInsideValue.GetWidth() - tickLength, origin.m_y - yChartRange - ((double)textSizeInsideValue.y / 2));
  int yPosOutsideValue = origin.m_y - (yChartRange * m_pParameter->PsOutside / m_pParameter->PsInside);
  pContext->DrawText(wxString::FromDouble(outsideValue), origin.m_x - textSizeOutsideValue.GetWidth() - tickLength, yPosOutsideValue - ((double)textSizeOutsideValue.y / 2));

  // X ticks
  double xPos(origin.m_x);
  double xStep(xChartRange / 10);

  for (int i = 0; i < 11; ++i)
  {
    pContext->SetPen(*wxBLACK_PEN);
    pContext->StrokeLine(xPos, origin.m_y + tickLength/2, xPos, origin.m_y - tickLength / 2);

    xPos += xStep;
  }

  // Y ticks
  double yPos(origin.m_y);
  double yStep(yChartRange / 10);

  for (int i = 0; i < 11; ++i)
  {
    pContext->SetPen(*wxBLACK_PEN);
    pContext->StrokeLine(origin.m_x - tickLength / 2, yPos, origin.m_x + tickLength / 2, yPos);

    yPos -= yStep;
  }
}
