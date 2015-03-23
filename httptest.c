#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
//#include <curl/types.h>
#include <curl/easy.h>

// Define our struct for accepting LCs output
struct BufferStruct
{
char * buffer;
size_t size;
};

// This is the function we pass to LC, which writes the output to a BufferStruct
static size_t WriteMemoryCallback
(void *ptr, size_t size, size_t nmemb, void *data)
{
size_t realsize = size * nmemb;

struct BufferStruct * mem = (struct BufferStruct *) data;

mem->buffer = realloc(mem->buffer, mem->size + realsize + 1);

if ( mem->buffer )
{
memcpy( &( mem->buffer[ mem->size ] ), ptr, realsize );
mem->size += realsize;
mem->buffer[ mem->size ] = 0;
}
return realsize;
}


int main()
{

curl_global_init( CURL_GLOBAL_ALL );
CURL * myHandle;
CURLcode result; // We’ll store the result of CURL’s webpage retrieval, for simple error checking.
struct BufferStruct output; // Create an instance of out BufferStruct to accept LCs output
output.buffer = NULL;
output.size = 0;
myHandle = curl_easy_init ( ) ;

/* Notice the lack of major error checking, for brevity */

curl_easy_setopt(myHandle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback); // Passing the function pointer to LC
curl_easy_setopt(myHandle, CURLOPT_WRITEDATA, (void *)&output); // Passing our BufferStruct to LC
curl_easy_setopt(myHandle, CURLOPT_URL, "https://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20yahoo.finance.quote%20where%20symbol%20in%20(%22GOOG%22)&format=json&diagnostics=true&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys&callback=");
result = curl_easy_perform( myHandle );
curl_easy_cleanup( myHandle );


printf( output.buffer );


if( output.buffer )
{
free ( output.buffer );
output.buffer = 0;
output.size = 0;
}

//printf("LibCurl rules!\n");
return 0;
}

