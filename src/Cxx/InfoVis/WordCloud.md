### Description
A word cloud is a visualization of word frequency in a given text as a weighted list. It is a variation of a [tag cloud](https://en.wikipedia.org/wiki/Tag_cloud).

This example creates a word cloud using vtkFreeTypeTools to render words into images. vtkImageBlend adds these images onto a final image. A vtkImageIterator compares pixels in the text image with those in the final image. If a non-background pixel exists in the final image, that word is not kept.

The example illustrates a number of std:: concepts including [random numbers](http://www.cplusplus.com/reference/random/), [regular expressions](http://www.cplusplus.com/reference/regex/) and [multi_set](http://www.cplusplus.com/reference/set/multiset/).

Also, the [kwsys](https://gitlab.kitware.com/utils/kwsys) CommandLineArguments  used to process command line arguments.

Many parameters are exposed on the command line:
```bash
Usage: WordCloud textFileName 
  --backgroundColorName opt  Name of the color for the background(MignightBlue)
  --bwMask  Mask image has a single channel(false).
  --colorDistribution opt o  Distribution of random colors(.6 1.0). If
                             wordColorName is not empty, random colors are
                             generated with this distribution
  --colorScheme opt  Color scheme(constant)
  --dpi opt  Dots per inch(200)
  --fontFile opt  Font file name(""). If fontFileName is empty, the
                             built-in Arial font is used.
  --fontMultiplier opt  Font multiplier(6). This final FontSize is this
                             value * the word frequency.
  --gap opt  Space gap of words (2). The gap is the number of
                             spaces added to the beginning and end of each word
  --help  Show help(false)
  --maskColorName opt  Name of the color for the mask (black). This is
                             the name of the color that defines the foreground
                             of the mask. Usually black or white
  --maskFile opt  Mask file name(""). If the mask file is specified,
                             if will be used as the mask, otherwise a black
                             square is used as the mask.
  --maxFontSize opt  Maximum font size(48)
  --minFontSize opt  Minimum font size(8)
  --offsetDistribution opt   Range of random offsets(-size[0]/100.0
                             -size{1]/100.0)(-20 20).
  --orientationDistribution  Ranges of random orientations(-20 20)
  --size opt opt ...  Size of image(640 480)
  --wordColorName opt  Name of the color for the words(). If the name is
                             empty, the colorDistribution will generate random
                             colors.
```
The example image was produced with these arguments:
```bash
WordCloud ${DATA}/Gettysburg.txt --dpi 150 --fontFile ${DATA}/Canterbury.ttf
```
and these parameters:
```bash
Cloud Parameters
  BackgroundColorName: MidnightBlue
  BWMask: false
  ColorDistribution: 0.6 1
  ColorSchemeName: 
  DPI: 150
  FontFile: /Canterbury.ttf
  FontMultiplier: 6
  Gap: 2
  MaskColorName: black
  MaskFile: 
  MinFontSize: 12
  MaxFontSize: 48
  OffsetDistribution: -6 4
  OrientationDistribution: -20 20
  Orientations: 
  ReplacementPairs: 
  Sizes: 640 480
  StopWords: 
  Title: 
  WordColorName: 
```
and produced this output:
```bash
Kept 94 words
Stopped 178 words
Skipped 5 words
```

!!! info
    We may add a word cloud class to VTK is there is enough interest.
