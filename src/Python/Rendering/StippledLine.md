### Description

VTK OpenGL2 no longer supports Stippled Lines. This example uses texture mapping to created stippled lines. Two parameters, StipplePattern and StippleRepeat, control the pattern of the stippled lines.

StipplePattern is a 16-bit binary pattern, 1 = pixel on, 0 = pixel off.

StippleRepeat is the stippling repeat factor of a Line, which specifies how many times each bit in the pattern is to be repeated.

It can  be tricky to set the proper pattern and repeat, so experiment.
