
#include <iostream>
#include <sstream>
#include "ui.h"
#include "msa.h"

int main(int argc, char* argv[])
{
	if (argc == 3)
	{
		string s1 ("--json");
		string s2 (argv[1]);
		
		if (s1.compare(s2) == 0)
		{
			
			
			// Use JSON to process input argument.
			string input = argv[2];
			istringstream iss (input, istringstream::in);
			json::Object elRoot;
			json::Reader::Read(elRoot, iss);
			
			json::Number gap = json::Number(elRoot["gap"]);
			json::String method = json::String(elRoot["algorithm"]);
			json::Array data = elRoot["seqs"];
			json::String data1 = elRoot["seqs"][0];
			json::String data2 = elRoot["seqs"][1];
			
			json::Object jsobj;
			json::Array seqArr;
			json::Array diffArr;
			
			string jsnw = "needleman";
			string jsmith = "smith";
			string jsmsa = "msa";
			
			if (method.Value().compare(jsnw) == 0) {
				UserInterface *ui = new UserInterface(false);
				
				// Use JSON values to really run the program.
				ui->Open(gap.Value(), method.Value(), data1.Value(), data2.Value());

				// JSON output formatting.
				seqArr = ui->Print();
			//	simNum = ui->getSeqPercent();
				diffArr = ui->seqDiffArray();
				
				delete ui;
			}
			else if (method.Value().compare(jsmsa) == 0) {
				MSA *msa = new MSA();
				
				for (unsigned int i = 0; i < data.Size(); i++) {
					json::String jsdata = data[i];
					Sequence * seq;
					seq = new Sequence(jsdata.Value());
					vector<char> seqdata = seq->get();
					msa->addSeq(seqdata);
				}
				
				msa->align();
				seqArr = msa->printSeqs();
			}
			
			jsobj["alignments"] = seqArr;
		//	jsobj["diffs"] = diffArr;
			
			// Output stream.
			ostringstream oss (ostringstream::out);
			
			// Output JSON string.
			json::Writer::Write(jsobj, oss);
			cout << oss.str();
			
			return 0;
		}
	}
	else
	{
		cout << "incorrect arguments; arguments given: " << argc << "\n";
	}
	
	return 0;
};
