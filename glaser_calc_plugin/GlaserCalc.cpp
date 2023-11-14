#include "GlaserCalcDlgImpl.h"
#include <LiveLogFeature.hpp>

GlaserCalc::GlaserCalc(IfcDB::Populationi* pDB, IfcDB::utils::PopulationStates* pStates, sdm::plugin::LiveLogInterface* pLogger)
  : m_pDB(pDB), m_pStates(pStates), m_pLogger(pLogger)
{
  // Dew period parameter
  ParameterData parameterDewPeriod;
  parameterDewPeriod.name = L"DewPeriod";
  parameterDewPeriod.ROutside = 0.04;
  parameterDewPeriod.RInside = 0.13;
  parameterDewPeriod.PhiInside = 0.5;
  parameterDewPeriod.PhiOutside = 0.8;
  parameterDewPeriod.ThetaInside = 20.0;
  parameterDewPeriod.ThetaOutside = -10.0;
  parameterDewPeriod.PsInside = 2340;
  parameterDewPeriod.PsOutside = 260;

  ParameterData parameterEvaporationPeriod;
  parameterEvaporationPeriod.name = L"EvaporationPeriod";
  parameterEvaporationPeriod.ROutside = 0.04;
  parameterEvaporationPeriod.RInside = 0.13;
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

    calc();

    m_pGlaserCalcDlg->setGlaserCalc(*this);
    m_pGlaserCalcDlg->updateValues();

  }
}

void GlaserCalc::processMaterial(IfcDB::Material::MaterialBase* pMaterialBase)
{
  if (pMaterialBase->getMaterialType() == IfcDB::MATERIAL)
  {
    IfcDB::Material* pMaterial = dynamic_cast<IfcDB::Material*>(pMaterialBase);

    LayerData layer;
    layer.name = pMaterial->m_MaterialName;

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
        layer.width = pLayer->m_width;

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
        layer.width = pLayer->m_width;

        for (auto pProperty : pLayer->m_Properties)
        {
          IfcDB::Property* pMaterialThermal = pProperty->find(_T("Pset_MaterialThermal"), _T(""));

          if (pMaterialThermal != nullptr)
          {
            std::tstring propertyValue;

            if (pMaterialThermal->findValue(_T("Pset_MaterialThermal"), _T("ThermalConductivity"), propertyValue) != nullptr)
            {
              layer.lambda = _ttof(propertyValue.c_str());
            }
          }
        }

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

        m_GlaserData.layers.emplace_back(layer);
      }
    }
  }
  else if (pMaterialBase->getMaterialType() == IfcDB::MATERIAL_CONSTITUENT)
  {
    IfcDB::MaterialConstituent* pMaterialConstituent = dynamic_cast<IfcDB::MaterialConstituent*>(pMaterialBase);

    LayerData layer;
    layer.name = pMaterialConstituent->m_Name;

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

        m_GlaserData.layers.emplace_back(layer);
      }
    }
  }
}

void GlaserCalc::calc()
{
  m_GlaserData.results.clear();

  double unitFactor = m_pDB->getUnitFactor(_T("LENGTHUNIT")) / 1000;

  double R(0.0);

  for (auto& layer : m_GlaserData.layers)
  {
    if (layer.mue != 0.0)
    {
      layer.Sd = layer.width * unitFactor * layer.mue;
    }
    else
    {
      layer.Sd = layer.width * unitFactor;
    }

    if (layer.lambda != 0)
    {
      layer.R = (layer.width * unitFactor / layer.lambda);
    }

    R += layer.R;
  }

  auto it = m_GlaserData.parameterSets.find(L"DewPeriod");

  std::tstring Value, ValueN;

  double dT = it->second.ThetaInside - it->second.ThetaOutside;
  double k = 1 / (it->second.ROutside + it->second.RInside + R);
  double q = k * dT;

  double T = it->second.ThetaInside - q * (it->second.RInside);

  m_GlaserData.results.T.emplace_back(T);
  m_GlaserData.results.Ps.emplace_back((288.88 * pow((1.098 + (T / 100.0)), 8.02)));

  for (auto& layer : m_GlaserData.layers)
  {
    T = T - (q * layer.R);

    m_GlaserData.results.T.emplace_back(T);
    m_GlaserData.results.Ps.emplace_back((288.88 * pow((1.098 + (T / 100.0)), 8.02)));
  }
}
