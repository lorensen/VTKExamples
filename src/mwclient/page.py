import client, errors, listing
import compatibility
from page_nowriteapi import OldPage

import urllib, urlparse, time
	
class Page(object):
	def __init__(self, site, name, info = None, extra_properties = {}):
		if type(name) is type(self):
			return self.__dict__.update(name.__dict__)
		self.site = site
		self.name = name
		
		if not info:
			if extra_properties:
				prop = 'info|' + '|'.join(extra_properties.iterkeys())
				extra_props = []
				[extra_props.extend(extra_prop) for extra_prop in extra_properties.itervalues()]					
			else:
				prop = 'info'
				extra_props = ()
			
			info = self.site.api('query', prop = prop, titles = name, 
				inprop = 'protection', *extra_props)
			info = info['query']['pages'].itervalues().next()
		self._info = info
				
		self.namespace = info.get('ns', 0)
		self.name = info.get('title', u'')
		if self.namespace:
			self.page_title = self.strip_namespace(self.name)
		else:
			self.page_title = self.name

		self.touched = client.parse_timestamp(info.get('touched', '0000-00-00T00:00:00Z'))
		self.revision = info.get('lastrevid', 0)
		self.exists = 'missing' not in info
		self.length = info.get('length')
		self.protection = dict([(i['type'], (i['level'], i['expiry'])) for i in info.get('protection', ()) if i])
		self.redirect = 'redirect' in info
		
		self.last_rev_time = None
		self.edit_time = None
			
	def __repr__(self):
		return "<Page object '%s' for %s>" % (self.name.encode('utf-8'), self.site)
	def __unicode__(self):
		return self.name
		
	@staticmethod
	def strip_namespace(title):
		if title[0] == ':':
			title = title[1:]
		return title[title.find(':') + 1:]
	@staticmethod
	def normalize_title(title):
		# TODO: Make site dependent
		title = title.strip()		
		if title[0] == ':':
			title = title[1:]
		title = title[0].upper() + title[1:]
		title = title.replace(' ', '_')
		return title

		
	def can(self, action):
		level = self.protection.get(action, (action, ))[0]
		if level == 'sysop': level = compatibility.protectright(self.site.version)
		
		return level in self.site.rights
		
	def get_token(self, type, force = False):
		self.site.require(1, 11)
		
		if type not in self.site.tokens:
			self.site.tokens[type] = '0'
		if self.site.tokens.get(type, '0') == '0' or force:
			info = self.site.api('query', titles = self.name,
				prop = 'info', intoken = type)
			for i in info['query']['pages'].itervalues():
				if i['title'] == self.name:
					self.site.tokens[type] = i['%stoken' % type]
		return self.site.tokens[type]
					
	def get_expanded(self):
		self.site.require(1, 12)
		
		revs = self.revisions(prop = 'content', limit = 1, expandtemplates = True)
		try:
			return revs.next()['*']
		except StopIteration:
			return u''
			
	def edit(self, section = None, readonly = False):
		if not self.can('read'):
			raise errors.InsufficientPermission(self)
		if not self.exists:
			return u''
			
		revs = self.revisions(prop = 'content|timestamp', limit = 1)
		try:
			rev = revs.next()
			self.text = rev['*']
			self.last_rev_time = rev['timestamp']
		except StopIteration:
			self.text = u''
			self.edit_time = None
		self.edit_time = time.gmtime()
		return self.text
	
	def save(self, text = u'', summary = u'', minor = False, bot = True, **kwargs):
		if not self.site.logged_in and self.site.force_login:
			# Should we really check for this?
			raise errors.LoginError(self.site)
		if self.site.blocked:
			raise errors.UserBlocked(self.site.blocked)
		if not self.can('edit'):
			raise errors.ProtectedPageError(self)
		
		if not text: text = self.text
		
		if not self.site.writeapi:
			return OldPage.save(self, text = text, summary = summary, minor = False)
		
		data = {}
		if minor: data['minor'] = '1'
		if not minor: data['notminor'] = '1'
		if self.last_rev_time: data['basetimestamp'] = time.strftime('%Y%m%d%H%M%S', self.last_rev_time)
		if self.edit_time: data['starttimestamp'] = time.strftime('%Y%m%d%H%M%S', self.edit_time)
		if bot: data['bot'] = '1'
		
		data.update(kwargs)
		
		def do_edit():
			result = self.site.api('edit', title = self.name, text = text, 
					summary = summary, token = self.get_token('edit'), 
					**data)		
			if result['edit'].get('result').lower() == 'failure':
				raise errors.EditError(self, result['edit'])
			return result	
		try:
			result = do_edit()
		except errors.APIError, e:
			if e.code == 'badtoken':
				# Retry, but only once to avoid an infinite loop
				self.get_token('edit', force = True)
				try:
					result = do_edit()
				except errors.APIError, e:
					self.handle_edit_error(e, summary)
			else:
				self.handle_edit_error(e, summary)

		if result['edit'] == 'Success':
			self.last_rev_time = client.parse_timestamp(result['newtimestamp'])
		return result['edit']
	
	def handle_edit_error(self, e,  summary):
		if e.code == 'editconflict':
			raise errors.EditError(self, summary, e.info)
		elif e.code in ('protectedtitle', 'cantcreate', 'cantcreate-anon', 'noimageredirect-anon', 
			    'noimageredirect', 'noedit-anon', 'noedit'):
			raise errors.ProtectedPageError(self, e.code, e.info)
		else:
			raise		

	def get_expanded(self):
		self.site.require(1, 12)
		
		revs = self.revisions(prop = 'content', limit = 1, expandtemplates = True)
		try:
			return revs.next()['*']
		except StopIteration:
			return u''
			
	def move(self, new_title, reason = '', move_talk = True, no_redirect = False):
		if not self.can('move'): raise errors.InsufficientPermission(self)
		
		if not self.site.writeapi:
			return OldPage.move(self, new_title = new_title, 
				reason = reason, move_talk = move_talk)
		
		data = {}
		if move_talk: data['movetalk'] = '1'
		if no_redirect: data['noredirect'] = '1'
		result = self.site.api('move', ('from', self.name), to = new_title, 
			token = self.get_token('move'), reason = reason, **data)
		return result['move']
		
			
	def delete(self, reason = '', watch = False, unwatch = False, oldimage = False):
		if not self.can('delete'): raise errors.InsufficientPermission(self)
		
		if not self.site.writeapi:
			return OldPage.delete(self, reason = reason)
		
		data = {}
		if watch: data['watch'] = '1'
		if unwatch: data['unwatch'] = '1'
		if oldimage: data['oldimage'] = oldimage
		result = self.site.api('delete', title = self.name, 
				token = self.get_token('delete'), 
				reason = reason, **data)
		return result['delete']
		
	def purge(self):
		self.site.raw_index('purge', title = self.name)
		
	# def watch: requires 1.14
		
	# Properties
	def backlinks(self, namespace = None, filterredir = 'all', redirect = False, limit = None, generator = True):
		self.site.require(1, 9)
		# Fix title for < 1.11 !!
		prefix = listing.List.get_prefix('bl', generator)
		kwargs = dict(listing.List.generate_kwargs(prefix, 
			namespace = namespace, filterredir = filterredir))
		if redirect: kwargs['%sredirect' % prefix] = '1'
		kwargs[compatibility.title(prefix, self.site.require(1, 11, raise_error = False))] = self.name
			
		return listing.List.get_list(generator)(self.site, 'backlinks', 'bl', limit = limit, return_values = 'title', **kwargs)
	def categories(self, generator = True):
		self.site.require(1, 11)
		if generator:
			return listing.PagePropertyGenerator(self, 'categories', 'cl')
		else:
			# TODO: return sortkey if wanted
			return listing.PageProperty(self, 'categories', 'cl', return_values = 'title')
	def embeddedin(self, namespace = None, filterredir = 'all', redirect = False, limit = None, generator = True):
		self.site.require(1, 9)
		# Fix title for < 1.11 !!
		prefix = listing.List.get_prefix('ei', generator)
		kwargs = dict(listing.List.generate_kwargs(prefix,
			namespace = namespace, filterredir = filterredir))
		if redirect: kwargs['%sredirect' % prefix] = '1'
		kwargs[compatibility.title(prefix, self.site.require(1, 11, raise_error = False))] = self.name
			
		return listing.List.get_list(generator)(self.site, 'embeddedin', 'ei', limit = limit, return_values = 'title', **kwargs)
	def extlinks(self):
		self.site.require(1, 11)
		return listing.PageProperty(self, 'extlinks', 'el', return_values = '*')
	def images(self, generator = True):
		self.site.require(1, 9)
		if generator:
			return listing.PagePropertyGenerator(self, 'images', '')
		else:
			return listing.PageProperty(self, 'images', '', return_values = 'title')
	def langlinks(self):
		self.site.require(1, 9)
		return listing.PageProperty(self, 'langlinks', 'll', return_values = ('lang', '*'))
	def links(self, namespace = None, generator = True):
		self.site.require(1, 9)
		kwargs = dict(listing.List.generate_kwargs('pl', namespace = namespace))
		if generator:
			return listing.PagePropertyGenerator(self, 'links', 'pl')
		else:
			return listing.PageProperty(self, 'links', 'pl', return_values = 'title')

	def revisions(self, startid = None, endid = None, start = None, end = None, 
			dir = 'older', user = None, excludeuser = None, limit = 50, 
			 prop = 'ids|timestamp|flags|comment|user', expandtemplates = False):
		self.site.require(1, 8)
		kwargs = dict(listing.List.generate_kwargs('rv', startid = startid, endid = endid,
			start = start, end = end, user = user, excludeuser = excludeuser))
		kwargs['rvdir'] = dir
		kwargs['rvprop'] = prop
		if expandtemplates: kwargs['rvexpandtemplates'] = '1'
		
		return listing.RevisionsIterator(self, 'revisions', 'rv', limit = limit, **kwargs)
	def templates(self, namespace = None, generator = True):
		self.site.require(1, 8)
		kwargs = dict(listing.List.generate_kwargs('tl', namespace = namespace))
		if generator:
			return listing.PagePropertyGenerator(self, 'templates', 'tl')
		else:
			return listing.PageProperty(self, 'templates', 'tl', return_values = 'title')

class Image(Page):
	def __init__(self, site, name, info = None):
		site.require(1, 11)
		Page.__init__(self, site, name, info,
			extra_properties = {'imageinfo': (('iiprop', 
				compatibility.iiprop(site.version)), )})
		self.imagerepository = self._info.get('imagerepository', '')
		self.imageinfo = self._info.get('imageinfo', ({}, ))[0]

	def imagehistory(self):
		return listing.PageProperty(self, 'imageinfo', 'ii', 
			iiprop = compatibility.iiprop(self.site.version))
	def imageusage(self, namespace = None, filterredir = 'all', redirect = False, 
			limit = None, generator = True):
		self.site.require(1, 11)
		# TODO: Fix for versions < 1.11
		prefix = listing.List.get_prefix('iu', generator)
		kwargs = dict(listing.List.generate_kwargs(prefix, title = self.name,
			namespace = namespace, filterredir = filterredir))
		if redirect: kwargs['%sredirect' % prefix] = '1'
		return listing.List.get_list(generator)(self.site, 'imageusage', 'iu', 
			limit = limit, return_values = 'title', **kwargs)
	def duplicatefiles(self, limit = None):
		self.require(1, 14)
		return listing.PageProperty(self, 'duplicatefiles', 'df',
			dflimit = limit)

	def download(self):
		url = self.imageinfo['url']
		# if not url.startswith('http://'):
			# url = 'http://' + self.site.host + url
		url = urlparse.urlparse(url)
		# TODO: query string
		return self.site.connection.get(url[1], url[2])
		
	def __repr__(self):
		return "<Image object '%s' for %s>" % (self.name.encode('utf-8'), self.site)
	
