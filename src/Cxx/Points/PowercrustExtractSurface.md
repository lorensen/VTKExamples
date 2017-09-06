### Description
The Powercrust, or Crust algorithm, reconstructs surfaces from unorganized points. See [The Power Crust](http://web.cs.ucdavis.edu/~amenta/pubs/sm.pdf) for technical details.

!!! danger
    The code is covered by the [GPL License](http://www.gnu.org/copyleft/gpl.html) and may restrict commercial use.. 

!!! seealso
    [ExtractSurface](/Cxx/Points/ExtractSurface) reconstructs surfaces and is included with the VTK distribution.

!!! info
    The Power Crust is implemented as a [VTK Remote Module](http://www.vtk.org/Wiki/VTK/Remote_Modules).

To use the Power Crust in VTK:

1. Download [Powercrust.remote.cmake](https://github.com/lorensen/Powercrust/blob/master/Powercrust.remote.cmake) and place it in your *VTK/Remote* directory.
2. Reconfigure your VTK build with *cmake*
3. Enable the remote module by setting *Module_Powercrust:BOOL=ON*.
4. `make`
