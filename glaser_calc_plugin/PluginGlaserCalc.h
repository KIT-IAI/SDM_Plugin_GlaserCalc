#pragma once

#include <Plugin.hpp>
#include <ActionFeature.hpp>
#include <DocumentObserver.hpp>
#include <LiveLogFeature.hpp>
#include <LogDialogFeature.hpp>
#include <LogDialogFeatureHelper.hpp>
#include <ifcdb/IfcDbInclude.h>
#include <ifcdb/utils/PopulationObserver.hpp>
#include "GlaserCalc.h"
#include "PluginObserver.h"

class GlaserCalcAction : public sdm::plugin::ActionFeature
{
  public:
    GlaserCalcAction();
    ~GlaserCalcAction() override;

    void execute() const override;

    void setLogger(sdm::plugin::LiveLogInterface* pLogger) { m_pLogger = pLogger; }
    void setDB(IfcDB::Populationi* pDB) { m_pDB = pDB; }
    void setStates(IfcDB::utils::PopulationStates* pSates)
    { 
      m_pStates = pSates;
      m_pGlaserCalc = new GlaserCalc(m_pDB, m_pStates, m_pLogger);
      m_pObserver = new PluginObserver(*m_pGlaserCalc);
      m_pStates->subscribe(*m_pObserver);
    }

  protected:
    sdm::plugin::LiveLogInterface* m_pLogger = nullptr;
    IfcDB::Populationi* m_pDB = nullptr;
    IfcDB::utils::PopulationStates* m_pStates = nullptr;
    GlaserCalc* m_pGlaserCalc = nullptr;
    PluginObserver* m_pObserver = nullptr;
};

class PluginGlaserCalc : public sdm::plugin::Plugin
{
  public:
    PluginGlaserCalc();
    ~PluginGlaserCalc() override = default;

    sdm::plugin::Version getInterfaceVersion() const override;
    sdm::plugin::PluginInfo getInfo() const override;
    std::vector<sdm::plugin::Feature*> getFeatures() const override;

    sdm::plugin::ComponentInfo getComponentInfo(const sdm::plugin::RequiredComponent& requiredComponent) const override;
    const sdm::plugin::InitializationState& getInitializationState() const override;

    IfcDB::Populationi* m_pDB = nullptr;
    IfcDB::utils::PopulationStates* m_States = nullptr;

  private:
    sdm::plugin::DocumentObserverImpl m_documentObserver;
    sdm::plugin::LiveLogObserver m_liveLogObserver;
    GlaserCalcAction m_GlaserCalcAction;
    sdm::plugin::InitializationState m_initState;
};