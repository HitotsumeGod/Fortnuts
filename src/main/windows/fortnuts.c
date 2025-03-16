#include <stdio.h>
#include <stdlib.h>
#include <curl.h>
#include <windows.h>

int main(void) {
	
	FILE * curlf;
	CURL *c_handle;
	CURLcode errcode;
	char buf[CURL_ERROR_SIZE];
	if ((curlf = fopen("curlf.txt", "w")) == NULL) {
		perror("fopen err");
		exit(EXIT_FAILURE);
	}
	if (curl_global_init(CURL_GLOBAL_WIN32) != 0) {
		perror("global_init issue");
		exit(EXIT_FAILURE);
	}
	if ((c_handle = curl_easy_init()) == NULL) {
		perror("curl init issue");
		exit(EXIT_FAILURE);
	}
	if (curl_easy_setopt(c_handle, CURLOPT_URL, "https://ipecho.net/plain") != CURLE_OK) {
		perror("curl setop err");
       	    	exit(EXIT_FAILURE);
	}
	if (curl_easy_setopt(c_handle, CURLOPT_WRITEDATA, curlf) != CURLE_OK) {
		perror("curl setop err");
		exit(EXIT_FAILURE);
	}
	if (curl_easy_setopt(c_handle, CURLOPT_ERRORBUFFER, buf) != CURLE_OK) {
		perror("curl setop err");
		exit(EXIT_FAILURE);
	}
	if ((errcode = curl_easy_perform(c_handle)) != CURLE_OK) {
		printf("%s\n", buf);
		exit(EXIT_FAILURE);
	}
	curl_easy_cleanup(c_handle);
	curl_global_cleanup();
	return 0;

}
