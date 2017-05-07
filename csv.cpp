#include <fstream>
#include<iostream>
#include<vector>
#include<errno.h>
#include<cstring>
using namespace std;
class CSV{
	string fname;
	fstream file;
	vector<string> mode;
	public:
	CSV(string name){
		fname = name;	
		// TO Open the given file
		open();
	}
	/*
	void addMod(string m){
		// ios::app
		// ios::ate
		// ios::in
		// ios::out
		// ios::trunc
		mode.push_back(m);
	}
	*/
	void open(){
		if(!file.is_open())
		{
			// Firstly open in out mode because if file does not exist then it would create it
			file.open(fname.c_str(),fstream::out);
			file.open(fname.c_str(),fstream::out | fstream::in);
			if(file.bad()){
				error();
			}
		}else{
			cerr << "File is already Open"<<endl;
			error();
		}
	}
	void close(){
		file.close();	
	}
	void error(){
		cerr << "Error: " << strerror(errno)<<endl;
	}
	// Task 1: TO create a csv file with particular column names
	void addColumn(){
		// First to set out pointer at end of first line 
		
	}	
	~CSV(){
		close();
	}	
};
int main(){
CSV f1("test.csv");
return 0;
}
