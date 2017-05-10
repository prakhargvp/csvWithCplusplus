#include <fstream>
#include<iostream>
#include<sstream>
#include<vector>
#include<errno.h>
#include<cstring>
using namespace std;
class CSV{
	string fname;
	fstream file;
	vector<string> mode;
 	vector <vector <string> > data;
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
			//file.open(fname.c_str(),fstream::out);
			file.open(fname.c_str(),fstream::binary | fstream::out | fstream::in);
			if(file.bad()){
				error();
			}else{
				read();
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
	void read(){

	  file.seekg(0,ios::beg);
	  while (!file.eof())
	  {
	    string s;
	    if (!getline( file, s )) break;

	    istringstream ss( s );
	    vector <string> record;

	    while (ss)
	    {
	      string s;
	      if (!getline( ss, s, ',' )) break;
	      record.push_back( s );
	    }

	    data.push_back( record );
	  }

	}
	void write(){
		
	}
	void print(){
	  for(int i=0;i<data.size();i++){
		for(int j=0;j<data[i].size();j++){
			cout << data[i][j] << " ";
		}
		cout << endl;
	  }
	}
	// Task 1: TO create a csv file with particular column names
	void addColumn(const char *cName){
		// First to set out pointer at end of first line 
		string line;		
		// file_pointer.seekg (number of bytes ,Reference point);
		file.seekg(0,ios::beg);
		data[0].push_back(cName);
	}	
	~CSV(){
		close();
	}	
};
int main(){
CSV f1("test.csv");
f1.addColumn("Column3");
f1.print();
return 0;
}
