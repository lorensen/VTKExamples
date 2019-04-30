### Description

vtkDiscretizableColorTransferFunction object is a cross between a vtkColorTransferFunction and vtkLookupTable selectively combining the functionality of both. 

This class is a vtkColorTransferFunction allowing users to specify the RGB control points that control the color transfer function. At the same time, by setting Discretize to 1 (true), one can force the transfer function to only have NumberOfValues discrete colors.
