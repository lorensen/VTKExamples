@echo off
lualatex VTKTextBook
biber VTKTextBook
makeglossaries VTKTextBook
lualatex VTKTextBook
makeindex VTKTextBook
lualatex VTKTextBook
