import fileinput
import os
import glob

from buzhug import TS_Base

#########createDatabase function simply makes the database, if it already exists it ignores##########
def createDatabase():
	#Creates the database with three parts. Create only once!!! 
	sequences = TS_Base('sequences_database')
	sequences.create(('name', str),('sequence',str),('person',str))

#A createDatabase function caller in case you need to make a new database.
#createDatabase()

#########([default] updateDatabase function updates and returns all the sequences in the database###############
def updateDatabase():

	print ""
	print "updateDatabase():"
	print ""
	print "This program simply reads the fasta_data folder and adds those "
	print "files(expect when they already exist) in which case, the program skips over them."
	print "Looking through the 'fasta_data' folder located at '../fasta_data/' now:"
	print ""

	seqs = {}

	#Open the database
	sequences = TS_Base('sequences_database')
	sequences = sequences.open()

	#This imports all the files from the. If the value exists then skips
	path = '../fasta_data/'
	for infile in glob.glob( os.path.join(path, '*.fasta') ):
		#Splits the path to exclude the '../fasta_data' in the path 
		splitstr1 = infile.split(path, len(infile))
		splitstr2 = splitstr1[1]

		#Splits the path once again by getting rid of hte .fasta abrevation at the end
		splitstr3 = splitstr2.split('.', len(infile))
		splitstr4 = splitstr3[0]
		filenamehold = splitstr4

		#Splits the string by the first 6 characters for which are assigned to the sequence name
		m = 0
		filename = ""
		while (m < 6):
			filename = filename + filenamehold[m]
			m = m + 1

		#Last split which takes characters after the first 6 and puts them into the person portion
		inputperson = ""
		while (m < len(filenamehold)):
			inputperson = inputperson + filenamehold[m]
			m = m + 1
		
		#Makes sure that there are no repeat sequences.
		if sequences.select(['name'], name=filename):
			#print filename + " already exists in the database!"
			continue

		#Parses the file to input only the sequence into the database
		fin = open(infile)
		line = fin.readline()
		if not line.startswith(">"):
			raise TypeError("Not a FASTA file: %r" % line)
		title = line
		sequence_lines = [];
		while 1:
			line = fin.readline().rstrip()
			if line == "":
				break
			sequence_lines.append(line)
		inputsequence = "".join(sequence_lines)

		#insert parsed sequence name as 'name' and the inputsequence from the file as 'sequence
		sequences.insert(name=filename, sequence=inputsequence, person=inputperson)

		#closes the current path
		fin.close()
		#end of the for loop

	###All the debuggers, feel free to comment them out
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
	###end of the debuggers
	

	#Close the database
	sequences.close()

	#return the seq[]
	print "The 'sequence_database' database is now updated with any new fasta files in the 'fasta_data' folder"
	print ""
	return seqs

#Included for test purposes to test this readfiles function
updateDatabase()
#createDatabase()
