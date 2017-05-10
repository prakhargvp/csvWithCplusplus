#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <errno.h>
#include <cstring>
using namespace std;
struct col{
	vector<string> d;
};
class CSV{
	fstream file;
	string fname;
	int records;
	vector <col> data;
public:
	CSV(string name=""){
		records = -1;
		fname = name;
	}
	// Utility Function
	// isExist : To check if file already exist or not
	static bool isExist(string name){
		if(ifstream(name.c_str())){
			//File already exists
			return true;
		}else{
			// File does not exists
			return false;
		}		
	}
	// error : Display the Standard error
	void error(){
		cerr << "Error: " << strerror(errno)<<endl;
	}
	// open : TO open the given file
	// return true if all going well
	// return false if any error
	bool open(string name){
		bool fStatus;
		fname = name;
		if(!file.is_open())
		{
			file.open(name.c_str(),fstream::binary | fstream::out | fstream::in);
			if(file.bad()){
				fStatus = false;
			}else{
				fStatus = true;
			}
		}else{
			//File is already Open
			fStatus = false;
		}
		return fStatus;
	}
	// getRecord : return total records
	int getRecord(){
		return records;
	}	
	// read : to read the file and create a dataset
	// return records
	vector<col> read(int rec=0){
	  // rec = 0 means fetch all the records
	  int i=0;
	  bool fetchAll = false;
	  if(rec==0){
	  	records = 0;
	  	fetchAll = true;
	  }
	  //
	  file.seekg(0,ios::beg);
	  while (!file.eof() && (fetchAll || i<rec))
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
	    // Increment Record by 1
	    records++;
	    // increment temp varaible 
	    i++;
	  }
	  return data;
	}
	// getColumn : Get the Column Name
	void getColumn(){
		for(int  i=0;i<data[0].d.size();i++){
			cout <<"| "<< data[0].d[i]<<" ";
		}
		cout <<"|"<< endl;
	}
	// addColumn : Add Column in CSV File
	// return the Column index
	int addColumn(string colName){
		file.seekg(0,ios::beg);
		data[0].d.push_back(colName);		
	}
	// write : write the dataset in file
	void write(string name=""){
		if(name==""){
			name = fname;
		}
		fstream fout;
		fout.open(name.c_str(),ios::out);		
		if(fout.good()){
		for(int i=0;i<data.size();i++){
			for(int j=0;j<data[i].d.size();j++){
				if(j!=0){
					fout << ",";
				}
				fout << data[i].d[j];
			}
			fout << endl;
	  	}
			fout.close();
		}else{
			error();
		}
	}	

};
