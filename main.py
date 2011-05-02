#!/usr/bin/env python

from python.needlemanwunsch import NeedlemanWunsch
from python.load import readfiles
from subprocess import *
from buzhug import Base
import glob, argparse, json, textwrap, math
from flask import Flask, render_template, request, Markup

# Is this application running on a server?
server = False

# Prevents internal server errors in FastCGI.
# print("Content-type: text/html\n")

## TODO: Implement these elsewhere and do them better
biocpp = False
db = []

### Bioinformatics
class Bio:
	def __init__(self):
		self.results = {}
		self.seqs = []
		self.seq = []
		self.name = []
		self.algorithm = ""
		self.error = ""
	
	def addseq(self, seqname):
		self.name.append(seqname)
		self.seq.append(self.seqs[seqname]) # db here
	
	def clearseq(self):
		self.name = []
		self.seq = []
	
	def nw(self):
		if len(self.name) > 2:
			self.error = "Too many sequences for Needleman-Wunsch."
		elif len(self.name) < 2:
			self.error = "Too few sequences for Needleman-Wunsch."
		
		# Use bioinfo binary, or native Python implementation?
		if biocpp:
			output = Popen(["./bioinfo", "-nm", self.seq[0], self.seq[1]], stdout=PIPE).communicate()[0]
			# process output into results here
		else:
			self.alg = NeedlemanWunsch(self.seq[0], self.seq[1])
			self.alg.align()
			self.results['similarity'] = self.alg.homology()
			self.results['alignments'] = [self.alg.A, self.alg.B]
			self.results['diffs'] = self.alg.diffs

### Database



### Web Interface

bio = Bio() # TODO make more modular / OO
bio.seqs = readfiles() # TODO database

app = Flask(__name__)

@app.route("/")
def main():
	return render_template('index.html')

@app.route("/nw")
def nw():
	bio.algorithm = "Needleman-Wunsch"
	
	# Get the sequence input from main page.
	bio.clearseq()
	bio.addseq(str(request.args['s1']))
	bio.addseq(str(request.args['s2']))
	
	# Align.
	bio.nw()
	
	# Format alignment strings for output.
	alignments = []
	
	for result in bio.results['alignments']:
		wrapped = textwrap.wrap(result, 80)
		formatted = []
		linenum = 1
		indices = bio.results['diffs']
		for line in wrapped:
			format = ""
			lastindex = 0
			for index in indices:
				if index >= linenum * 80: # this area has problems......
					indx = math.floor(index / 80) # In case there are two or more lines here.
					print(str(indx) + "indx")
					while indx > 0:
						linenum += 1 # not robust enough! fails on M90848, M90907
						indx -= 1
					break
				else:
					i = index - 80 * (linenum - 1)
					if i < 80 and i >= 0:
						print(lastindex)
						print(i)
						format += line[lastindex:i] + '<span class="hred">' + line[i] + '</span>'
						lastindex = i + 1
			format += line[lastindex:]
			formatted.append(format)
		alignments.append('<br>'.join(formatted))
	
	# If no errors and alignment is done, render to template.
	if bio.alg.done and bio.error == "":
		return render_template('nw.html', \
			results = bio.results,
			name = bio.name,
			alg = bio.algorithm,
			formA = Markup(alignments[0]),
			formB = Markup(alignments[1]),
			lenA = len(bio.seq[0]),
			lenB = len(bio.seq[1]))
	else:
		return bio.error

@app.route("/diffs", methods=['POST'])
def diffs():
	if request.method == 'POST':
		return json.dumps(bio.results['diffs'])

@app.route("/seqs", methods=['POST'])
def seqs():
	if request.method == 'POST':
		return json.dumps(sorted([s[0] for s in bio.seqs.iteritems()]))

# Run web app.
if __name__ == "__main__":
	if server:
		print('bla')
	#	from werkzeug.contrib.fixers import LighttpdCGIRootFix
	#	app.wsgi_app = LighttpdCGIRootFix(app.wsgi_app)
	else:
		app.run(debug=True)

#db.close()
