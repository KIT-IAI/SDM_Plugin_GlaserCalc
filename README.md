# GlaserCalc
The GlaserCalc plug-in is based on the Glaser method, a mathematical verification method in accordance with DIN 4108-3, to determining whether and where condensation occurs in a component structure.

For the calculation the plug-in uses the material information of individual IFC building elements. 
The existing parameters for an IFC building element selected in the scene are transferred to the Glaser dialoge. The layer structure with the name of the individual layers and the layer thicknesses is taken over. If a component layer also has material properties, the plug-in checks whether a value exists for the thermal conductivity. This value is located in the PropertySet **ThermalMaterialProperties** up to **IFC2x3** and in the PropertySet **Pset_MaterialThermal** from **IFC4** onwards.
Missing values e.g. for the thermal conductivity coefficient λ and the vapour diffusion resistance coefficient μ can be added manually.

<img width="1545" alt="GlaserCalcPlugin" src="https://github.com/KIT-IAI/SDM_Plugin_GlaserCalc/assets/7059379/aabe8744-a632-4c61-a47e-38ebc8ae3469">

## User Interface
The user interface is based on [wxWidgets](https://www.wxwidgets.org/) and was made with [wxFormBuilder](https://github.com/wxFormBuilder/wxFormBuilder).

## Dependencies

### Use of vcpkg:

|Package Name         |Install Command                            |
|:---                 |:---                                       |
|wxwidgets            |vcpkg install wxwidgets triplet=x64-windows|

### How to cite:

```bibtex
@software{SDM_Plugin_GlaserCalc,
	title        = {SDM_Plugin_Papermodel},
	author       = {{Andreas Geiger}},
	url          = {https://github.com/KIT-IAI/SDM_Plugin_Papermodel},
	date         = {2023}
}
```
