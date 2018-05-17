@echo off
lualatex VTKTextBook
makeglossaries VTKTextBook
biber VTKTextBook
lualatex VTKTextBook
lualatex VTKTextBook
