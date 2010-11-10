#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>


using namespace std;

int char_to_int(char a)
{	return a - '0';
}

int str_to_int(string b, int w)//unstable function - last string symbol crash
{
	int k=0;
	
	for(;isdigit(b[w]);w++)
				{
		k=k*10+char_to_int(b[w]);
		}
	return k;
}

int wait_for_char(string b, int w, char q)//пробегает до требуемого символа и останавливается ЗА ним
{
    while (b[w] != q) w++; w++;
    return w;
}

int wait_for_digit(string b, int w)//пробегает до цифры и останавливается на ней
{
    while (!isdigit(b[w])) w++;
    return w;
}

double string_to_double(string b, int &w)
{
    double t = 0.0;
    while (b[w] != '.')
    {
        t = t * 10 + char_to_int(b[w]); w++;
    } w++; double flag = 0.1;
    while (isdigit(b[w]))
    {
        t = t + flag * char_to_int(b[w]);
        w++;flag=flag*0.1;
    }
    return t;

}

 string get_string(string b, int &w, char k)//copy string until k
{
    string end = "";
   
	while (b[w] != k)
    {
        end = end + b[w]; w++;
    }

	return end;}

 int endl(string b, int w)//доходит до конца строки и пропускает нижележащие комментарии
    {
        w = wait_for_char(b, w, '\n');
        while (b[w] == '#') wait_for_char(b, w, '\n');
        return w;
    }

   bool contain(string b, string a, int w)//a in b from w-place until ' ' or ' . ' or ' : '
    {
        for (; !isspace(b[w]) || b[w] != '.' || b[w] != ':'; w++) if (a[w] != b[w]) return false;
        return true;
    }

class col
{
public:	
	int counter;
	struct node
	{
		string name;
		int type;
		/*
		0-int;
		1-unsigned int
		2-double
		*/
		vector<int> val0;
		vector<unsigned int> val1;
		vector<double> val2;
	};
	vector<node> columns;
////////////////////////////////////////////////////////

col()
{
	node temp;//for type, etc
    string line;
	ifstream myfile ("Example.txt");
	int c=0;//column's counter
	if (myfile.is_open())
	{
		getline (myfile,line);
		//first string:
		 for(int i=0;i<line.length();i++)
		 {
			while(isspace(line[i]))i++;
			temp.name=get_string(line,i,'(');
			i=wait_for_char(line,i,')');i--;
			int h=0;
			switch (line[i-1])
			{
				case 'i':{temp.type =0;break;}
				case 'u':{temp.type =1;break;}
				case 'd':{temp.type =2;break;}
			}
			columns.push_back(temp);
			c++;
		 }
		counter=c;
		//other//
		while ( myfile.good() )
		{
			getline (myfile,line);
			int i=0;
			c=0;
			while(i<line.length())
			{	
				line=line+" ";
				while(!isdigit(line[i])){i++;}
				switch(columns[c].type)
				{
				case 0:
					{	int trig=1;
						int iddqd = str_to_int(line,i);
						if(line[i-1]=='-')trig=-1;
						columns[c].val0.push_back(trig*str_to_int(line,i));
						break;}
				case 1:
					{	columns[c].val0.push_back(str_to_int(line,i));
						break;}
				case 2:
					{	columns[c].val2.push_back(string_to_double(line,i));
						break;}
				}
				c++;if(c==counter)break;
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file"; 	
	}
///////////////////////////////////////////////////////////////////////////////////////

string nPrinter(node N)
{	
	ostringstream out;
	out<<"\n Name: "<<N.name<<" Type: "<<N.type<<endl;
	out<<" Int: ";
	for(int j=0; j<N.val0.size(); j++)
		out<<N.val0[j]<<" ";
	out<<"\n UInt: ";
	for(int j=0; j<N.val1.size(); j++)
		out<<N.val1[j]<<" ";
	out<<"\n Double: ";
	for(int j=0; j<N.val2.size(); j++)
		out<<N.val2[j]<<" ";
	out<<endl;
	return out.str();
}

string cPrinter(){
	ostringstream out;
	for(int i=0; i<counter; i++)
	{
		out<<nPrinter(columns[i]);
	}
	return out.str();
}

node cGetByN(string N){
	for(int i=0; i<counter; i++)
	{
		if(columns[i].name==N)
			return columns[i];
	}
	cout<<"NO SUCH COLUMN"<<endl;
}

///////////////////////////////////////////////////////////////////////


void Menu()
{
	cout<<" Choose: \n PC(N) for printing column\n WC(N) for writing column to a file\n TC (N) text; for printing text\n" <<endl;
	string cmd,body, arg, text;
	char* tmp="Result.txt";
	ofstream myfile;
	while(1)
	{
		int i=0;
		cin>>cmd;
		/////////////////////////
		while(isspace(cmd[i]))i++;
		body=get_string(cmd,i,'(');i++;
		arg=get_string(cmd,i,')');
		cout<<"B: "<<body<<" A: "<<arg<<endl;
		////////////////////////////////////
		if(body=="PC")
			if(arg=="A")
				cout<<cPrinter();
			else
			{
				cout<<nPrinter(cGetByN(arg));
			}
		if(body=="WC")
			if(arg=="A")
			{myfile.open(tmp); myfile<<cPrinter();myfile.close();}
			else
			{myfile.open(tmp); myfile<<nPrinter(cGetByN(arg)); myfile.close();}
		if(body=="TC")
			{
				myfile.open(tmp);
				i++;
				int place;
				while(i<cmd.length())
				{
					place=cmd.find('*',i);
					if(place>0)
					{
						text=get_string(cmd,i,'*'); 
						myfile<<text;
						if(arg=="A")
							myfile<<cPrinter();
						else
							myfile<<nPrinter(cGetByN(arg));
						i++;
					}
					else
					{
						text=get_string(cmd,i,';');
						myfile<<text;
						break;
					}
				}
				myfile.close();
			}
	}
}
};




int main()
{

col parser;

parser.Menu();


// main code:
 


return 0;
}