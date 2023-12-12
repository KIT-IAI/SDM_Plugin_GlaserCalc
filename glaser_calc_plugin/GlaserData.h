#pragma once

struct LayerData
{
  std::wstring name;
  double width = 0.0;
  double mue = 0.0;
  double lambda = 0.0;
  double R = 0.0;

  double calcSd() const
  {
    if (mue != 0.0)
    {
      return (width * mue);
    }
    else
    {
      return width;
    }
  }
};

struct ParameterData
{
  ParameterData() = default;
  ParameterData(const std::wstring& name)
    : name(name) {}

  ParameterData(const ParameterData& other)
  {
    name = other.name;
    RsOutside = other.RsOutside;
    RsInside = other.RsInside;
    PhiInside = other.PhiInside;
    PhiOutside = other.PhiOutside;
    ThetaInside = other.ThetaInside;
    ThetaOutside = other.ThetaOutside;
    PsInside = other.PsInside;
    PsOutside = other.PsOutside;
  }

  bool operator == (const ParameterData& other)
  {
    return (name == other.name &&
            RsOutside == other.RsOutside &&
            RsInside == other.RsInside &&
            PhiInside == other.PhiInside &&
            PhiOutside == other.PhiOutside &&
            ThetaInside == other.ThetaInside &&
            ThetaOutside == other.ThetaOutside &&
            PsInside == other.PsInside &&
            PsOutside == other.PsOutside);
  };

  std::wstring name;
  double RsOutside = 0.0;
  double RsInside = 0.0;
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
    mT = 0.0;
    mV = 0.0;
  }

  std::vector<double> Ps;
  std::vector<double> T;
  double mT = 0.0;
  double mV = 0.0;
};

struct GlaserData
{
  std::wstring elementName;
  std::wstring elementType;
  std::vector<LayerData> layers;
  std::unordered_map<std::wstring, ParameterData> parameterSets;
  ParameterData* pCurrentParameterData = nullptr;
  Results results;
};
