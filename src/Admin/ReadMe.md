# Admin

Files in this folder generate web pages, provide extra data derived from examples and manipulate files/examples.

| Name | Description |
| ---- | ----------- |
| `AddTestPrefix.py` | For each file in `VTKExamples/src/Testing/Baseline` look in the corresponding folder in `VTKExamples/src/Testing/Baseline` for an image file that does not have the Test prefix. Use with care and understand the options! |
| `FindMissingExamples.py` | Produce a list of examples that are not mentioned in the src/*.md files. |
| `FindMissingTestImages.py` | Display examples that are missing test image files. The first part of the script has a function that returns a dictionary that lists examples that do not produce image files. |
| `getDeletedFile.sh` | Given a file, find that file in a git repository, even if it has been deleted. |
| `ScrapeRepo` | Create site files from the src repo. |
| `sitemap_gen.py` | This script crawls a web site from a given starting URL and generates a Sitemap file in the format that is accepted by Google. |
| `sitemap.xml` | The generated sitemap file from `sitemap_gen.py`. |
| `sitemapGenerator` | A python script that calls `sitemap_gen.py`. |
| `TinyUrlCache` | A cache of generated tiny URLs. |
| `ValidateMarkdown.py` | Parses a markdown file that is used to generate the web page. This is used to validate files like `Cxx.md` |
| `VTKClassesUsedInExamples.py` | Produces markdown tables of the VTK classes used and not used in the examples. |
| `VTKCMakeLists` | Added to the end of the web page for each example. |
| `VTKQtCMakeLists` | Added to the end of the web page for each Qt example. |
| `WhatModulesVTK` | Generate a `FindPackage(VTK COMPONENTS)` that lists all modules  referenced by a set of files. |
