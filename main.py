#!/usr/bin/env python

from python.needlemanwunsch import NeedlemanWunsch
from python.load import readfiles
from python.bio import Bioinformatics as Bio
import json, textwrap, math
from flask import Flask, render_template, request, Markup
from buzhug import TS_Base

### Bioinformatics


## TODO: Implement these elsewhere and do them better
biocpp = True

### Web Interface

bio = Bio() # TODO make more modular / OO
bio.seqs = readfiles() # TODO database

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
		return bio.error + "bla"

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
	app.debug = True
	app.run()

