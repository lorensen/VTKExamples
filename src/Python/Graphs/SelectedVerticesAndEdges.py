#!/usr/bin/env python
from __future__ import print_function

import vtk

source = vtk.vtkRandomGraphSource()
source.Update()

view = vtk.vtkGraphLayoutView()
view.AddRepresentationFromInputConnection(source.GetOutputPort())


def selectionCallback(caller, event):

    # In C++ there is some extra data passed to the callback, but in Python
    # the callback data is lost...

    # There should be two selection nodes, but which one is vertices and which
    # is edges does not seem to be guaranteed...
    sel = caller.GetCurrentSelection()
    node0 = sel.GetNode(0)
    node0_field_type = node0.GetFieldType()
    sel_list0 = caller.GetCurrentSelection().GetNode(0).GetSelectionList()
    node1 = sel.GetNode(1)
    node1_field_type = node1.GetFieldType()
    sel_list1 = caller.GetCurrentSelection().GetNode(1).GetSelectionList()

    if (sel_list0.GetNumberOfTuples() > 0):
        printFieldType(node0_field_type)
        for ii in range(sel_list0.GetNumberOfTuples()):
            print("\t", sel_list0.GetValue(ii))

    if (sel_list1.GetNumberOfTuples() > 0):
        printFieldType(node1_field_type)
        for ii in range(sel_list1.GetNumberOfTuples()):
            print("\t", sel_list1.GetValue(ii))

        print("- - -")


def printFieldType(field_type):

    if field_type == 3:
        print("Vertices Selected:")
    elif field_type == 4:
        print("Edges Selected:")
    else:
        print("Unknown type:")


rep = view.GetRepresentation(0)

# The vtkRenderedGraphRepresentation should already have a vtkAnnotationLink,
# so we just want to grab it and add an observer with our callback function
# attached
link = rep.GetAnnotationLink()
link.AddObserver("AnnotationChangedEvent", selectionCallback)

view.GetRenderWindow().SetSize(600, 600)
view.ResetCamera()
view.Render()
view.GetInteractor().Start()
