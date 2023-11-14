#pragma once

#include <ifcdb/utils/PopulationObserver.hpp>

class GlaserCalc;

class PluginObserver final : public IfcDB::utils::PopulationObserver
{
 public:
    explicit PluginObserver(GlaserCalc& glaserCalc);
    ~PluginObserver() override = default;

    void selectEntity(IfcDB::ifcOid oid, bool selected) override;

 private:
     GlaserCalc& m_GlaserCalc;
};