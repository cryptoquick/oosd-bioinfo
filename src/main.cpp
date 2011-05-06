
//#include <string>
//#include <string.h>
//
//#include <vector>
//#include "libjson.h"
#include <iostream>
#include <sstream>
#include "ui.h"

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
			ostringstream oss (ostringstream::out);
			
			json::Object jsobj;
			jsobj["Name"] = json::String("Schlafly American Pale Ale");
			jsobj["Origin"] = json::String("St. Louis, MO, USA");
			jsobj["ABV"] = json::Number(3.8);
			jsobj["BottleConditioned"] = json::Boolean(true);
			
			json::Writer::Write(jsobj, oss);
			
			cout << oss.str();
			
			// int gap = (int)argv[2];
			// 		string method = argv[3];
			// 		string data1 = argv[4];
			// 		string data2 = argv[5];
			// 		
			// 		ui->Open(gap, method, data1, data2);
			// 		ui->Compare();
			// 		ui->Print();
			// 		delete ui;
			return 0;
		}
	}
	else
	{
		cout << "incorrect arguments; arguments given: " << argc << "\n";
	}
	
	return 0;
};
