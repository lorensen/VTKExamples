!!! danger This page is not complete

VTKExamples Administrators have write access to the [git repository]([https://github.com/lorensen/VTKExamples). If you are a VTKExamples User [go here](/Instructions/ForUsers) or a VTKExamples Developer [go here](/Instructions/ForDevelopers).

# Organization of the VTKExamples Repository

The VTKExamples are stored in a [git repository](https://github.com/lorensen/VTKExamples.git) hosted at [github.com](http://www.github.com/). The repository contains several types of files.

All example source code, descriptions, test data and test baselines are stored in the src/ tree.

## VTKExamples
The major elements of the tree are:

``` bash
|-- VTKExamples
  |-- CMakeLists.txt
  |-- _layouts
  |-- custom_theme
  |-- mkdocs.yml
  |-- src
    |-- SyncSiteWithRepo.sh
    |-- Admin
    |   |-- ScrapeRepo
    |   |-- VTKCMakeLists
    |   |-- VTKQtCMakeLists
    |   |-- sitemap.xml
    |   |-- sitemapGenerator
    |-- Artifacts
    |-- Instructions
    |-- LANGUAGE.md
    |-- LANGUAGE
    |   |-- TOPIC
    |-- Tarballs
    |-- Testing
    |   |-- Baseline
    |   |   |-- LANGUAGE
    |   |   |   |-- TOPIC
    |   |-- Data
    |-- stylesheets
        |-- extra.css
  |-- site
```

# Look and Feel
## [MkDocs](http://www.mkdocs.org/)
### Configuring MkDocs
#### Markdown Extensions
##### [admonition](http://squidfunk.github.io/mkdocs-material/extensions/admonition/)
##### [codehilite](http://squidfunk.github.io/mkdocs-material/extensions/codehilite/)
##### toc
## [MkDocs Materials theme](http://squidfunk.github.io/mkdocs-material/)

### Configuring Materiala

## [Google Analytics](https://analytics.google.com/)
Google Analytics tracks the site usage, providing lots of useful statistics. To have Google Analytics track web usage you need to register the url with the Google Analytics ayatwm. After registarion, an html snippet is provided to incde on every web page to be tracked.

### Configuring Google Analytics

## [Google Custom Search Engine](https://analytics.google.com/)
### Configuring GCSE
### Inplementating GCSE

## [Lazy Image Loading](https://davidwalsh.name/lazyload-image-fade)

The first implementation had problems loading the [Cxx summary](/Cxx). The number of embedded images exceeded the throttle limits of github. A lazy image load solution solved the problem. Now, images are only loaded if they appear on the browser window.

# Administrator Tasks
## [ScrapeWiki](/Admin/ScrapeRepo)
![alt text](https://github.com/lorensen/VTKExamples/blob/master/src/Artifacts/ScrapeRepo.png "ScrapeRepo")
