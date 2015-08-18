#include <map>
#include <list>
#include <iostream>
#include <stdlib.h>

using namespace std;

int search(int& begin, map<int, list<int> >& match_list)
{
    cout<<"==search =="<<begin<<endl;

    int ret = 0;
    auto it = match_list.lower_bound(begin);
    if(it != match_list.end())
    {
        cout<<"find iterator lower_bound("<<begin<<"), it->first:"<<it->first<<endl;
        begin = it->first;
        ret = it->second.front();
        it->second.pop_front();
        cout<<"pop "<< ret<<" from ["<<it->first<<"]"<<endl;
        if(it->second.empty())
        {
            cout<<"["<<it->first<<"] is empty, remove it"<<endl;
            match_list.erase(it);
        }
    }
    else if(it != match_list.begin())
    {
        //--it;
        //cout<<"find iterator while --it, ("<<begin<<"), it->first:"<<it->first<<" update begin:"<<begin<<endl;
        //begin = it->first;
        //ret = it->second.front();
        //it->second.pop_front();
        //cout<<"pop "<< ret<<" from ["<<it->first<<"]"<<endl;
        //if(it->second.empty())
        //{
            //cout<<"["<<it->first<<"] is empty, remove it"<<endl;
            //match_list.erase(it);
        //}

        cout<<"reset begin:"<<0<<endl;
        begin = 0;
        ret = 0;
    }
    else
    {
        cout<<"match list is empty"<<endl;
        ret = -2;
    }
    return ret;
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cout<<"Usage: "<<argv[0]<<" score"<<endl;
        return -1;
    }

    map<int, list<int> > match_list;
    match_list[1000].push_back(1);
    match_list[998].push_back(2);
    match_list[998].push_back(5);
    match_list[900].push_back(3);
    match_list[1050].push_back(4);

    int search_begin = atoi(argv[1]);

    int ret = 0;
    do
    {
        ret = search(search_begin, match_list);
        if(ret > 0)
        {
            cout<<"search begin:"<< search_begin<<" result: "<< ret<<endl;
        }
    }while(ret >= 0);

     
    return 0;
}
