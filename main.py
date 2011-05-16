#!/usr/bin/env python

from python.needlemanwunsch import NeedlemanWunsch
import python.load
from python.bio import Bioinformatics as Bio
import json, textwrap, math
from flask import Flask, render_template, request, Markup
from buzhug import TS_Base

### Bioinformatics


## TODO: Implement these elsewhere and do them better
biocpp = True

### Web Interface

bio = Bio() # TODO make more modular / OO
app = Flask(__name__)

@app.route("/")
def main():
	return render_template('index.html')
	
@app.route("/nw")
def nw():
	bio.algorithm = "needleman"
	bio.cpp = True
	# Get the sequence input from main page.
	bio.clearseq()
	bio.addseq(str(request.args['s1']))
	bio.addseq(str(request.args['s2']))
	
	# Align.
	bio.nw()
	
	# If no errors and alignment is done, render to template.
	if bio.error == "":
		return render_template('nw.html',
			results = bio.results,
			name = bio.name,
			alg = bio.algorithm,
			formA = bio.results['alignments'][0], #Markup(alignments[0]),
			formB = bio.results['alignments'][1], #Markup(alignments[1]),
			lenA = len(bio.seq[0]),
			lenB = len(bio.seq[1]))
	else:
		return bio.error + " error!"

@app.route("/diffs", methods=['POST'])
def diffs():
	if request.method == 'POST':
		return json.dumps(bio.results['diffs'])

@app.route("/seqs", methods=['POST'])
def seqs():
	if request.method == 'POST':
		return json.dumps(sorted([s[0] for s in python.load.readfiles().iteritems()]))

@app.route("/msa")
def msa():
	bio.algorithm = "msa"
	bio.cpp = True
	bio.clearseq()
	seqs = str(request.args['seqs']).split(',')
	
	if len(seqs) <= 6:
		[bio.addseq(s) for s in seqs]
		bio.msa()
		items = zip(bio.results['alignments'], bio.name)
		return render_template('msa.html',
			items = items,
			tree = bio.results['tree'])
	else:
		return "Too many sequences!"
	
# Run web app.
if __name__ == "__main__":
	app.debug = True
	app.run()
<<<<<<< local
=======

>>>>>>> other
