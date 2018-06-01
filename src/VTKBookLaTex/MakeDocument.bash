#!/bin/bash
lualatex VTKTextBook
makeglossaries VTKTextBook
biber VTKTextBook
lualatex VTKTextBook
makeindex VTKTextBook
lualatex VTKTextBook
