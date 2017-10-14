#!/usr/bin/env python

import vtk


# ImageSets = List of Image sets
# Weights  = List of wieghts e.g [1, 1, 1]

def SumVTKImages(ImageSets, Weights):
    NumOfImages = len(ImageSets)
    SumFilter = vtk.vtkImageWeightedSum()
    for x in range(0, NumOfImages, 1):
        SumFilter.AddInputConnection(ImageSets[x])
        SumFilter.SetWeight(x, Weights[x])
    SumFilter.Update()

    # Return summed Image as vtkImageData
    return SumFilter.GetOutput()
