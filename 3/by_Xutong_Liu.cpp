#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <ctype.h>
#include <cctype>
using namespace std;

typedef pair<string,string> row;

vector<row> detach(vector<string> input,int n)
{
    vector<row> res;
    for(int i=0;i<n;i++)
    {
        row dep;
        size_t found=input[i].find("��");
        cout<<found<<endl;
        if(found!=string::npos)
        {
            dep.first.push_back(input[i][0]);
            if(found==2)
            {
                dep.first.push_back(input[i][1]);
            }
            dep.second=input[i].substr(found+2);
            res.push_back(dep);
        }
    }
    for(int i=0;i<n;i++)
    {
        cout<<res[i].first<<" "<<res[i].second<<endl;
    }
    return res;
}


vector<row> repl(vector<row> res,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            size_t found = res[j].second.find(res[i].first);
            while(found!=string::npos)
            {
                char c[2];
                c[0]=i+48;
                c[1]='\0';
                //cout<<"res[i].first.size()"<<res[i].first.size()<<endl;
                //cout<<" c= "<<c<<endl;
                res[j].second.replace(found,res[i].first.size(),c);
                found = res[j].second.find(res[i].first);
            }

        }
    }
    for(int i=0;i<n;i++)
    {
        cout<<res[i].first<<" "<<res[i].second<<endl;
    }
    return res;
}



void solve(vector<row> res,int n)
{
    vector<row> sol;
    for(int i=0;i<n;i++)
    {
        row comb;
        comb.first=res[i].first;
        comb.second="";
        sol.push_back(comb);
    }

    int counter=0;
    while(counter<4)
 {

    for(int i=0;i<n;i++)
    {

        if(!isdigit(res[i].second[0]))  //�ѷ����ּӽ�first��
           {
               //cout<<"�������ֿ�ͷ"<<endl;
               if(sol[i].second.find(res[i].second[0])==string::npos)
               {
                    sol[i].second.push_back(res[i].second[0]);
               }

           }
           //�ұ��ʽ�Ҳ���û�пմ�
        size_t found=res[i].second.find("~");
        if(found!=string::npos)
            {
                cout<<"1"<<endl;
                sol[i].second.push_back('~');
            }

        if(isdigit(res[i].second[0])) //��ͷ�Ƿ��ս���Ļ�
        {


            int bro = res[i].second[0]-48;
            for(int j=0;j<sol[bro].second.size();j++)
            {
                if(sol[i].second.find(sol[bro].second[j])==string::npos)
                {
                    sol[i].second.push_back(sol[bro].second[j]);
                }
            }
        }
        //�ұ��ʽ�Ҳ���û�л��������| ����У��Ͱ�|������ս��Ҳ���뵽first��
        found = res[i].second.find('|');
        if(found!=string::npos)
        {
             if(found+1<res[i].second.size()&&!isdigit(res[i].second[found+1]))  //found+1�Ǹ�λ����һ���ս���Ļ�
             {
               if(sol[i].second.find(res[i].second[found+1])==string::npos)
               {
                    sol[i].second.push_back(res[i].second[found+1]);

               }

             }
             if(found+1<res[i].second.size()&&isdigit(res[i].second[found+1]))
             {
                 int bro = res[i].second[found+1]-48;
                 for(int j=0;j<sol[bro].second.size();j++)
                 {

                    if(sol[i].second.find(sol[bro].second[j])==string::npos)
                    {
                        sol[i].second.push_back(sol[bro].second[j]);
                    }
                 }
            }
            res[i].second[found]='z';
        }
    }
    counter++;
 }
    for(int i=0;i<n;i++)
    {
        cout<<sol[i].first<<" ��first��: "<<sol[i].second<<endl;
    }
}



int main()
{

    vector<string> input;
    int n;//�ķ�������
    cout<<"�����ķ�������"<<endl;
    cin>>n;
    for(int i=0;i<n;i++) //��ʼ���ķ�
    {
        string s;
        cin>>s;
        input.push_back(s);
    }

    vector<row> res = repl(detach(input,n),n);
    solve(res,n);

}
