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
struct acompare{
	acompare(int colNum){this->colNum = colNum;}
	bool operator () (col lhs, col rhs){return lhs.d[colNum] < rhs.d[colNum];}
	int colNum;
};
//bool acompare(col lhs, col rhs) { return lhs.d[0] < rhs.d[0]; }
class CSV{
	fstream file;
	string fname;
	int records;
	int columns;
	vector <col> data;
public:
	CSV(string name=""){
		records = -1;
		fname = name;
		columns = 0;
	}
	// Utility Function
	// isExist : To check if file already exist or not
	static bool isExist(string name);	
	// error : Display the Standard error
	void error();
	void close();
	// open : TO open the given file
	// return true if all going well
	// return false if any error
	bool open(string name);
	// getRecord : return total records
	int getRecord();	
	// read : to read the file and create a dataset
	// return records
	vector<col> read(int rec=0);
	int totalColumn();
	// getColumn : Get the Column Name
	void getColumn();
	// addColumn : Add Column in CSV File
	// return the Column index
	int addColumn(string colName);
	// write : write the dataset in file
	void write(string name="");
	// sort
	void sort(int colNum);	
	void print();
	~CSV(){
		close();
	}	
};
	// Utility Function
	// isExist : To check if file already exist or not
	bool CSV::isExist(string name){
		if(ifstream(name.c_str())){
			//File already exists
			return true;
		}else{
			// File does not exists
			return false;
		}		
	}
	// error : Display the Standard error
	void CSV::error(){
		cerr << "Error: " << strerror(errno)<<endl;
	}
	void CSV::close(){
		file.close();	
	}
	// open : TO open the given file
	// return true if all going well
	// return false if any error
	bool CSV::open(string name){
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
	int CSV::getRecord(){
		return records;
	}	
	// read : to read the file and create a dataset
	// return records
	vector<col> CSV::read(int rec){
	  // rec = 0 means fetch all the records
	  int i=0;
	  bool fetchAll = false;
	  if(rec==0){
	  	records = -1;
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
	    columns = 0;
	    col s1;
	    while (ss)
	    {
	      string s;
	      if (!getline( ss, s, ',' )) break;
	      s1.d.push_back(s);
	      // Count Columns
	      columns++;
	    }
	    data.push_back(s1);
	    // Increment Record by 1
	    records++;
	    // increment temp varaible 
	    i++;
	  }
	  return data;
	}
	int CSV::totalColumn(){
		return columns;
	}
	// getColumn : Get the Column Name
	void CSV::getColumn(){
		if(records>-1){
			for(int  i=0;i<data[0].d.size();i++){
				cout <<"| "<< data[0].d[i]<<" ";
			}
			cout <<"|";
		}
		cout<<endl;
	}
	// addColumn : Add Column in CSV File
	// return the Column index
	int CSV::addColumn(string colName){
		file.seekg(0,ios::beg);
		if(records==-1){
			col firstLine;
			data.push_back(firstLine);
			// increment the record to be -1 to 0
			// -1 means file is empty
			// 0 means header is available but no record
			records++;
		}
		data[0].d.push_back(colName);	
		columns++;
	}
	// write : write the dataset in file
	void CSV::write(string name){
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
			// Don't end new line in last record
			if(i < data.size()-1){
				fout << endl;
			}
	  	}
			fout.close();
		}else{
			error();
		}
	}	
	// sort
	void CSV::sort(int colNum){
		std::sort(data.begin()+1,data.end(),acompare(colNum));

	}
	void CSV::print(){
	  for(int i=0;i<data.size();i++){
		for(int j=0;j<data[i].d.size();j++){
			cout << data[i].d[j] << " ";
		}
		cout << endl;
	  }
	}