import urllib2
import urlparse
import httplib
import socket
import time

import upload
import errors

from client import __ver__

class Request(urllib2.Request):
	def __init__(self, url, data=None, headers={},
		origin_req_host=None, unverifiable=False, head = False):
		urllib2.Request.__init__(self, url, data, headers, origin_req_host, unverifiable)
		
		self.add_header('User-Agent', 'MwClient-' + __ver__)
		self.head = head
	def get_method(self):
		if self.head: return 'HEAD'
		return urllib2.Request.get_method(self)

		
class CookieJar(dict):
	def __init__(self):
		dict.__init__(self, ())
	def extract_cookies(self, response):
		for cookie in response.msg.getallmatchingheaders('Set-Cookie'):
			self.parse_cookie(cookie.strip())
		if response.getheader('set-cookie2', None):
			# ...
			raise RuntimeError, 'Set-Cookie2', value
	def parse_cookie(self, cookie):
		if not cookie: return
		value, attrs = cookie.split(': ', 1)[1].split(';', 1)
		i = value.strip().split('=')
		if len(i) == 1 and i[0] in self: 
			del self[i[0]]
		else:
			self[i[0]] = i[1]
		
	def get_cookie_header(self):
		return '; '.join(('%s=%s' % i for i in self.iteritems()))
	def __iter__(self):
		for k, v in self.iteritems():
			yield Cookie(k, v)
		
class Cookie(object):
	def __init__(self, name, value):
		self.name = name
		self.value = value
		
class HTTPPersistentConnection(object):
	http_class = httplib.HTTPConnection
	scheme_name = 'http'
	
	def __init__(self, host, pool = None):
		self.cookies = {}
		self.pool = pool
		if pool: self.cookies = pool.cookies
		self._conn = self.http_class(host)
		self._conn.connect()
		self.last_request = time.time()
		
	def request(self, method, host, path, headers, data,
			raise_on_not_ok = True, auto_redirect = True):		
		
		# Strip scheme
		if type(host) is tuple:
			host = host[1]
			
		# Dirty hack...
		if (time.time() - self.last_request) > 60:
			self._conn.close()
			self._conn.connect()			
		
		_headers = headers
		headers = {}
		
		headers['Connection'] = 'Keep-Alive'
		headers['User-Agent'] = 'MwClient/' + __ver__
		headers['Host'] = host
		if host in self.cookies: 
			headers['Cookie'] = self.cookies[host].get_cookie_header()
		if issubclass(data.__class__, upload.Upload):
			headers['Content-Type'] = data.content_type
			headers['Content-Length'] = data.length;
		elif data:
			headers['Content-Length'] = len(data)
			
		if _headers: headers.update(_headers)
		
		try:
			self._conn.request(method, path, headers = headers)
			if issubclass(data.__class__, upload.Upload):
				for str in data:
					self._conn.send(str)
			elif data:
				self._conn.send(data)
			
			self.last_request = time.time()
			try:
				res = self._conn.getresponse()
			except httplib.BadStatusLine:
				self._conn.close()
				self._conn.connect()
				self._conn.request(method, path, data, headers)
				res = self._conn.getresponse()
		except socket.error, e:
			self._conn.close()
			raise errors.HTTPError, e
		#except Exception, e:
		#	raise errors.HTTPError, e
				
		if not host in self.cookies: self.cookies[host] = CookieJar()
		self.cookies[host].extract_cookies(res)
		
		if res.status >= 300 and res.status <= 399 and auto_redirect:
			res.read()
			
			location = urlparse.urlparse(res.getheader('Location'))
			if res.status in (302, 303):
				if 'Content-Type' in headers:
					del headers['Content-Type']
				if 'Content-Length' in headers:
					del headers['Content-Length']
				method = 'GET'
				data = ''
			old_path = path
			path = location[2]
			if location[4]: path = path + '?' + location[4]
			
			if location[0].lower() != self.scheme_name:
				raise errors.HTTPRedirectError, ('Only HTTP connections are supported',
					res.getheader('Location'))
			
			if self.pool is None:
				if location[1] != host: 
					raise errors.HTTPRedirectError, ('Redirecting to different hosts not supported', 
						res.getheader('Location'))

				return self.request(method, host, path, headers, data)
			else:
				if host == location[1] and path == old_path:
					conn = self.__class__(location[1], self.pool)
					self.pool.append(([location[1]], conn))
				return self.pool.request(method, location[1], path, 
					headers, data, raise_on_not_ok, auto_redirect)
			
		if res.status != 200 and raise_on_not_ok:
			try:
				raise errors.HTTPStatusError, (res.status, res)
			finally:
				res.close()
			
		return res
		
	def get(self, host, path, headers = None):
		return self.request('GET', host, path, headers, None)
	def post(self, host, path, headers = None, data = None):
		return self.request('POST', host, path, headers, data)
	def head(self, host, path, headers = None, auto_redirect = False):
		res = self.request('HEAD', host, path, headers, 
			data = None, raise_on_not_ok = False,
			auto_redirect = auto_redirect)
		res.read()
		return res.status, res.getheaders()
		
	def close(self):
		self._conn.close()
	def fileno(self):
		return self._conn.sock.fileno()

class HTTPConnection(HTTPPersistentConnection):
	def request(self, method, host, path, headers, data,
			raise_on_not_ok = True, auto_redirect = True):
		if not headers: headers = {}
		headers['Connection'] = 'Close'
		res = HTTPPersistentConnection.request(self, method, host, path, headers, data, 
			raise_on_not_ok, auto_redirect)
		return res

class HTTPSPersistentConnection(HTTPPersistentConnection):
	http_class = httplib.HTTPSConnection
	scheme_name = 'https'

	
class HTTPPool(list):
	def __init__(self):
		list.__init__(self)
		self.cookies = {}
	def find_connection(self, host, scheme = 'http'):
		if type(host) is tuple:
			scheme, host = host
			
		for hosts, conn in self:
			if (scheme, host) in hosts: return conn
		
		redirected_host = None
		for hosts, conn in self:
			status, headers = conn.head(host, '/')
			if status == 200:
				hosts.append((scheme, host))
				return conn
			if status >= 300 and status <= 399:
				# BROKEN!
				headers = dict(headers)
				location = urlparse.urlparse(headers.get('location', ''))
				if (location[0], location[1]) == (scheme, host):
					hosts.append((scheme, host))
					return conn
		if scheme == 'http':
			cls = HTTPPersistentConnection
		elif scheme == 'https':
			cls = HTTPSPersistentConnection
		else:
			raise RuntimeError('Unsupported scheme', scheme)
		conn = cls(host, self)
		self.append(([(scheme, host)], conn))
		return conn
	def get(self, host, path, headers = None):
		return self.find_connection(host).get(host, 
			path, headers)
	def post(self, host, path, headers = None, data = None):
		return self.find_connection(host).post(host, 
			path, headers, data)
	def head(self, host, path, headers = None, auto_redirect = False):
		return self.find_connection(host).head(host, 
			path, headers, auto_redirect)
	def request(self, method, host, path, headers, data,
			raise_on_not_ok, auto_redirect):
		return self.find_connection(host).request(method, host, path,
			headers, data, raise_on_not_ok, auto_redirect)
	def close(self):
		for hosts, conn in self:
			conn.close()
			
