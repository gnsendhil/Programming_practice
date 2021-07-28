//LAPIN

#include <iostream>
#include <map>
#include <cstring>
#include <string>
using namespace std;


void insert_to_map(char c, map<char, int> &dict)
{
    if(dict.find(c) == dict.end())
    {
        dict[c] = 1;
    }
    else
    {
        dict[c] = dict[c] + 1;
    }
}

bool is_lapindrome(string s)
{
    map<char, int> s1_dict;
	map<char, int> s2_dict;
	
	int incrementer = 0;
	if (s.length() % 2 == 1)
	{
	    incrementer = s.length()/2 + 1;
	}
	else
	{
	    incrementer = s.length()/2;
	}
	
	for(int i=0; i<s.length()/2; i++)
	{
	    insert_to_map(s[i], s1_dict);
	    insert_to_map(s[i+incrementer], s2_dict);
	}
	
    map<char, int>::iterator itr;

/*     for(itr = s1_dict.begin(); itr!= s1_dict.end(); ++itr)
    {
        cout<<itr->first<<"-->";
        cout<<itr->second<<endl;
    }

    for(itr = s2_dict.begin(); itr!= s2_dict.end(); ++itr)
    {
        cout<<itr->first<<"-->";
        cout<<itr->second<<endl;
    }
 */	
    for(itr = s1_dict.begin(); itr!= s1_dict.end(); ++itr)
    {
        if(s2_dict.find(itr->first) == s2_dict.end())
        {
            //cout<<"false";
            return false;
        }
        if(s2_dict[itr->first] != s1_dict[itr->first])
        {
            //cout<<"false";
            return false;
        }
    }
    //cout<<"true";
    return true;
}

int main() {
	// your code goes here

    string s;
	
	int T;
    cin>>T;
    //getline(cin, s);
	cin.ignore();
    for(int i=0; i<T; i++ )
    {
        //cout<<"enter the string";
        getline(cin, s);
        if(is_lapindrome(s))
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }	
	return 0;
}
