import glob

fasta_files = glob.glob(('./fasta_data/*'))
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

