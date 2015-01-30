# Resource view

C++/Qt

## Editor features

* Search (with smart filters, e.g. "grass type:texture tag:ground")
* Sorting
* Filtering (by tag and by type)
* Rename
* Import new (+ drag and drop)
* Create group
* Create resource
* Favourites (???)
* Shortcuts (!)

## Engine classes

ResourceManager, ResourceIO, ResourceNode

## Importers

The importer in editor has attached dialog with import settings. 
It also should handle progress bar ('emit progress()').

* Model importer - [Assimp](http://assimp.sourceforge.net/)
* Texture importer - [FreeImgae](http://freeimage.sourceforge.net/)
* Video and sound importer - [ffmpeg](https://www.ffmpeg.org/) ?
* Font importer - [Freetype](http://www.freetype.org/) ?
* Text importer
* Binary data importer