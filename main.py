#!/usr/bin/env python

from python.needlemanwunsch import NeedlemanWunsch
from python.load import readfiles
from subprocess import *
from buzhug import Base
import glob, argparse, web

biocpp = False
db = []
#seqs = {} # to be deprecated

### Bioinformatics

def callbio(seqs, name1, name2):
	print(seqs)
	seq1 = seqs[name1] # db here
	seq2 = seqs[name2]
	
	results = {}
	
	if biocpp:
		output = Popen(["./bioinfo", "-nm", seq1, seq2], stdout=PIPE).communicate()[0]
		# process output into results here
	else:
		nw = NeedlemanWunsch(seq1, seq2)
		nw.align()
		results['similarity'] = nw.homology()
		results['alignA'] = nw.A
		results['alignB'] = nw.B
	
	return results

### Database

loading = False

# Define a command-line argument for loading the database.
'''parser = argparse.ArgumentParser(description='Load sequences into database, one-time only.')
parser.add_argument('--load', action='store_true')
args = parser.parse_args()
print(args)
if args.load:
	print(args.load)
#	db = Base('./db')
#	loading = True'''

### Web Interface

#print("Content-type: text/html\n")

urls = (
	'/', 'main'
#	'/seq', 'seq'
)

render = web.template.render('templates/')

class main:
	def GET(self):
		seqs = readfiles()
		results = callbio(seqs, "M90848", "M90855")
		#message = "Welcome to bioinfo!\nHere's your output:\n" + out
		return render.index(results['similarity'], results['alignA'], results['alignB'])

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

#db.close()
