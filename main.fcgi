#!/usr/bin/python
from flup.server.fcgi import WSGIServer
#from werkzeug.contrib.fixers import LighttpdCGIRootFix
from main import app

if __name__ == '__main__':
	application = app
#	application.wsgi_app = LighttpdCGIRootFix(application.wsgi_app)
#	WSGIServer(application, bindAddress='/tmp/bioinfo-fcgi.sock').run()
	WSGIServer(application).run()
	

