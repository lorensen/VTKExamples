import client, page
import compatibility

class List(object):
	def __init__(self, site, list_name, prefix, limit = None, return_values = None, max_items = None, *args, **kwargs):
		# NOTE: Fix limit
		self.site = site
		self.list_name = list_name
		self.generator = 'list'
		self.prefix = prefix
		
		kwargs.update(args)
		self.args = kwargs
		
		if limit is None: limit = site.api_limit
		self.args[self.prefix + 'limit'] = str(limit)
		
		self.count = 0
		self.max_items = max_items
		
		self._iter = iter(xrange(0))
		
		self.last = False
		self.result_member = list_name
		self.return_values = return_values
		
	def __iter__(self):
		return self
		
	def next(self, full = False):
		if self.max_items is not None:
			if self.count >= self.max_items:
				raise StopIteration
		try:
			item = self._iter.next()
			self.count += 1
			if 'timestamp' in item:
				item['timestamp'] = client.parse_timestamp(item['timestamp'])
			if full: return item
				
			if type(self.return_values) is tuple:
				return tuple((item[i] for i in self.return_values))
			elif self.return_values is None:
				return item
			else:
				return item[self.return_values]
			
		except StopIteration:
			if self.last: raise StopIteration
			self.load_chunk()
			return List.next(self, full = full)
			
	def load_chunk(self):
		data = self.site.api('query', (self.generator, self.list_name), *[(str(k), v) for k, v in self.args.iteritems()])
		if not data:
			# Non existent page
			raise StopIteration
		self.set_iter(data)
		
		if self.list_name in data.get('query-continue', ()):
			self.args.update(data['query-continue'][self.list_name])
		else:
			self.last = True
	def set_iter(self, data):
		if self.result_member not in data['query']:
			self._iter = iter(xrange(0))
		elif type(data['query'][self.result_member]) is list:
			self._iter = iter(data['query'][self.result_member])
		else:
			self._iter = data['query'][self.result_member].itervalues()
				
		
	def __repr__(self):
		return "<List object '%s' for %s>" % (self.list_name, self.site)

	@staticmethod 
	def generate_kwargs(_prefix, *args, **kwargs):
		kwargs.update(args)
		for key, value in kwargs.iteritems():
			if value != None:
				yield _prefix + key, value
	@staticmethod
	def get_prefix(prefix, generator = False):
		if generator:
			return 'g' + prefix
		else:
			return prefix
	@staticmethod
	def get_list(generator = False):
		if generator:
			return GeneratorList
		else:
			return List


class GeneratorList(List):
	def __init__(self, site, list_name, prefix, *args, **kwargs):
		List.__init__(self, site, list_name, prefix, *args, **kwargs)
		
		self.args['g' + self.prefix + 'limit'] = self.args[self.prefix + 'limit']
		del self.args[self.prefix + 'limit']
		self.generator = 'generator'
		
		self.args['prop'] = 'info|imageinfo'
		self.args['inprop'] = 'protection'
		
		self.result_member = 'pages'
		
		self.page_class = page.Page
		
	def next(self):
		info = List.next(self, full = True)
		if info['ns'] == 14:
			return Category(self.site, u'', info)
		if info['ns'] == 6:
			return page.Image(self.site, u'', info)
		return page.Page(self.site, u'', info)
		
	def load_chunk(self):
		# Put this here so that the constructor does not fail 
		# on uninitialized sites
		self.args['iiprop'] = compatibility.iiprop(self.site.version)
		return List.load_chunk(self)
		
	
class Category(page.Page, GeneratorList):
	def __init__(self, site, name, info = None, namespace = None):
		page.Page.__init__(self, site, name, info)
		kwargs = {}
		kwargs.update((compatibility.cmtitle(self, self.site.require(
			1, 12, raise_error = False), prefix = 'gcm'), ))
		if namespace: kwargs['gcmnamespace'] = namespace
		GeneratorList.__init__(self, site, 'categorymembers', 'cm', **kwargs)
	def __repr__(self):
		return "<Category object '%s' for %s>" % (self.name.encode('utf-8'), self.site)
	def members(self, prop = 'ids|title', namespace = None, sort = 'sortkey', 
			dir = 'asc', start = None, end = None, generator = True):
		prefix = self.get_prefix('cm', generator)
		kwargs = dict(self.generate_kwargs(prefix, prop = prop, namespace = namespace,
			sort = sort, dir = dir, start = start, end = end, *(compatibility.cmtitle(
			self, self.site.require(1, 12, raise_error = False)), )))
		return self.get_list(generator)(self.site, 'categorymembers', 'cm', **kwargs)
		
class PageList(GeneratorList):
	def __init__(self, site, prefix = None, start = None, namespace = 0, redirects = 'all'):
		self.namespace = namespace
		
		kwargs = {}
		if prefix: kwargs['apprefix'] = prefix
		if start: kwargs['apfrom'] = start
			
		GeneratorList.__init__(self, site, 'allpages', 'ap',
			apnamespace = str(namespace), apfilterredir = redirects, **kwargs)

	def __getitem__(self, name):
		return self.get(name, None)
	def get(self, name, info = ()):
		if self.namespace == 14:
			return Category(self.site, self.site.namespaces[14] + ':' + name, info)
		elif self.namespace == 6:
			return page.Image(self.site, self.site.namespaces[6] + ':' + name, info)
		elif self.namespace != 0:
			return page.Page(self.site, self.site.namespaces[self.namespace] + ':' + name, info)
		else:
			# Guessing page class
			namespace = self.guess_namespace(name)
			if namespace == 14:
				return Category(self.site, name, info)
			elif namespace == 6:
				return page.Image(self.site, name, info)
			else:
				return page.Page(self.site, name, info)
		
	def guess_namespace(self, name):
		normal_name = page.Page.normalize_title(name)
		for ns in self.site.namespaces:
			if ns == 0: continue
			if name.startswith(u'%s:' % self.site.namespaces[ns].replace(' ', '_')):
				return ns
			elif ns in self.site.default_namespaces:
				if name.startswith(u'%s:'  % self.site.default_namespaces[ns].replace(' ', '_')):
					return ns
		return 0

		
class PageProperty(List):
	def __init__(self, page, prop, prefix, *args, **kwargs):
		List.__init__(self, page.site, prop, prefix, titles = page.name, *args, **kwargs)
		self.page = page
		self.generator = 'prop'
	def set_iter(self, data):
		for page in data['query']['pages'].itervalues():
			if page['title'] == self.page.name:
				self._iter = iter(page.get(self.list_name, ()))
				return
		raise StopIteration

		
class PagePropertyGenerator(GeneratorList):
	def __init__(self, page, prop, prefix, *args, **kwargs):
		GeneratorList.__init__(self, page.site, prop, prefix, titles = page.name, *args, **kwargs)
		self.page = page

class RevisionsIterator(PageProperty):
	def load_chunk(self):
		if 'rvstartid' in self.args and 'rvstart' in self.args:
			del self.args['rvstart']
		return PageProperty.load_chunk(self)
	