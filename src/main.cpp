
#include <iostream>
#include <sstream>
#include "ui.h"

// JSON
#include "../json/reader.h"
#include "../json/writer.h"
#include "../json/elements.h"

int main(int argc, char* argv[])
{
	if (argc == 3)
	{
		string s1 ("--json");
		string s2 (argv[1]);
		
		if (s1.compare(s2) == 0)
		{
			UserInterface *ui = new UserInterface(false);
			
			// Use JSON to process input argument.
			string input = argv[2];
			istringstream iss (input, istringstream::in);
			json::Object elRoot;
			json::Reader::Read(elRoot, iss);
			
			json::Number gap = json::Number(elRoot["gap"]);
			json::String method = json::String(elRoot["algorithm"]);
			json::String data1 = elRoot["seqs"][0];
			json::String data2 = elRoot["seqs"][1];
			
			// Use JSON values to really run the program.
			ui->Open(gap.Value(), method.Value(), data1.Value(), data2.Value());
			
			// JSON output formatting.
			json::Object jsobj;
			json::Array seqArr = ui->Print();
			json::Number simNum = ui->getSeqPercent();
			json::Array diffArr = ui->seqDiffArray();
			
			jsobj["alignments"] = seqArr;
			jsobj["similarity"] = simNum;
			jsobj["diffs"] = diffArr;
			
			// Output stream.
			ostringstream oss (ostringstream::out);
			
			// Output JSON string.
			json::Writer::Write(jsobj, oss);
			cout << oss.str();
			
			delete ui;
			return 0;
		}
	}
	else
	{
		cout << "incorrect arguments; arguments given: " << argc << "\n";
	}
	
	return 0;
};
