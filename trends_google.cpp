// trends_google.cpp written by Jae Hyuk Kwak
#include "stdafx.h"
#include "config.hpp"
#include "MycURL.hpp"

int main( int argn, const char *argv[] )
{
	curl_global_init( CURL_GLOBAL_ALL ); // required once

	MycURL curl;
	SetOpt_URL( curl, url );
	string rss = RequestGet( curl );

	const string titleBegin = "<title>";
	const string titleEnd = "</title>";
	size_t lastPos = 0;
	while ( true ) {
		const size_t posBegin = rss.find( titleBegin, lastPos );
		const size_t posEnd = rss.find( titleEnd, lastPos );
		if ( posBegin == string::npos || posEnd == string::npos ) break;
		lastPos = posEnd + titleEnd.size();

		const size_t posBeginInner = posBegin + titleBegin.size();
		string title = rss.substr( posBeginInner, posEnd - posBeginInner );
		cout << title << endl;
	}
	return 0;
}
