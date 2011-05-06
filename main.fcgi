#!/usr/bin/python
from flup.server.fcgi import WSGIServer
from main import app

if __name__ == '__main__':
	application = app
	WSGIServer(application).run()
