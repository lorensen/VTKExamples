# Admin

Files in this folder generate web pages, provide extra data derived from examples and manipulate files/examples.

| Name | Description |
| ---- | ----------- |
| `FindExamplesMissingTestImages.py` | Run this to display examples that are missing tests. The first part of the script has a dictionary that lists examples that do not produce image files. |
| `FindMissingExamples.py` | Produce a list of examples that are not mentioned in the src/*.md files. |
| `getDeletedFile.sh` | Given a file, find that file in a git repository, even if it has been deleted. |
| `RenameFiles.py` | For each file in `VTKExamples/src/Testing/Baseline` look in the corresponding folder in `VTKExamples/src/Testing/Baseline` for an image file that does not have the Test prefix. Use with care and understand the options! |
| `ScrapeRepo` | Create site files from the src repo. |
| `sitemap_gen.py` | This script crawls a web site from a given starting URL and generates a Sitemap file in the format that is accepted by Google. |
| `sitemap.xml` | The generated sitemap file from `sitemap_gen.py`. |
| `sitemapGenerator` | A python script that calls `sitemap_gen.py`. |
| `TinyUrlCache` | A cahce of generated tiny URLs. |
| `ValidateMarkdown.py` | Parses a markdown file that is used to generate the web page. This is used to validate files like `Cxx.md` |
| `VTKClassesUsedInExamples.py` | Produces markdown tables of the VTK classes used and not used in the examples. |
| `VTKCMakeLists` | added to the end of the web page for each example. |
| `VTKQtCMakeLists` | added to the end of the web page for each Qt example. |
