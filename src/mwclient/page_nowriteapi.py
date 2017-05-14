import time
from HTMLParser import HTMLParser
from htmlentitydefs import name2codepoint 

import errors

class OldPage(object):
	@staticmethod
	def save(self, text = u'', summary = u'', minor = False):
		data = {}
		data['wpTextbox1'] = text
		data['wpSummary'] = summary
		data['wpSave'] = 'Save page'
		data['wpEditToken'] = self.get_token('edit')
		if self.last_rev_time:
			data['wpEdittime'] = time.strftime('%Y%m%d%H%M%S', self.last_rev_time)
		else:
			data['wpEdittime'] = time.strftime('%Y%m%d%H%M%S', time.gmtime())
		if self.edit_time:
			data['wpStarttime'] = time.strftime('%Y%m%d%H%M%S', self.edit_time)
		else:
			data['wpStarttime'] = time.strftime('%Y%m%d%H%M%S', time.gmtime())
		data['wpStarttime'] = time.strftime('%Y%m%d%H%M%S', time.gmtime())

		if minor: data['wpMinoredit'] = '1'
		data['title'] = self.name
		
		page_data = self.site.raw_index('submit', **data)
				
		page = EditPage('editform')
		page.feed(page_data)
		page.close()
		
		if page.data:
			if page.readonly: raise errors.ProtectedPageError(self)
			self.get_token('edit',  True)
			raise errors.EditError(page.title, data)

	@staticmethod
	def move(self, new_title, reason = '', move_talk = True):
		postdata = {'wpNewTitle': new_title,
			'wpOldTitle': self.name,
			'wpReason': reason,
			'wpMove': '1',
			'wpEditToken': self.get_token('move')}
		if move_talk: postdata['wpMovetalk'] = '1'
		postdata['title'] = 'Special:Movepage'
		
		page_data = self.site.raw_index('submit', **data)
				
		page = EditPage('movepage')
		page.feed(page_data.decode('utf-8', 'ignore'))
		page.close()
		
		if 'wpEditToken' in page.data:
			raise errors.EditError(page.title, postdata)
			
	@staticmethod
	def delete(self, reason = ''):
		postdata = {'wpReason': reason,
			'wpConfirmB': 'Delete',
			'mw-filedelete-submit': 'Delete',
			'wpEditToken': self.get_token('delete'),
			'title': self.name}
			
		page_data = self.site.raw_index('delete', **postdata)

class EditPage(HTMLParser):
	def __init__(self, form):
		HTMLParser.__init__(self)
		
		self.form = form
		
		self.in_form = False
		self.in_text = False
		self.in_title = False
		
		self.data = {}
		self.textdata = []
		self.title = u''
		
		self.readonly = True
		
	def handle_starttag(self, tag, attrs):
		self.in_title = (tag == 'title')
		
		if (u'id', self.form) in attrs:
			attrs = dict(attrs)
			self.in_form = True
			self.action = attrs['action']
			
		if tag == 'input' and self.in_form and (u'type', u'submit') \
				not in attrs and (u'type', u'checkbox') not in attrs:
			attrs = dict(attrs)
			if u'name' in attrs: self.data[attrs[u'name']] = attrs.get(u'value', u'')
			
		if self.in_form and tag == 'textarea':
			self.in_text = True
			self.readonly = (u'readonly', u'readonly') in attrs
	
			
	def handle_endtag(self, tag):
		if self.in_title and tag == 'title': self.in_title = False
		if self.in_form and tag == 'form': self.in_form = False
		if self.in_text and tag == 'textarea': self.in_text = False
	
	def handle_data(self, data):
		if self.in_text: self.textdata.append(data)
		if self.in_title: self.title += data
		
	def handle_entityref(self, name):
		if name in name2codepoint: 
			self.handle_data(unichr(name2codepoint[name]))
		else:
			self.handle_data(u'&%s;' % name)
	def handle_charref(self, name):
		try:
			self.handle_data(unichr(int(name)))
		except ValueError:
			self.handle_data(u'&#$s;' % name)
		
