import glob

#My added includes
import fileinput
import os
import sys


##########This program includes three methods(one disabled)#####################
####
#### readfiles(): the default function, for which returns sequences you enter as 
####              extra agruments into the terminal
####		  "Example: python load.py M90848dentist M90907patientH
####
#### readallfiles(): this function, returns all the sequences in the database
####                  (you have to activate this one by calling it.)
####
################################################################################


#This is your sequencer Alex, I disabled it and went with my own. My version is below this one. Note it also returns a seq{} array so there should be a minimal amount of problems with exception of the method for which you parsed the files.


from buzhug import TS_Base

fasta_files = glob.glob(('./fasta_data/*'))
db = []
seqs = {}

# Read & Format.
"""
def readfiles():

	for file_name in fasta_files:
		print file_name
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
		#print seqs
		f.close()	
	return seqs

# Input all sequences into DB
readfiles()
"""

###This starts my version of the sequencer###############################################################

#This part reads all the data in the 'sequence_database' database and loads it on the webpage.

#If you want to add more fasta files to the database, simply put them in the fasta_data folder and run the updateDatabase.py file in the terminal(not in this file) and it will dynamically update the database.

def selectrecord(seqname):
	db = TS_Base('db')
	db.open()
	result = db.select(['sequence'], name = seqname)
	for record in result:
	    seq = record.sequence
	db.close()
	return seq

def readfiles():
	sequences = TS_Base('db')
	sequences = sequences.open()
	see = sequences.select(None)

	for record in see:
		seq = ""
		name = ""
		
		seq = record.sequence
		name = record.name
		
		if (seq != ''):
			seqs[name[:6]] = seq
	
		#print seqs
	sequences.close()
	return seqs

#readfiles()
