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

"""
fasta_files = glob.glob(('../fasta_data/*'))
#print fasta_files
db = []
# Read & Format.
def readfiles():
	seqs = {}
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
	return seqs
# Input all sequences into DB
"""

###This starts my version of the sequencer###############################################################

#This commented outsection reads all the data in the '../fasta_data' folder and prints saves it into the database. Run only once

#If you want to add more fasta files to the database, simply put them in the fasta_data folder and run the updateDatabase.py file in the terminal(not in this file) and it will dynamically update the database.

from buzhug import TS_Base

#Read single file function, able to get multiple inputs from command-prompt/terminal####################
def readfiles():

	#print sys.argv
	 
	if (len(sys.argv[:]) <= 1):
		print ""
		print "***Sorry you need to add 1 or more agruments to your command-prompt/terminal input"
		print "***Some examples are:'M90848', 'M90853', 'M90907' "
		print "***(Other choices can be found in the 'fasta_data' folder)"
		print ""
		exit(0)

	seqs = {}
	m = 1
	while (len(sys.argv) > m):
		file_name = sys.argv[m]

		#Checks if the person accidently put a extension on the file input and deletes that extension
		bey = file_name
		bee = bey.split('.fasta', len(bey))
		file_name = bee[0]

		#Open the database
		sequences = TS_Base('sequences_database')
		sequences = sequences.open()
		
		#finds and prints out the sequence your inputed sequences
		#if you wish to customize it simply add to variable to the name
		print ""
		print "***" + file_name + " sequence contains:"
	
		see = sequences.select(['sequence'],name = file_name)

		if not see:
			print "Sorry " + file_name + " does not exist in the database!"
			print "Some examples are:'M90848', 'M90853', 'M90907' "
			print "More options are included in the 'fasta_data' folder, note the extension is not needed."
			print ""
			exit(0)


		i = 0
		for record in see:
			print record.sequence
			seqs[i] = record.sequence
			i = i + 1
		#iterator for m
		m = m + 1
		see = ""

	#returns those sequences
	print ""
	return seqs

#method call for readfiles()
readfiles()


###############readAllFiles(): Return all fasta files in database####################################
def readAllFiles():

	print "This function prints out and returns all the fasta files in the database in a seq{} array:"

	seqs = {}

	#Open the database
	sequences = TS_Base('sequences_database')
	sequences = sequences.open()

	###All the debuggers, feel free to comment them out###
	#prints out the total number of sequences in the database:
	print ""
	print "***The total number of sequences in the 'sequence_database' are:"
	print len(sequences)

	#prints out all the sequence names that are currently in the database
	print ""
	print "***The sequences currently in the database are now:"
	printall = sequences.select(['name'])

	i = 0
	for record in printall:
		print record.name

		#Add the name to the Seq{} array to be returned later
		seqs[i] = record.name
		i = i + 1

	print ""

	#Debugger print out all in the array
	#print seqs

	###end of the debuggers###

	#Close the database
	sequences.close()

	#return the seq[]
	return seqs

#A readAllFiles function caller that returns all the fasta files in the database
#readAllFiles()
