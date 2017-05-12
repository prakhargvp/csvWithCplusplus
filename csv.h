#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <errno.h>
#include <cstring>
#include <string>  
using namespace std;
struct col{
	vector<string> d;
};
struct ccompare{
	ccompare(int sType){
		this->sType = sType;
	}
	bool operator () (string lhs, string rhs){
		string str1,str2;
		str1 = lhs;
		str2 = rhs;
		// 0 => int
		// 1 => Ascii-case sensitive
		// 2 => Ascii-case in-sensiti
		if(sType==0){
			return (stoi)(str1) < stoi(str2);
		}else if(sType==2){
			std::transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
			std::transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
			return str1 < str2;
		}else {
			return str1 < str2;
		}
	}
	int sType;
};
struct acompare{
	acompare(int colNum,int sType){
		this->colNum = colNum;
		this->sType = sType;
	}
	bool operator () (col lhs, col rhs){
		string str1,str2;
		str1 = lhs.d[colNum];
		str2 = rhs.d[colNum];
		// 0 => int
		// 1 => Ascii-case sensitive
		// 2 => Ascii-case in-sensiti
		if(sType==0){
			return (stoi)(str1) < stoi(str2);
		}else if(sType==2){
			std::transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
			std::transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
			return str1 < str2;
		}else {
			return str1 < str2;
		}
	}
	int colNum,sType;
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
	vector<col> read(int );
	int totalColumn();
	// getColumn : return the sttructur
	col getColumn();
	// printColumn : Get the Column Name
	void printColumn();
	// addColumn : Add Column in CSV File
	// return the Column index
	int addColumn(string colName);
	// write : write the dataset in file
	void write(string name="");
	// sort
	void sort(int colNum,int sortType);	
	// compare : return true or false
	// true if same structure
	// false if not same structure
	// compareStructure
	/*
	int compStruct(const CSV& obj1,int caseSens);
	*/
	void setData(vector <col>);
	int getIndexNo(string);
	int IsDuplicate(int);
	int removeDuplicate(int);
	int removeDuplicateCol(int colNo,int caseS);
	// getData
	vector <col> getData(int);
	static string toLower(string str,int convert=1){
		if(convert){
			transform(str.begin(), str.end(), str.begin(), ::tolower);
		}
		return str;
	}
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
	vector<col> CSV::read(int rec=0){
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
	// getColumn : return the sttructur
	col CSV::getColumn(){
		return data[0];
	}
	// printColumn : Get the Column Name
	void CSV::printColumn(){
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
	void CSV::sort(int colNum=0, int sortType=1){
		std::sort(data.begin()+1,data.end(),acompare(colNum,sortType));

	}
	void CSV::print(){
	  for(int i=0;i<data.size();i++){
		for(int j=0;j<data[i].d.size();j++){
			cout << data[i].d[j] << " ";
		}
		cout << endl;
	  }
	}
	// compareStructure
	/*
	int compStruct(const CSV& obj1,int caseSens=0){
		return 1;
	}
	*/
	int CSV::IsDuplicate(int caseS=0){
		int flag = 0;

		for(int i=1;i<records;i++){
			int tcount = 0;
			for(int j=0;j<data[i].d.size();j++){
				if(toLower(data[i].d[j],caseS)==toLower(data[i+1].d[j],caseS)){
					tcount++;
				}
			}
			if(tcount == data[i].d.size()){
				flag++;
			}
		}
		return flag;
	}
	int CSV::removeDuplicate(int caseS=0){
		int flag = 0;
		int i=1;
		while(i<data.size()-1){
			int tcount = 0;
			for(int j=0;j<data[i].d.size();j++){
				if(toLower(data[i].d[j],caseS)==toLower(data[i+1].d[j],caseS)){
					tcount++;
				}
			}
			if(tcount == data[i].d.size()){
				data.erase(data.begin() + i + 1);
				flag++;
			}else{
				i++;
			}
		}
		return flag;
	}
	int CSV::removeDuplicateCol(int colNo,int caseS=0){
		int flag = 0;
		int i=1;
		while(i<data.size()-1){
			int tcount = 0;

			if(toLower(data[i].d[colNo],caseS)==toLower(data[i+1].d[colNo],caseS)){
				tcount++;
			}
			if(tcount == 1){
				data.erase(data.begin() + i + 1);
				flag++;
			}else{
				i++;
			}
		}
		return flag;
	}
	int CSV::getIndexNo(string str){
		int index=-1;
		for(int i=0;i<columns;i++){
			if(toLower(str)==toLower(data[0].d[i])){
				index = i;
			}
		}
		return index;
	}
	vector <col> CSV::getData(int recordno=-1){
		return data;
	}
	void CSV::setData(vector <col> d){
		data = d;
	}