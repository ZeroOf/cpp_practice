#ifndef __RSSREADER_H__
#define __RSSREADER_H__
#include "tinyxml2.h"
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <regex>
#include <iostream>

using namespace tinyxml2;
using std::string;
using std::vector;
using std::ofstream;
using std::stringstream;
using std::regex;
using std::cout;
using std::endl;

struct RssItem
{
	string title;
	string link;
	string content;
};

class RssReader
{
public:
	void parseRss(const vector<string> & filenames)
	{
		XMLDocument doc;
		for(auto file: filenames){
			doc.LoadFile(file.c_str());
			if(doc.ErrorID()){
				doc.PrintError();
				continue;
			}

			RssItem tmp;
			XMLElement *rss, *channel, *item, *title, *link, *content;
			rss = doc.FirstChildElement("rss");
			//channel = (rss ? rss->FirstChildElement("channel") : NULL);
			if(rss){
				channel = rss->FirstChildElement("channel");
			}else{
				channel = NULL;
			}
			if(channel)
				for(item = channel->FirstChildElement("item"); item ; item = item -> NextSiblingElement("item"))
				{
					title = item -> FirstChildElement("title");
					link = item -> FirstChildElement("link");
					content = item -> FirstChildElement("content:encoded");

					if(link)
						tmp.link =link -> GetText();
					if(content)
						tmp.content = content -> GetText();
					else continue;
					if(title)
						tmp.title = title -> GetText();
					else if(content){
						stringstream ss(tmp.content) ;
						getline(ss,tmp.title);
					}
					_rss.push_back(tmp);
				}
		}
		cout << "parseRss" << endl;
		return;
	}

	void dump(vector<string> & vecfile)
	{
		stringstream ss;
		regex rep("<.+?>");
		string tmp;
		cout << _rss.size() << endl;
		for(size_t i = 0; i < _rss.size(); i++)
		{
			ss	<< "<doc>" << endl
				<< "\t<docid>" << i + 1 << "</docid>" << endl
				<< "\t<title>" << _rss[i].title << "</title>" << endl
				<< "\t<link>" << _rss[i].link << "</link>" << endl
				<< "\t<content>" << regex_replace(_rss[i].content,rep,string("")) << "</content>" << endl
				<< "</doc>" << endl;
			tmp = ss.str();
			ss.str("");
			vecfile.push_back(tmp);
		}
	}
private:
		vector<RssItem> _rss;
};
#endif
