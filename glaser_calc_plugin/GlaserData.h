#pragma once

struct LayerData
{
  std::wstring name;
  double width = 0.0;
  double mue = 0.0;
  double lambda = 0.0;
  double Sd = 0.0;
  double R = 0.0;
};

struct ParameterData
{
  std::wstring name;
  double ROutside = 0.0;
  double RInside = 0.0;
  double PhiInside = 0.0;
  double PhiOutside = 0.0;
  double ThetaInside = 0.0;
  double ThetaOutside = 0.0;
  int PsInside = 0;
  int PsOutside = 0;
};

struct Results
{
  void clear()
  {
    Ps.clear();
    T.clear();
  }

  std::vector<double> Ps;
  std::vector<double> T;
};

struct GlaserData
{
  std::wstring elementName;
  std::wstring elementType;
  std::vector<LayerData> layers;
  std::unordered_map<std::wstring, ParameterData> parameterSets;
  Results results;
};
