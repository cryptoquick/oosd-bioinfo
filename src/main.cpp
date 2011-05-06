
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
			
			string input = argv[2];
			istringstream iss (input, istringstream::in);
			json::Object elRoot;
			json::Reader::Read(elRoot, iss);
			
			json::Number gap = json::Number(elRoot["gap"]);
			json::String method = json::String(elRoot["algorithm"]);
			json::String data1 = elRoot["seqs"][0];
			json::String data2 = elRoot["seqs"][1];
		
			ui->Open(gap.Value(), method.Value(), data1.Value(), data2.Value());
			
			// JSON formatting.
			json::Object jsobj;
			json::Array seqArr = ui->Print();
			jsobj["alignments"] = seqArr;
			
			// Output stream.
			ostringstream oss (ostringstream::out);
			
			// JSON formatting.
		//	json::Object jsobj;
		//	jsobj["alignments"] = ui->Print();
			
			// Output JSON string.
			json::Writer::Write(jsobj, oss);
		//	json::Writer::Write(elRoot, oss);
			cout << oss.str();
			
		/*	json::Object jsobj;
			jsobj["Name"] = json::String("Schlafly American Pale Ale");
			jsobj["Origin"] = json::String("St. Louis, MO, USA");
			jsobj["ABV"] = json::Number(3.8);
			jsobj["BottleConditioned"] = json::Boolean(true);*/
			
			// int gap = (int)argv[2];
			// 		string method = argv[3];
			// 		string data1 = argv[4];
			// 		string data2 = argv[5];
			// 		
			// 		ui->Open(gap, method, data1, data2);
			// 		ui->Compare();
			// 		ui->Print();
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
