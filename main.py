#!/usr/bin/env python

from subprocess import *
from buzhug import Base
import glob, argparse, web

fasta_files = glob.glob(('./fasta_data/*'))
seqs = {}
db = []

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

### Bioinformatics

def callbio(seq1, seq2):
	output = Popen(["./bioinfo", "-nm", seqs[seq1], seqs[seq2]], stdout=PIPE).communicate()[0]
	return output

### Database

loading = False

# Define a command-line argument for loading the database.
parser = argparse.ArgumentParser(description='Load sequences into database, one-time only.')
parser.add_argument('--load', action='store_true')
args = parser.parse_args()
print(args)
if args.load:
	print(args.load)
#	db = Base('./db')
#	loading = True

### Web Interface

#print("Content-type: text/html\n")

urls = (
	'/', 'main'
#	'/seq', 'seq'
)

class main:
	def GET(self):
		readfiles()
		out = callbio("M90848", "M90849")
		message = "Welcome to bioinfo!\nHere's your output:\n" + out
		return message

"""
class seq:
	def POST():
		return render.seq(name)
"""

# Run web app.
if __name__ == "__main__":
 	if not loading:
		app = web.application(urls, globals())
		app.run()

db.close()
