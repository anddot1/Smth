#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
//#include <vector.h>
using namespace std;



		int char_to_int(char a)
        {	return a - '0';
        }
		int str_to_int(string b, int &w)
		{
			int k=0;
			while(!isspace(b[w])||b[w]!='\n')
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
            } w++; double flag = 1;
            while (isdigit(b[w]))
            {
                t = t + flag * char_to_int(b[w]);
                w++;
            }
            return t;
            //до : и комментить!
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
	int n;//column's number
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




	col()
	{
	node temp;
    string line;
	bool flag=false;
	ifstream myfile ("example.txt");
  int c=0;//column's counter
  //columns=new vector<node>();
  
  if (myfile.is_open())
  {
	  while ( myfile.good() )
    {
     getline (myfile,line);
		//myfile>> line;
	 cout << line << endl;
	 if(!flag){
	 for(int i=0;i<line.length();i++)
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
		
	 }flag=true;}
	counter=c;
	//////////////////////////////////////////////////////////////////////////
	{
	int i=0;c=0;
	getline (myfile,line);
		//myfile>> line;
	cout << line << endl;

	
	while(i<line.length())
	{i=wait_for_digit(line,i);
		switch(columns[c].type)
		{
		case 0:
			{
				columns[c].val0.push_back(str_to_int(line,i));
				break;
			}
		
		case 1:
			{	columns[c].val0.push_back(str_to_int(line,i));
				break;
			}
			
		case 2:
			{	columns[c].val2.push_back(string_to_double(line,i));
				break;
			}
	}}
	
	
	
	}
	 
/*next code*/



    }
    myfile.close();
  }

  else cout << "Unable to open file"; 
			
	}

};






int main()
{

/*
input:
*/

	col parser;
string tmp="example.txt";



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
return 0;
}