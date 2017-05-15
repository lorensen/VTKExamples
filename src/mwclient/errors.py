class MwClientError(RuntimeError):
	pass

class MediaWikiVersionError(MwClientError):
	pass

class APIDisabledError(MwClientError):
	pass

class HTTPError(MwClientError):
	pass
class HTTPStatusError(MwClientError):
	pass
class HTTPRedirectError(HTTPError):
	pass

class MaximumRetriesExceeded(MwClientError):
	pass
	
class APIError(MwClientError):
	def __init__(self, code, info, kwargs):
		self.code = code
		self.info = info
		MwClientError.__init__(self, code, info, kwargs)
	
class InsufficientPermission(MwClientError):
	pass
class UserBlocked(InsufficientPermission):
	pass

class EditError(MwClientError):
	pass
class ProtectedPageError(EditError, InsufficientPermission):
	pass
class FileExists(EditError):
	pass
	

class LoginError(MwClientError):
	pass

class EmailError(MwClientError):
	pass
class NoSpecifiedEmail(EmailError):
	pass
	
