#include "PluginObserver.h"
#include "GlaserCalc.h"

PluginObserver::PluginObserver(GlaserCalc& glaserCalc)
    : m_GlaserCalc(glaserCalc)
{
}

void PluginObserver::selectEntity(IfcDB::ifcOid oid, bool selected)
{
  m_GlaserCalc.updateValues(oid);
}
