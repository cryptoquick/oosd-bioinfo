from subprocess import *
import glob

fasta_files = glob.glob(('fasta_data/*'))

seqs = {}

# Read & Format
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

output = Popen(["./bioinfo", "-nm", seqs["M90848"], seqs["M90849"]], stdout=PIPE).communicate()[0]
print(output)

