### Description

This example uses vtkPointInterpolator probe a high resolution dataset with a lower resolution dataset. Then, using vtkInterpolateDataSetAttributes, interpolate between the original low resolution data and the probed, low resolution data.

!!! warning
    For the vtkPointInterpolator, point arrays will not be interpolated unless PassPointArrays is off.     vtkPointInterpolator does not interpolate vtkFieldData. To interpolate vtkFieldData it must be added as the active scalar.


!!! warning
    vtkInterpolateDataSetAttibutes does not interpolate vtkFieldData. To interpolate vtkFieldData it must be added as the active scalar.

!!! info "Thanks"
    This example was inspired by Andrew E. Slaughter, Idaho National Laboratory.
