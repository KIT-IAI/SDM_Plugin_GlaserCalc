#pragma once

#include <wx/wx.h>

struct GlaserData;
struct ParameterData;

class GlaserDiagram : public wxControl
{
  public:
    GlaserDiagram(wxWindow* parent);

    void OnPaint(wxPaintEvent& event);

    void setParameterData(const ParameterData* pParameter) { m_pParameter = pParameter; }
    void setGlaserData(const GlaserData* pGlaserData) { m_pGlaserData = pGlaserData; }

  private:
    void drawCoordAxis(wxGraphicsContext* pContext, const wxPoint2DDouble& origin, double xChartRange, double yChartRange, double arrowLength, double arrowWidth);
    void drawTicks(wxGraphicsContext* pContext, const wxPoint2DDouble& origin, double xChartRange, double yChartRange, double tickLength);

  private:
    const GlaserData* m_pGlaserData = nullptr;
    const ParameterData* m_pParameter = nullptr;
};