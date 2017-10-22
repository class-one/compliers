#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <fstream>
#include <list>
#define max 100
using namespace std;
static map<string, int> dictionary;
void init()
{
    dictionary.insert(map<string, int>::value_type("for",1));
    dictionary.insert(map<string, int>::value_type("if",2));
    dictionary.insert(map<string, int>::value_type("then",3));
    dictionary.insert(map<string, int>::value_type("else",4));
    dictionary.insert(map<string, int>::value_type("while",5));
    dictionary.insert(map<string, int>::value_type("do",6));
    dictionary.insert(map<string, int>::value_type("var",10));
    dictionary.insert(map<string, int>::value_type("num",11));
    dictionary.insert(map<string, int>::value_type("+",13));
    dictionary.insert(map<string, int>::value_type("-",14));
    dictionary.insert(map<string, int>::value_type("*",15));
    dictionary.insert(map<string, int>::value_type("/",16));
    dictionary.insert(map<string, int>::value_type(":",17));
    dictionary.insert(map<string, int>::value_type(":=",18));
    dictionary.insert(map<string, int>::value_type("<",19));
    dictionary.insert(map<string, int>::value_type("<>",21));
    dictionary.insert(map<string, int>::value_type("<=",22));
    dictionary.insert(map<string, int>::value_type(">",23));
    dictionary.insert(map<string, int>::value_type(">=",24));
    dictionary.insert(map<string, int>::value_type("=",25));
    dictionary.insert(map<string, int>::value_type(";",26));
    dictionary.insert(map<string, int>::value_type("(",27));
    dictionary.insert(map<string, int>::value_type(")",28));
    dictionary.insert(map<string, int>::value_type("until",29));
    dictionary.insert(map<string, int>::value_type("int",30));
    dictionary.insert(map<string, int>::value_type("input",31));
    dictionary.insert(map<string, int>::value_type("output",32));
    dictionary.insert(map<string, int>::value_type("#",0));

}
int findbykey(string key)
{
   map<string, int >::iterator l_it;
   l_it=dictionary.find(key);
   if(l_it==dictionary.end())
             return -1;
   else
    return l_it->second;
}

string keyword[10]={"for","if","then","else","while","do","int","until","input","output"};

bool isletter(char a)
{
    if((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isdigit(char a)
{
    if(a >= '0' && a <= '9')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool iskeyw(string keywords)
{
    for(int i = 0; i < 10; i++)
    {
        if(keyword[i] == keywords)
        {
            return true;
        }

    }
        return false;
}

bool isvar(string var)    //ID=letter(letter | digit)*
{
       if(isletter(var[0]))
       {
           for(int i = 0; i < var.length(); i++)
           {
               if(isletter(var[i]) || isdigit(var[i]))
               {

               }
               else
               {
                   return false;
               }
           }
           return true;
       }
       else
       {
           return false;
       }
}

bool isnum(string num)     //NUM=digit digit*   (xiaoshudian
{
    if(isdigit(num[0]))
       {
           int flag1 = 1;
           int flag2 = 1;
           int flag3 = 1;
           for(int i = 0; i < num.length(); i++)
           {
               if(isdigit(num[i]))
               {

               }
               else if(num[i] == '.' && isdigit(num[i+1]) && flag1)
               {
                  flag1 = 0;
               }
               else if (((num[i] == 'E' || num[i] == 'e') &&
                (num[i+1] == '+' || num[i+1] == '-' || isdigit(num[i+1])) && flag2))
               {
                //  cout << num[i] << "dddd" << endl;
                  flag2 = 0;
               }
               else if((num[i] == '+' || num[i] == '-') && isdigit(num[i+1]))
               {

               }
               else if(num[i] == '/' && isdigit(num[i+1]) && flag3)
               {
                  flag3 = 0;
               }
               else
               {
                   return false;
               }
           }
           return true;
       }
       else
       {
           return false;
       }
}

string to_String(int n)
{
    string temp;
    stringstream ss;
    ss << n;
    temp = ss.str();

    return temp;
}

string packet(string test, int type)
{
      int a;
      if(type == 0)
      {
        a = findbykey(test);
      }
      else if(type == 1)
      {
        a = findbykey("var");
      }
      else if(type == 2)
      {
        a = findbykey("num");
      }

       string req = "";
       string aa;
       aa = to_String(a);
       req += "(" + aa;
       req += ",";
       req += test;
       req += ") ";
       return req;
}

string texthandle(string test, int linenum)
{
     if(iskeyw(test))
     {
          return packet(test, 0);
     }
     else if(isvar(test))
     {
         return packet(test, 1);
     }
     else if(isnum(test))
     {
         return packet(test, 2);
     }
     else if(-1 == findbykey(test))
     {
           string b = "There are some errors in";
           string bb;
           bb = to_String(linenum);
           b += bb;
           return  b;
     }
     else
     {

         return packet(test, 0);
     }
}

void File_output(string filename)
{
     int linenum = 0;
     string test;
     fstream file;
     string pice;
    string expression = "";
     list<string> words;
     file.open(filename, ios_base::in | ios_base::out) ;
     if(!file)
     {
         cout << "error" << endl;
     }
     else
     {
        while(getline(file, test))
        {
              linenum++;
              //处理逻辑
           /*
              划分单词，. 标点

           */
            string temp = "";
           for(int i = 0; i < test.length(); i++)
           {


               if( test[i] == ' ' )
               {

               }
               else
               {
                    temp += test[i];
                    if(test[i+1] == ' ' || test[i+1] == '\0')
                    {
                        words.push_back(temp);
                        pice = texthandle(temp,linenum);
                        expression += "\n";
                        expression += pice;
                        temp = "";
                    }
               }

           }
         }
          //对单词链表进行处理

        //  list<string>::iterator i;
        //   for (i = words.begin(); i != words.end(); ++i)
        //         // 测试
        //       cout<<*i<<endl;
         cout << expression << endl;
     }



}

int main()
{
    init();
    File_output("a.txt");
   // int b =findbykey("for");
   //  cout<<b<<endl;
    return 0;
}