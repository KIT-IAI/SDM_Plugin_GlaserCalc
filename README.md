# GlaserCalc
The GlaserCalc plug-in is based on the Glaser method, a mathematical verification method in accordance with DIN 4108-3, to determining whether and where condensation occurs in a building structure. The material structure of individual IFC building elements is used. 
The existing parameters for an IFC building element selected in the scene are transferred to the Glaser dialoge. The layer structure with the name of the individual layers and the layer thicknesses is taken over. If a component layer also has material properties, the plug-in checks whether a value exists for the thermal conductivity. This value is located in the PropertySet "ThermalMaterialProperties" up to IFC2x3 and in the PropertySet "Pset_MaterialThermal" from IFC4 onwards.
Missing values e.g. for the thermal conductivity coefficient λ and the vapour diffusion resistance coefficient μ can be added manually.

<img width="1545" alt="GlaserCalc" src="https://github.com/KIT-IAI/SDM_Plugin_GlaserCalc/assets/7059379/aabe8744-a632-4c61-a47e-38ebc8ae3469">

## User Interface
The user interface was made with the aid of [wxFormBuilder](https://github.com/wxFormBuilder/wxFormBuilder).
