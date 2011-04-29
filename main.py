#!/usr/bin/env python

from subprocess import *
import glob, web

### Web Interface

urls = (
	'/', 'main'
)

class main:
	def GET(self):
		readfiles()
		out = callbio()
		message = "Welcome to bioinfo!\nHere's your output:\n" + out
		return message

# Run web app.
if __name__ == "__main__":
	app = web.application(urls, globals())
	app.run()

### Bioinformatics

fasta_files = glob.glob(('fasta_data/*'))
seqs = {}

# Read & Format.
def readfiles():
	for file_name in fasta_files:
		f = open(file_name, "r")
		flines = f.readlines()
		seq = ""
		name = ""
		for el in flines[1:]:
			seq += el.strip()
		for el in flines[:1]:
			name = el.split('|')[3]
		if (seq != ''):
			seqs[name[:6]] = seq
		f.close()

def callbio():
	output = Popen(["./bioinfo", "-nm", seqs["M90848"], seqs["M90849"]], stdout=PIPE).communicate()[0]
	return output
