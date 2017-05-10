#include <fstream>
#include<iostream>
#include<sstream>
#include<vector>
#include<errno.h>
#include<cstring>
using namespace std;
struct col{
	vector<string> d;
};
class CSV{
	string fname;
	fstream file;
	vector<string> mode;
 	vector <col> data;
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
	    vector<col> record;

	    col s1;
	    while (ss)
	    {
	      string s;
	      if (!getline( ss, s, ',' )) break;
	      s1.d.push_back(s);
	    }
	    data.push_back(s1);
	  }

	}
	void write(){
		fstream fout;
		fout.open("output.csv",ios::out);		
		if(fout.good()){
		for(int i=0;i<data.size();i++){
			for(int j=0;j<data[i].d.size();j++){
				fout << data[i].d[j] << " ";
			}
			fout << endl;
	  	}
			fout.close();
		}else{
			error();
		}
	
	}
	void print(){
	  for(int i=0;i<data.size();i++){
		for(int j=0;j<data[i].d.size();j++){
			cout << data[i].d[j] << " ";
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
		data[0].d.push_back(cName);
	}	
	~CSV(){
		close();
	}	
};
int main(){
/*
CSV f1("test.csv");
f1.addColumn("Column3");
f1.addColumn("Column4");
f1.addColumn("Column5");
f1.print();
f1.write();
*/
	int option;
	// Menus
	cout <<"Menus : "<<endl;
	cout <<"1. Add Column"<<endl;
	cout <<"2. IsSameStructure"<<endl;
	cout <<"3. IsDuplicate"<<endl;
	cout <<"4. RemoveDuplicate"<<endl;
	cout <<"5. sort"<<endl;
	cout <<"6. union"<<endl;
	cout <<"7. intersection"<<endl;
	cout <<"8. Exit"<<endl;
	cin << option;
	switch(option){
		case 1:
			cout << "Enter the File Name : " <<endl;
		break;
	}
return 0;
}
