#include "GlaserCalcDlgImpl.h"
#include <LiveLogFeature.hpp>

GlaserCalc::GlaserCalc(IfcDB::Populationi* pDB, IfcDB::utils::PopulationStates* pStates, sdm::plugin::LiveLogInterface* pLogger)
  : m_pDB(pDB), m_pStates(pStates), m_pLogger(pLogger)
{
  // Dew period parameter
  ParameterData parameterDewPeriod;
  parameterDewPeriod.name = L"DewPeriod";
  parameterDewPeriod.RsOutside = 0.04;
  parameterDewPeriod.RsInside = 0.13;
  parameterDewPeriod.PhiInside = 0.5;
  parameterDewPeriod.PhiOutside = 0.8;
  parameterDewPeriod.ThetaInside = 20.0;
  parameterDewPeriod.ThetaOutside = -10.0;
  parameterDewPeriod.PsInside = 2340;
  parameterDewPeriod.PsOutside = 260;

  ParameterData parameterEvaporationPeriod;
  parameterEvaporationPeriod.name = L"EvaporationPeriod";
  parameterEvaporationPeriod.RsOutside = 0.04;
  parameterEvaporationPeriod.RsInside = 0.13;
  parameterEvaporationPeriod.PhiInside = 0.7;
  parameterEvaporationPeriod.PhiOutside = 0.7;
  parameterEvaporationPeriod.ThetaInside = 12.0;
  parameterEvaporationPeriod.ThetaOutside = 12.0;
  parameterEvaporationPeriod.PsInside = 1403;
  parameterEvaporationPeriod.PsOutside = 1403;

  ParameterData parameterUserDefinedPeriod;
  parameterUserDefinedPeriod.name = L"UserDefinedPeriod";

  m_GlaserData.parameterSets.emplace(parameterDewPeriod.name, parameterDewPeriod);
  m_GlaserData.parameterSets.emplace(parameterEvaporationPeriod.name, parameterEvaporationPeriod);
  m_GlaserData.parameterSets.emplace(parameterUserDefinedPeriod.name, parameterUserDefinedPeriod);
}

void GlaserCalc::updateValues(IfcDB::ifcOid oid)
{
  if (m_pGlaserCalcDlg == nullptr)
  {
    return;
  }

  m_GlaserData.layers.clear();

  auto pEntity = m_pDB->get(oid);

  if (pEntity != nullptr)
  {
    m_GlaserData.elementName = pEntity->getName();
    m_GlaserData.elementType = IfcDB::getTypeOfEntityAsString(pEntity->getType());

    IfcDB::IfcRelationList relations;
    IfcDB::IfcRelationList typeRelations;

    m_pDB->getRelation(pEntity->getOid(), IfcDB::REL_ASSOCIATES_MATERIAL, relations);

    if (relations.empty())
    {
      m_pDB->getRelation(pEntity->getOid(), IfcDB::REL_DEFINES_BY_TYPE, typeRelations);

      if (typeRelations.empty() != true)
      {
        IfcDB::IfcRelDefType* pRelDefinesType = dynamic_cast<IfcDB::IfcRelDefType*>(typeRelations.front());
        IfcDB::IfcEntityType* pEntityType = pRelDefinesType->getRelatingType();
        m_pDB->getRelation(pEntityType->getOid(), IfcDB::REL_ASSOCIATES_MATERIAL, relations);
      }
    }

    for (auto pRelation : relations)
    {
      IfcDB::IfcRelMaterial* pRelMaterial = dynamic_cast<IfcDB::IfcRelMaterial*>(pRelation);

      IfcDB::Material::MaterialBase* pMaterial = pRelMaterial->getMaterial();

      if (pMaterial != nullptr)
      {
        processMaterial(pMaterial);
      }
    }

    m_pGlaserCalcDlg->setGlaserCalc(*this);

    m_GlaserData.pCurrentParameterData = m_pGlaserCalcDlg->getCurrentParameterData();

    calc();

    m_pGlaserCalcDlg->updateValues();
  }
}

void GlaserCalc::processMaterial(IfcDB::Material::MaterialBase* pMaterialBase)
{
  double unitFactor = m_pDB->getUnitFactor(_T("LENGTHUNIT")) / 1000;

  if (pMaterialBase->getMaterialType() == IfcDB::MATERIAL)
  {
    IfcDB::Material* pMaterial = dynamic_cast<IfcDB::Material*>(pMaterialBase);

    LayerData layer;
    layer.name = pMaterial->m_MaterialName;

    checkMaterialProperties(layer, pMaterial->m_Properties);

    m_GlaserData.layers.emplace_back(layer);
  }
  else if (pMaterialBase->getMaterialType() == IfcDB::MATERIAL_LAYER_SET)
  {
    IfcDB::MaterialLayerSet* pMaterialLayerSet = dynamic_cast<IfcDB::MaterialLayerSet*>(pMaterialBase);

    if (pMaterialLayerSet->m_MaterialLayers.empty() == false)
    {
      for (auto pLayer : pMaterialLayerSet->m_MaterialLayers)
      {
        LayerData layer;
        layer.name = pLayer->m_MaterialName;
        layer.width = pLayer->m_width * unitFactor;

        checkMaterialProperties(layer, pLayer->m_Properties);

        m_GlaserData.layers.emplace_back(layer);
      }
    }
  }
  else if (pMaterialBase->getMaterialType() == IfcDB::MATERIAL_LAYER_SET_USAGE)
  {
    IfcDB::MaterialLayerSetUsage* pMaterialLayerSetUsage = dynamic_cast<IfcDB::MaterialLayerSetUsage*>(pMaterialBase);

    if (pMaterialLayerSetUsage->m_MaterialLayers.empty() == false)
    {
      for (auto pLayer : pMaterialLayerSetUsage->m_MaterialLayers)
      {
        LayerData layer;
        layer.name = pLayer->m_MaterialName;
        layer.width = pLayer->m_width * unitFactor;

        checkMaterialProperties(layer, pLayer->m_Properties);

        m_GlaserData.layers.emplace_back(layer);
      }
    }
  }
  else if (pMaterialBase->getMaterialType() == IfcDB::MATERIAL_LIST)
  {
    IfcDB::MaterialList* pMaterialList = dynamic_cast<IfcDB::MaterialList*>(pMaterialBase);

    for (auto pMaterial : pMaterialList->m_Materials)
    {
      LayerData layer;
      layer.name = pMaterial->m_MaterialName;

      checkMaterialProperties(layer, pMaterial->m_Properties);

      m_GlaserData.layers.emplace_back(layer);
    }
  }
  else if (pMaterialBase->getMaterialType() == IfcDB::MATERIAL_PROFILE_SET)
  {
    IfcDB::MaterialProfileSet* pMaterialProfileSet = dynamic_cast<IfcDB::MaterialProfileSet*>(pMaterialBase);

    if (pMaterialProfileSet->m_MaterialProfiles.empty() == false)
    {
      for (auto pMaterialProfile : pMaterialProfileSet->m_MaterialProfiles)
      {
        LayerData layer;
        layer.name = pMaterialProfile->m_Name;

        checkMaterialProperties(layer, pMaterialProfile->m_Properties);

        m_GlaserData.layers.emplace_back(layer);
      }
    }
  }
  else if (pMaterialBase->getMaterialType() == IfcDB::MATERIAL_PROFILE_SET_USAGE)
  {
    IfcDB::MaterialProfileSetUsage* pMaterialProfileSetUsage = dynamic_cast<IfcDB::MaterialProfileSetUsage*>(pMaterialBase);

    if (pMaterialProfileSetUsage->m_MaterialProfiles.empty() == false)
    {
      for (auto pMaterialProfile : pMaterialProfileSetUsage->m_MaterialProfiles)
      {
        LayerData layer;
        layer.name = pMaterialProfile->m_Name;

        checkMaterialProperties(layer, pMaterialProfile->m_Properties);

        m_GlaserData.layers.emplace_back(layer);
      }
    }
  }
  else if (pMaterialBase->getMaterialType() == IfcDB::MATERIAL_CONSTITUENT)
  {
    IfcDB::MaterialConstituent* pMaterialConstituent = dynamic_cast<IfcDB::MaterialConstituent*>(pMaterialBase);

    LayerData layer;
    layer.name = pMaterialConstituent->m_Name;

    checkMaterialProperties(layer, pMaterialConstituent->m_pMaterial->m_Properties);

    m_GlaserData.layers.emplace_back(layer);
  }
  else if (pMaterialBase->getMaterialType() == IfcDB::MATERIAL_CONSTITUENT_SET)
  {
    IfcDB::MaterialConstituentSet* pMaterialConstituentSet = dynamic_cast<IfcDB::MaterialConstituentSet*>(pMaterialBase);

    if (pMaterialConstituentSet->m_MaterialConstituents.empty() == false)
    {
      for (auto pMaterialConstituent : pMaterialConstituentSet->m_MaterialConstituents)
      {
        LayerData layer;
        layer.name = pMaterialConstituent->m_Name;

        checkMaterialProperties(layer, pMaterialConstituent->m_pMaterial->m_Properties);

        m_GlaserData.layers.emplace_back(layer);
      }
    }
  }
}

void GlaserCalc::checkMaterialProperties(LayerData& layerData, std::vector<IfcDB::Property*>& vProperties)
{
  std::tstring propertyValue;

  for (auto pProperty : vProperties)
  {
    // ---------------------
    // ThermalConductivity
    // ---------------------
    // Material properties in IFC version >= IFC4
    IfcDB::Property* pMaterialThermal = pProperty->find(_T("Pset_MaterialThermal"), _T(""));

    if (pMaterialThermal != nullptr)
    {
      if (pMaterialThermal->findValue(_T("Pset_MaterialThermal"), _T("ThermalConductivity"), propertyValue) != nullptr)
      {
        layerData.lambda = _ttof(propertyValue.c_str());
      }
    }
    else
    {
      // Material properties in IFC version < IFC4
      pMaterialThermal = pProperty->find(_T("ThermalMaterialProperties"), _T(""));

      if (pMaterialThermal != nullptr)
      {
        if (pMaterialThermal->findValue(_T("ThermalMaterialProperties"), _T("ThermalConductivity"), propertyValue) != nullptr)
        {
          layerData.lambda = _ttof(propertyValue.c_str());
        }
      }
    }
  }
}

double GlaserCalc::calcPs(double phi)
{
  if (phi > 0)
  {
    return (288.68 * pow((1.0981 + (phi / 100.0)), 8.02));
  }
  else
  {
    return (4.689 * pow((1.486 + (phi / 100.0)), 12.3));
  }
}

void GlaserCalc::calc()
{
  m_GlaserData.results.clear();

  double R(0.0);
  double Sd(0.0);

  for (auto& layer : m_GlaserData.layers)
  {
    Sd += layer.calcSd();

    if (layer.lambda != 0)
    {
      layer.R = (layer.width / layer.lambda);
    }

    R += layer.R;
  }

  if (m_GlaserData.pCurrentParameterData != nullptr)
  {
    std::tstring Value, ValueN;

    double dT = m_GlaserData.pCurrentParameterData->ThetaInside - m_GlaserData.pCurrentParameterData->ThetaOutside;
    double k = 1 / (m_GlaserData.pCurrentParameterData->RsOutside + m_GlaserData.pCurrentParameterData->RsInside + R);
    double q = k * dT;

    double T = m_GlaserData.pCurrentParameterData->ThetaInside - q * (m_GlaserData.pCurrentParameterData->RsInside);

    m_GlaserData.results.T.emplace_back(T);
    m_GlaserData.results.Ps.emplace_back(calcPs(T));

    for (auto& layer : m_GlaserData.layers)
    {
      T = T - (q * layer.R);

      m_GlaserData.results.T.emplace_back(T);
      m_GlaserData.results.Ps.emplace_back(calcPs(T));
    }

    if (!m_GlaserData.results.Ps.empty())
    {
      // To make a calculation, it is assumed that Indoor air = 20°C at 50% relative humidity and
      // outdoor air = -10°C at 80% relative humidity.
      double PsInside = m_GlaserData.pCurrentParameterData->PsInside / 100.0 * 50;
      double PsOutside = m_GlaserData.pCurrentParameterData->PsOutside / 100.0 * 80;

      int i(0);
      double SdLayer(0.0);

      for (auto& layer : m_GlaserData.layers)
      {
        ++i;

        SdLayer += layer.calcSd();

        double Ps = PsInside - (PsInside - PsOutside) / Sd * SdLayer;

        if (m_GlaserData.results.Ps[i] < Ps)
        {
          // condensation calculation

          m_GlaserData.results.mT = 1440 * ((PsInside - m_GlaserData.results.Ps[i]) / SdLayer - (m_GlaserData.results.Ps[i] - PsOutside) / (Sd - SdLayer)) / 1500000;

          // According to DIN 1408-3,
          // a constant temperature of 12°C inside and outside at a relative humidity of 70%
          // is a prerequisite for the calculation for the evaporation period.
          Ps = calcPs(12.0);
          double PsRed = Ps / 100.0 * 70;
          m_GlaserData.results.mV = 2160 * ((Ps - PsRed) / SdLayer + ((Ps - PsRed) / (Sd - SdLayer))) / 1500000;
        }
      }
    }
  }
}
