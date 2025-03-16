#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int main(void) {
	
	FILE *zipf;
	CURL *c_handle;
	if ((zipf = fopen("output.zip", "w")) == NULL) {
		perror("fopen err");
		exit(EXIT_FAILURE);
	}
	if (curl_global_init(CURL_GLOBAL_NOTHING) != 0) {
		perror("global_init issue");
		exit(EXIT_FAILURE);
	}
	if ((c_handle = curl_easy_init()) == NULL) {
		perror("curl init issue");
		exit(EXIT_FAILURE);
	}
	if (curl_easy_setopt(c_handle, CURLOPT_URL, "https://youfailit.net/pub/idgames/levels/doom/v-z/vega_1.zip") != CURLE_OK) {
		perror("curl setop err");
       	    	exit(EXIT_FAILURE);
	}
	if (curl_easy_setopt(c_handle, CURLOPT_WRITEDATA, zipf) != CURLE_OK) {
		perror("curl setop err");
		exit(EXIT_FAILURE);
	}
	if (curl_easy_perform(c_handle) != CURLE_OK) {
		perror("curl perform err");
		exit(EXIT_FAILURE);
	}
	curl_easy_cleanup(c_handle);
	curl_global_cleanup();
	if (fclose(zipf) == -1) {
		perror("fclose err");
		exit(EXIT_FAILURE);
	}
	return 0;

}
