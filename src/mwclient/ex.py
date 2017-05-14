import client, http

def read_config(config_files, **predata):
	cfg = {}
	for config_file in config_files:
		cfg.update(_read_config_file(
			config_file, predata))
	return cfg
	
def _read_config_file(_config_file, predata):
	_file = open(_config_file)
	exec _file in globals(), predata
	_file.close()
	
	for _k, _v in predata.iteritems():
		if not _k.startswith('_'):
			yield _k, _v
	for _k, _v in locals().iteritems():
		if not _k.startswith('_'):
			yield _k, _v

class SiteList(object):
	def __init__(self):
		self.sites = {}
	def __getitem__(self, key):
		if key not in self.sites:
			self.sites[key] = {}
		return self.sites[key]
	def __iter__(self):
		return self.sites.itervalues()

class ConfiguredSite(client.Site):
	def __init__(self, *config_files, **kwargs):
		self.config = read_config(config_files, sites = SiteList())
		
		if 'name' in kwargs:
			self.config.update(self.config['sites'][kwargs['name']])
		
		do_login = 'username' in self.config and 'password' in self.config
		
		client.Site.__init__(self, host = self.config['host'],
			path = self.config['path'], ext = self.config.get('ext', '.php'), 
			do_init = not do_login,
			retry_timeout  = self.config.get('retry_timeout', 30),
			max_retries = self.config.get('max_retries', -1))
			
			
		if do_login:
			self.login(self.config['username'],
				self.config['password'])
	
class ConfiguredPool(list):
	def __init__(self, *config_files):
		self.config = read_config(config_files, sites = SiteList())
		self.pool = http.HTTPPool()
		
		config = dict([(k, v) for k, v in self.config.iteritems()
			if k != 'sites'])
		
		for site in self.config['sites']:
			cfg = config.copy()
			cfg.update(site)
			site.update(cfg)
			
			do_login = 'username' in site and 'password' in site
					
			self.append(client.Site(host = site['host'], 
				path = site['path'], ext = site.get('ext', '.php'),
				pool = self.pool, do_init = not do_login,
				retry_timeout = site.get('retry_timeout', 30),
				max_retries = site.get('max_retries', -1)))
			if do_login:
				self[-1].login(site['username'], site['password'])
			self[-1].config = site
			

