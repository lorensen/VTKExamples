### Description

vtkCaptionWidget object provides support for interactively placing a caption on the 2D overlay plane. 

A caption is defined by some text with a leader (e.g., arrow) that points from the text to a point in the scene. 

The caption is represented by a vtkCaptionRepresentation. It uses the event bindings of its superclass (vtkBorderWidget) to control the placement of the text, and adds the ability to move the attachment point around. In addition, when the caption text is selected, the widget emits a ActivateEvent that observers can watch for. This is useful for opening GUI dialogoues to adjust font characteristics, etc.
