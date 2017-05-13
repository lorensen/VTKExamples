This files describes mwclient-0.6.4. The latest version is available in the 
subversion repository <https://mwclient.svn.sourceforge.net/svnroot/mwclient>
and also browsable <http://mwclient.svn.sourceforge.net/viewvc/mwclient/>.

Mwclient is a client to the MediaWiki API <http://mediawiki.org/wiki/API>
and allows access to almost all implemented API functions. Mwclient requires
Python 2.4. This version supports MediaWiki 1.11 and above. However, for 
functions not available in the current MediaWiki, a MediaWikiVersionError
is raised.

This framework is written by Bryan Tong Minh and serves most of his bots.
The framework and this documentation are primarily written for personal
use and may or may not work for you. In case it doesn't, Bryan can be
contacted on btongminh@users.sourceforge.net.

This framework heavily depends on simplejson, (c) copyright Bob Ippolito.
 

== Implementation notes ==
Most properties and generators accept the same parameters as the API, without
their two letter prefix. Exceptions to this rule:
* Image.imageinfo is the imageinfo of the latest image. Earlier versions can be
  fetched using imagehistory()
* Site.all* : parameter [ap]from renamed to start
* categorymembers is implemented as Category.members
* deletedrevs is deletedrevisions
* usercontribs is usercontributions
* First parameters of search and usercontributions are search and user 
  respectively

Properties and generators are implemented as Python generators. Their limit 
parameter is only an indication of the number of items in one chunk. It is not
the total limit. Doing list(generator(limit = limit)) will return ALL items of 
generator, and not be limited by the limit value.
Default chunk size is generally the maximum chunk size.

== HTTPS ==
To use https, specify the host as a tuple in the form of ('https', hostname).

== Example ==
## For more information, see REFERENCE.txt
# Init site object
import mwclient
site = mwclient.Site('commons.wikimedia.org')
site.login(username, password) # Optional

# Edit page
page = site.Pages['Commons:Sandbox']
text = page.edit()
print 'Text in sandbox:', text.encode('utf-8')
page.save(text + u'\nExtra data', summary = 'Test edit')

# Printing imageusage
image = site.Images['Example.jpg']
print 'Image', image.name.encode('utf-8'), 'usage:'
for page in image.imageusage():
	print 'Used:', page.name.encode('utf-8'), '; namespace', page.namespace
	print 'Image info:', image.imageinfo

# Uploading a file
site.upload(open('file.jpg'), 'destination.jpg', 'Image description')

# Listing all categories (don't do this in reality)
for category in site.allcategories():
	print category

== License ==
 Copyright (c) 2006-2009 Bryan Tong Minh
 
 Permission is hereby granted, free of charge, to any person
 obtaining a copy of this software and associated documentation
 files (the "Software"), to deal in the Software without
 restriction, including without limitation the rights to use,
 copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following
 conditions:
 
 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.