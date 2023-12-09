#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "PluginGlaserCalc.h"
#include "GlaserCalcDlgImpl.h"

#include "IFCDBInterfaceVersion.hpp"
#include "PluginInterfaceVersion.hpp"

using namespace std;
using namespace sdm::plugin;

IMPLEMENT_PLUGIN(PluginGlaserCalc);

GlaserCalcAction::GlaserCalcAction()
  : ActionFeature("Glaser Calc")
{
}

GlaserCalcAction::~GlaserCalcAction()
{
  delete m_pGlaserCalc;
  delete m_pObserver;
}

void GlaserCalcAction::execute() const
{

  wxInitialize();

  auto pDlg = new GlaserCalcDlgImpl(nullptr, wxID_ANY, wxT("Glaser Calculation"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE);

  m_pGlaserCalc->setGlaserCalcDlg(pDlg);

  IfcDB::tOidSet selectedOids = m_pStates->getSelectedEntities();

  if (selectedOids.empty() == false)
  {
    m_pGlaserCalc->updateValues(*selectedOids.begin());
  }

  pDlg->Show();
}

PluginGlaserCalc::PluginGlaserCalc()
{
	m_liveLogObserver.attach([this](LiveLogInterface* pLogger) { m_GlaserCalcAction.setLogger(pLogger); });
  m_documentObserver.attach([this](IfcDB::Populationi* pDB) { m_GlaserCalcAction.setDB(pDB); IfcDB::assignGlobalStates(pDB); } );
	m_documentObserver.attach([this](IfcDB::utils::PopulationSubject* pStates) { m_GlaserCalcAction.setStates(dynamic_cast<IfcDB::utils::PopulationStates*>(pStates)); });
}

Version PluginGlaserCalc::getInterfaceVersion() const
{
  return Version();
}

PluginInfo PluginGlaserCalc::getInfo() const
{
  PluginInfo info;
  info.name        = "Glaser Calc";
  info.description = "Glaser diagram calculation for a selected building element";
  info.version     = { 0, 1 };

  return info;
}

std::vector<Feature*> PluginGlaserCalc::getFeatures() const
{
  std::vector<Feature*> features;

  features.emplace_back(const_cast<LiveLogObserver*>(&m_liveLogObserver));
  features.emplace_back(const_cast<DocumentObserverImpl*>(&m_documentObserver));
  features.emplace_back(const_cast<GlaserCalcAction*>(&m_GlaserCalcAction));

  return features;
}

ComponentInfo PluginGlaserCalc::getComponentInfo(const RequiredComponent& requiredComponent) const
{
  if (requiredComponent.version == IFCDB_INTERFACE_COMPONENT_VERSION)
  {
    return { ComponentState::SUPPORTED, std::string{IFCDB_INTERFACE_COMPONENT_VERSION} };
  }

  if (requiredComponent.version == PLUGIN_INTERFACE_COMPONENT_VERSION)
  {
    return { ComponentState::SUPPORTED, std::string{PLUGIN_INTERFACE_COMPONENT_VERSION} };
  }

  return { ComponentState::UNSUPPORTED, "" };
}

const sdm::plugin::InitializationState& PluginGlaserCalc::getInitializationState() const
{
  return m_initState;
}
