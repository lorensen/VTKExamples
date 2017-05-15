import upload, errors

def title(prefix, new_format):
	if new_format: 
		return prefix + 'title'
	else:
		return 'titles'
		
def userinfo(data, new_format = None):
	if new_format is None:
		# Unknown version; trying to guess
		if 'userinfo' in data: 
			return data['userinfo']
		elif 'userinfo' in data.get('query', ()):
			return data['query']['userinfo']
		else: 
			return {}
	elif new_format:
		return data['query']['userinfo']
	else:
		return data['userinfo']

def iiprop(version):
	if version[:2] >= (1, 13):
		return 'timestamp|user|comment|url|size|sha1|metadata|archivename'
	if version[:2] >= (1, 12):
		return 'timestamp|user|comment|url|size|sha1|metadata'
	else:
		return 'timestamp|user|comment|url|size|sha1'
		
def cmtitle(page, new_format, prefix = ''):
	if new_format:
		return prefix + 'title', page.name
	else:
		return prefix + 'category', page.strip_namespace(page.name)
		
def protectright(version):
	if version[:2] >= (1, 13):
		return 'editprotected'
	else:
		return 'protect'

from cStringIO import StringIO
def old_upload(self, file, filename, description, license = '', ignore = False, file_size = None): 
	image = self.Images[filename]
	if not image.can('upload'):
		raise errors.InsufficientPermission(filename)
	if image.exists and not ignore:
		raise errors.FileExists(filename)
		
	if type(file) is str:
		file_size = len(file)
		file = StringIO(file)
	if file_size is None:
		file.seek(0, 2)
		file_size = file.tell()
		file.seek(0, 0)
			
	predata = {}
	# Do this thing later so that an incomplete upload won't work
	# predata['wpDestFile'] = filename
	predata['wpUploadDescription'] = description
	predata['wpLicense'] = license
	if ignore: predata['wpIgnoreWarning'] = 'true'
	predata['wpUpload'] = 'Upload file'
	predata['wpSourceType'] = 'file'
	predata['wpDestFile'] = filename
	predata['wpEditToken'] = image.get_token('edit')
		
	postdata = upload.UploadFile('wpUploadFile', filename, file_size, file, predata)
		
	wait_token = self.wait_token()
	while True:
		try:
			self.connection.post(self.host,
					self.path + 'index.php?title=Special:Upload&maxlag=' 
					+ self.max_lag, data = postdata).read()
		except errors.HTTPStatusError, e:
			if e[0] == 503 and e[1].getheader('X-Database-Lag'):
				self.wait(wait_token, int(e[1].getheader('Retry-After')))
			elif e[0] < 500 or e[0] > 599:
				raise
			else:
				self.wait(wait_token)
		except errors.HTTPError:
			self.wait(wait_token)
		else:
			return
		file.seek(0, 0)

			