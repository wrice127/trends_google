// MycURL.hpp written by Jae Hyuk Kwak
class MySList
{
	struct curl_slist *list_ = nullptr;
public:
	void append( const char *v )
	{
		list_ = curl_slist_append( list_, v );
	}
	void clear()
	{
		if ( list_ ) curl_slist_free_all( list_ );
		list_ = nullptr;
	}
	struct curl_slist *native() { return list_; }
	~MySList() // could be nicer with unique_ptr but...
	{
		if ( list_ ) curl_slist_free_all( list_ );
	}
};

class MycURL
{
	unique_ptr< CURL, decltype( curl_easy_cleanup )* > curl_;
public:
	MycURL() : curl_( curl_easy_init(), curl_easy_cleanup )
	{
		if ( nullptr == curl_ )
			throw runtime_error( "curl_easy_init() failed." );
	}
	CURL *native() { return curl_.get(); }
	MySList httpheader;
};

template< typename ParamType >
void SetOpt_( MycURL &mycURL, CURLoption option, const ParamType &param )
{
	CURLcode res = curl_easy_setopt( mycURL.native(), option, param );
	if ( CURLE_OK != res )
		throw runtime_error( string( "curl_easy_setopt() failed." )
		+ curl_easy_strerror( res ) );
}

void SetOpt_URL( MycURL &mycURL, const string &url )
{
	SetOpt_( mycURL, CURLOPT_URL, url.c_str() );
}

void SetOpt_VERBOSE( MycURL &mycURL, int val )
{
	SetOpt_( mycURL, CURLOPT_VERBOSE, val );
}

size_t WriteMemoryCallback_( void *contents, size_t size, size_t numberOfMemoryBlocks, void *userChunk )
{
	const size_t realSize = size * numberOfMemoryBlocks;
	string &html = *static_cast< string * >( userChunk );
	html += string( static_cast< char * >( contents ), realSize );
	return realSize;
}

string Request( MycURL &mycURL )
{
	string html;
	SetOpt_( mycURL, CURLOPT_HTTPHEADER, mycURL.httpheader.native() );
	SetOpt_( mycURL, CURLOPT_WRITEDATA, static_cast< void * >( &html ) );
	SetOpt_( mycURL, CURLOPT_WRITEFUNCTION, WriteMemoryCallback_ );
	const CURLcode res = curl_easy_perform( mycURL.native() );
	if ( CURLE_OK != res )
		throw runtime_error( string( "RequestGet() failed: " ) +
		+ curl_easy_strerror( res ) );
	return html;
}

string RequestGet( MycURL &mycURL )
{
	SetOpt_( mycURL, CURLOPT_POST, 0 );
	return Request( mycURL );
}

string RequestPost( MycURL &mycURL, const string &postfields )
{
	SetOpt_( mycURL, CURLOPT_POST, 1 );
	SetOpt_( mycURL, CURLOPT_POSTFIELDS, postfields.c_str() );
	SetOpt_( mycURL, CURLOPT_POSTFIELDSIZE, postfields.size() );
	return Request( mycURL );
}

