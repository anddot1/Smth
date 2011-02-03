#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
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

		double string_to_double(string b, int w)
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
{public:	
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



col(char* F)
{
	node temp;//additional column
    string line;//string from file
	bool flag=false;//first string or not
	//ifstream myfile ("Example.txt");//reading file
	ifstream myfile(F);
	 int c=0;//column's counter
  //columns=new vector<node>();
if (myfile.is_open())
  {
while ( myfile.good() )
{
			     getline (myfile,line);
					//myfile>> line;
				 cout << line << endl;
				
				 if(!flag)
				 { //first string:

					 for(int i=0;i<line.length()-1;i++)
					 {
						while(isspace(line[i]))i++;
			
						temp.name=get_string(line,i,'(');
						i=wait_for_char(line,i,')');i--;
					//cout<<line[i]<<endl;
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
					flag=true;
					 counter=c;
				}else{
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//cout<<endl<<"col. counter: "<<counter<<endl;
	for(int u=0;u<counter;u++)
	{
		//cout<<"col: "<<u<<"  type:"<<columns[u].type<<endl;
	}
	int i=0;
	c=0;
	//getline (myfile,line);
		//myfile>> line;
	//cout << line << endl;

	

	while(i<line.length())
	{	//cout<<endl<<"line inforemation: "<<line<<endl;
	line=line+" ";
	
	while(!isdigit(line[i])){i++;}
	//cout<<"counter: "<<c<<" col type: "<<columns[c].type<<endl;
		switch(columns[c].type)
		{
		case 0:
			{int trig=1;
			int iddqd = str_to_int(line,i);if(line[i-1]=='-')trig=-1;
			
			columns[c].val0.push_back(trig*str_to_int(line,i));

				break;
			}
		
		case 1:
			{	columns[c].val0.push_back(str_to_int(line,i));
				break;
			}
			
		case 2:
			{
			columns[c].val2.push_back(string_to_double(line,i));
				break;
			}
	}
c++;
if(c==counter)break;
  }
 }
}
    myfile.close();//cout<<"lol";
  }
  else cout << "Unable to open file"; 
 // cout<<"here we are: "<<endl;


 // for(int y=0;y<columns.size();y++)
//{
	//switch(columns[y].type)
	//{
	//case 0:{for(int h=0;h<columns[y].val0.size();h++)cout<<columns[y].val0[h]<<" from "<<columns[y].name<<endl;break;}
	//case 1:{for(int h=0;h<columns[y].val1.size();h++)cout<<columns[y].val1[h]<<" from "<<columns[y].name<<endl;break;}
	//case 2:{for(int h=0;h<columns[y].val2 .size();h++)cout<<columns[y].val2[h]<<" from "<<columns[y].name<<endl;break;}
	
	//}

//}
		}

///////////////////////////////////////////////////////////////////////////////////////
string nPrinter(node N) //NOT_USED//
{
        ostringstream out;
        out<<"\n Name: "<<N.name<<" Type: "<<N.type<<endl;
        out<<" Int: ";
        for(int j=0; j<N.val0.size(); j++)
                out<<N.val0[j]<<"	";
        out<<"\n UInt: ";
        for(int j=0; j<N.val1.size(); j++)
                out<<N.val0[j]<<"	";
        out<<"\n Double: ";
        for(int j=0; j<N.val2.size(); j++)
                out<<N.val2[j]<<"	";
        out<<endl;
        return out.str();
}


string cPrinter(vector<node> N)
{	
	ostringstream out;
	///FIRST_STR///
	for (int i=0; i<N.size(); i++)
	out<<N[i].name<<"("<<N[i].type<<")   ";
	out<<endl;
	///OTHER///
	int S;
	if(N[0].type==0)
		S=N[0].val0.size();
	else if(N[0].type==1)
		S=N[0].val1.size();
	else
		S=N[0].val2.size();
	for(int j=0; j<S; j++)
	{
		for (int i=0; i<N.size(); i++)
		{

			if(N[i].type==0)
				out<<N[i].val0[j]<<"	";
			else if(N[i].type==1)
				out<<N[i].val0[j]<<"	";
			else
				out<<N[i].val2[j]<<"	";
		}
		out<<endl;
	}
	return out.str();
}

string cPrinter()
{
	ostringstream out;
	for(int i=0; i<counter; i++)
	{
		out<<nPrinter(columns[i]);
	}
	return out.str();
}

node cGetByN(string N)
{
        for(int i=0; i<columns.size(); i++)
	{
		if(columns[i].name==N)
            {
                    return columns[i];}
	}
	node n;
	n.type=-1;
        cout<<"THERE IS NO COLUMN WITH SUCH NAME"<<endl;
	return n;
}

///////////////////////////////////////////////////////////////////////


void Menu() //МНОГО_ИЗВРАЩЕНИЙ//
{
        printf( gettext( "text" ) );
	//cout<<" Choose:\n CF(Filename.txt) for choosing file \n PC(N) for printing column called N\n PF(N) for the same in file\n PCN(N) and PFN(N) for the same with number\n Ctrl+C for exit\n" <<endl;
	string cmd,body, text;
	int i, p, place;
	vector<string> args;
	char* tmp=new char[100];
	vector<node> C;
	//tmp="Result.txt";
	ofstream myfile;
	while(1)
	{
		i=0; 
		cin>>cmd;
		///GETTING_BODY///
		while(isspace(cmd[i]))i++;
		body=get_string(cmd,i,'(');i++;
		///CMDS_WITHOUT_ARGS///
                if(body=="EX") 
		  //exit(0)
		;
                ///GETTING_ARGS///
                else
		{
			args.clear();
			while(i<cmd.length())
			{
				place=cmd.find(',',i);
				if(place>0)
				{
					args.push_back(get_string(cmd,i,',')); 
					i++; 
				}
				else
				{
					args.push_back(get_string(cmd,i,')'));
					break;
				}
			}

		}
                
		///CONSOLE_PRINT///
		if(body=="CF")
                {
			strcpy(tmp,args[0].c_str());
			///CHECKING_FILE///
			myfile.open(tmp);
			if(myfile.is_open())
				cout<<tmp<<" Got it."<<endl;
			else
				cout<<"FILE ERROR"<<endl;
			myfile.close();
		}
		if(body=="PC"||body=="PCN"||body=="PF"||body=="PFN")
                {	///ALL///cout<<"err5"<<endl;
                    //cout<<"err6"<<endl;

                    //-----------------------------------
                    if(args[0]=="A")
                        {
                       // cout<<"err7"<<endl;
				if(body=="PC"||body=="PCN")
                                  {
                                    //cout<<"err1"<<endl;
                                    cout<<cPrinter(columns);}
				else
                                {//cout<<"err2"<<endl;
					myfile.open(tmp);
					myfile<<cPrinter(columns);
					myfile.close();
				}

			}
			///SOME///
			else

                            //----------------------------------------------------------------------------------------

                            if(body=="PC"||body=="PF")
                                {//cout<<"err8"<<endl;//drop here!
					for(int j=0; j<args.size(); j++)
                            {//cout<<"err10"<<endl;
                                            if(cGetByN(args[j]).type!=(-1))//DROP HERE!!!!  err0 not printed... but why? it's just like while(1) 0_0... because of cGetByn
                                            {//cout<<"err0"<<endl;
											C.push_back(cGetByN(args[j]));}}
					if(body=="PC")
						cout<<cPrinter(C);
					else
					{
						myfile.open(tmp);
						myfile<<cPrinter(C);
						myfile.close();
					}
					C.clear();
				}
				else
                                {//cout<<"err9"<<endl;
					for(int j=0; j<args.size(); j++)
						if(str_to_int(args[j],0)<columns.size())//no fail
							C.push_back(columns[str_to_int(args[j],0)]);
					if(body=="PCN")
						cout<<cPrinter(C);
					else
					{
						myfile.open(tmp);
						myfile<<cPrinter(C);
						myfile.close();
					}
					C.clear();
				}
                            }
            }
}








};






int main()
{

       setlocale( LC_ALL, "" );
       bindtextdomain( "parser", "/usr/share/locale" );
       textdomain( "parser" );



	char * tmp="Example.txt";
	col parser(tmp);
		
	parser.Menu();


		/*
		
////<<"\n\n\n\n";//
		cout<<endl<<"here:!";
for(int y=0;y<parser.counter;y++)
{
	cout<<' '<<parser.columns[y].name;
}

*/
/*
for(int y=0;y<parser.columns.size();y++)
{
	switch(parser.columns[y].type)
	{
	case 0:{for(int h=0;h<2;h++)cout<<parser.columns[y].val0[h]<<" from "<<parser.columns[y].name<<endl;break;}
	case 1:{for(int h=0;h<2;h++)cout<<parser.columns[y].val1[h]<<" from "<<parser.columns[y].name<<endl;break;}
	case 2:{for(int h=0;h<2;h++)cout<<parser.columns[y].val2[h]<<" from "<<parser.columns[y].name<<endl;break;}
	
	}
}
*/


  // main code:
  
/*
*/


/*
output:

 ofstream myfile;
 myfile.open ("example.txt");
 myfile << "Writing this to a file.\n";
 myfile.close();

*/

	/*
cout<<"Enter the filename:"<<endl;
char * filename=new char[100];
cin>>filename;
col parser(filename);
parser.Menu();
*/





return 0;
}