/*
Muhammad Ahmad Rana
*/

#include "pugixml.hpp"  //For xml parcing
#include "lexertk.hpp"  //For tokenization

#include <iostream>
#include <stdlib.h>
#include <stdio.h>      // printf, fgets 
#include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;
using namespace pugi;
using namespace lexertk;

map<int, string> find_function(string, map<string, map<string, int>>);  //Seaching function prototype

int main()
{
	xml_document doc;                 //Creating document object 
	doc.load_file("wikiii.xml");       //Loading xml file and creating a tree

	string id;                        //Retriving Page id from the tree
	string title;
	string expression = { NULL };     //Retriving text from each page

	map<string, map<string, int>> map1;
	map<string, int> map_data;        //For storing frequency coresponding to words

	xml_node node1 = doc.child("mediawiki");   //Object pointer node pointing to parrent
	for (xml_node tool = node1.child("page"); tool; tool = tool.next_sibling()) //Traversing the pages ie crawling
	{
		id = tool.child("id").child_value();   //Storing id to identify each page
		title = tool.child("title").child_value();

		expression = expression + title;       //Apending title in text

		expression = tool.child("revision").child("text").child_value();

		generator generator, titleToken;        //title token is for storing tokens of title
		generator.process(expression);         //Sending the expression from each page to tokenize ie breaking

		int a = 0;
		int flag = 0;                          //Used in page rank

		for (int i = 0; i < generator.size(); ++i)
		{
			token t = generator[i];
			map<string, int>::iterator it;

			titleToken.process(title);          //Tokenizing the title

			if (t.value.size() > 2 && t.value.size() < 20)
			{
				it = map_data.find(t.value.c_str());

				token t1 = titleToken[0];
				token t2 = titleToken[1];

				if (flag == 0 && (t.value.c_str() == title))  //Finding weather the word is in title
				{
					map_data.insert(pair<string, int>(t.value.c_str(), 15));
					flag = 1;
				}
				else
				if (it != map_data.end())                   //Finding frequency of words
				{
					a = it->second;
					a++;
					it->second = a;
				}
				else
				{
					map_data.insert(pair<string, int>(t.value.c_str(), 1));
				}
			}
			flag = 0;
		}

		map1.insert(pair<string, map<string, int>>(id, map_data));

		map_data.clear();
	}

	//vector<string> words;       //Breaks our searched string into words
	string search,words;

	while (1)
	{

		cout << "-----------------------------" << endl;
		cout << "Welcome to UDFA Search Engine" << endl;
		cout << "-----------------------------" << endl;

		cout << "Please Search : ";

		generator tokenizer;
		getline(cin, search);

		/*tokenizer.process(search);

		for (int i = 0; i < tokenizer.size(); ++i)
		{
			token tk = tokenizer[i];
			words.push_back(tk.value.c_str());
		}*/

		map<int, string> result;
		result = find_function(search, map1);      //Sending the Queery word and map to find Inverted indexer

		map<int, string>::reverse_iterator itr;
		for (itr = result.rbegin(); itr != result.rend(); itr++)
		{
			cout << "Found in Page  :" << itr->second << endl;
		}
		cout << "-----------------------------------------" << endl;
		cout << "Enter the id of the page you want to open" << endl;
		cout << "-----------------------------------------" << endl;

		string temp;
		cin >> temp;

		for (itr = result.rbegin(); itr != result.rend(); itr++)
		{
			if (temp == itr->second)
			{
				for (xml_node tool = node1.child("page"); tool; tool = tool.next_sibling()) //Traversing the pages ie crawling
				{
					if (tool.child("id").child_value() == temp)
					{
						cout << endl;
						cout << "The title of page is" << endl;
						cout << tool.child("title").child_value() << endl << endl;

						cout << tool.child("revision").child("text").child_value() << endl;

						getchar();
						break;
					}
				}
			}
		}

		getchar();
		words.empty();
		system("CLS");

	}
	return 0;

}
map<int, string> find_function(string str, map<string, map<string, int>> data)
{
	map<string, int>::iterator find, f2, f3, f4;    /*finding iterator*/
	map<int, string> result;
	map<string, map<string, int>>::iterator itr1;
	map<string, int>::iterator itr2;
	string test;
	test = str;

	for (itr1 = data.begin(); itr1 != data.end(); itr1++)
	{
		if (isupper(test[0]))                //Finding word in second map
		{
			find = itr1->second.find(test);

			if (find != itr1->second.end())
			{
				result.insert(pair<int, string>(find->second, itr1->first));
			}

			test[0] = tolower(test[0]);

			f2 = itr1->second.find(test);

			if (f2 != itr1->second.end())
			{
				result.insert(pair<int, string>(f2->second, itr1->first));
			}
		}
		else
		if (islower(test[0]))
		{
			f3 = itr1->second.find(test);

			if (f3 != itr1->second.end())
			{
				result.insert(pair<int, string>(f3->second, itr1->first));
			}

			test[0] = toupper(test[0]);

			f4 = itr1->second.find(test);

			if (f4 != itr1->second.end())
			{
				result.insert(pair<int, string>(f4->second, itr1->first));
			}


		}
	}

	return result;
}
