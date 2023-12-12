#pragma once

#include <ifcdb/IfcDbInclude.h>
#include <ifcdb/utils/PopulationObserver.hpp>
#include <unordered_map>
#include "GlaserData.h"

namespace sdm
{
	namespace plugin
	{
		class LiveLogInterface;
	}
}

class GlaserCalcDlgImpl;

class GlaserCalc
{
  public:
    GlaserCalc(IfcDB::Populationi* pDB, IfcDB::utils::PopulationStates* pStates, sdm::plugin::LiveLogInterface* pLogger);
    ~GlaserCalc() = default;

    void setGlaserCalcDlg(GlaserCalcDlgImpl* pDlg) { m_pGlaserCalcDlg = pDlg; }
    GlaserData& getGlaserData() { return m_GlaserData; }
    void updateValues(IfcDB::ifcOid oid);
    void calc();

  private:
    void processMaterial(IfcDB::MaterialBase* pMaterialBase);
    void checkMaterialProperties(LayerData& layerData, std::vector<IfcDB::Property*>& vProperties);
    double calcPs(double phi);

  private:
    IfcDB::Populationi* m_pDB = nullptr;
		IfcDB::utils::PopulationStates* m_pStates = nullptr;
		sdm::plugin::LiveLogInterface* m_pLogger = nullptr;

    GlaserData m_GlaserData;

    GlaserCalcDlgImpl* m_pGlaserCalcDlg = nullptr;
};
