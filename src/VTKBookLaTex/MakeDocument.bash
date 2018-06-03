#!/bin/bash
lualatex VTKTextBook
makeglossaries VTKTextBook
biber VTKTextBook
makeindex VTKTextBook
lualatex VTKTextBook
lualatex VTKTextBook
