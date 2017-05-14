import random
from cStringIO import StringIO

class Upload(object):
	"""
	Base class for upload objects. This class should always be subclassed 
	by upload classes and its constructor always be called.
	
	Upload classes are file like object/iterators that have additional 
	variables length and content_type.
	"""
	
	BLOCK_SIZE = 8192
	def __init__(self, length, content_type):
		self.length = length
		self.content_type = content_type
		
	def __iter__(self):
		return self
	def next(self):
		data = self.read(self.BLOCK_SIZE)
		if data == '':
			raise StopIteration
		return data
		
	@staticmethod
	def encode(s):
		if type(s) is str:
			return s
		elif type(s) is unicode:
			return s.encode('utf-8')
		else:
			return s

class UploadRawData(Upload):
	"""
	This upload class is simply a wrapper around StringIO 
	"""
	def __init__(self, data, content_type = 'application/x-www-form-urlencoded'):
		self.fstr = StringIO(data)
		Upload.__init__(self, len(data), content_type)
	def read(self, length = -1):
		return self.fstr.read(length)
		
		
class UploadDict(UploadRawData):
	"""
	This class creates an x-www-form-urlencoded representation of a dict 
	and then passes it through its parent UploadRawData 
	"""
	def __init__(self, data):
		postdata = '&'.join('%s=%s' % (self.encode(i), self.encode(data[i])) for i in data)
		UploadRawData.__init__(self, postdata)
		
class UploadFile(Upload):
	"""
	This class accepts a file with information and a postdata dictionary
	and creates a multipart/form-data representation from it.
	"""
	STAGE_FILEHEADER = 0
	STAGE_FILE = 1
	STAGE_POSTDATA = 2
	STAGE_FOOTER = 3
	STAGE_DONE = 4
	def __init__(self, filefield, filename, filelength, file, data):
		self.stage = self.STAGE_FILEHEADER;
		self.boundary = self.generate_boundary()
		self.postdata = self.generate_multipart_from_dict(data)
		self.footer = '\r\n--%s--\r\n' % self.boundary
		self.fileheader = ('--%s\r\n' % self.boundary +
				'Content-Disposition: form-data; name="%s"; filename="%s"\r\n' %
					(self.encode(filefield), self.encode(filename)) +
				'Content-Type: application/octet-stream\r\n\r\n')
		self.file = file
		self.length_left = filelength
		self.str_data = None
		
		Upload.__init__(self, len(self.fileheader) + filelength + len(self.postdata) + len(self.footer) + 2,
			'multipart/form-data; boundary=' + self.boundary)
		
	def read(self, length):
		if self.stage == self.STAGE_DONE:
			return ''
		elif self.stage != self.STAGE_FILE:	
			if self.str_data is None:
				if self.stage == self.STAGE_FILEHEADER:
					self.str_data = StringIO(self.fileheader)
				elif self.stage == self.STAGE_POSTDATA:
					self.str_data = StringIO(self.postdata)
				elif self.stage == self.STAGE_FOOTER:
					self.str_data = StringIO(self.footer)
			data = self.str_data.read(length)
		else:
			if self.length_left:
				if length > self.length_left:
					length = self.length_left
				data = self.file.read(length)
				self.length_left -= len(data)
			else:
				self.stage += 1
				return '\r\n'
		
		if data == '':
			self.stage += 1
			self.str_data = None
			return self.read(length)
		return data

		
	@staticmethod
	def generate_boundary():
		return '----%s----' % ''.join((random.choice(
			'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789') 
			for i in xrange(32)))
	
	def generate_multipart_from_dict(self, data):
		postdata = []
		for i in data:
			postdata.append('--' + self.boundary) 
			postdata.append('Content-Disposition: form-data; name="%s"' % self.encode(i))
			postdata.append('')
			postdata.append(self.encode(data[i]))
		return '\r\n'.join(postdata)
