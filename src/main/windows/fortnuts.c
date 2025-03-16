#include <stdio.h>
#include <stdlib.h>
#include <curl.h>
#include <windows.h>

int main(void) {

	FILE *of;	
	CURL *c_handle;
	CURLcode errcode;
	char buf[CURL_ERROR_SIZE], fname[20], **args;
	if ((args = malloc(sizeof (char *) * 3)) == NULL) {
		perror("malloc err");
		exit(EXIT_FAILURE);
	}
	*args = "ftp://ftp.gamers.org/pub/idgames/levels/doom/a-c/acastle2.zip";
	*(args + 1) = "ftp://ftp.gamers.org/pub/idgames/levels/doom/a-c/adamwad.zip";
	*(args + 2) = "ftp://ftp.gamers.org/pub/idgames/levels/doom/a-c/andrew.zip";
	if (curl_global_init(CURL_GLOBAL_WIN32) != 0) {
		perror("global_init issue");
		exit(EXIT_FAILURE);
	}
	if ((c_handle = curl_easy_init()) == NULL) {
		perror("curl init issue");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < 3; i++) {
		if (snprintf(fname, sizeof fname, "%s%d%s", "output", i, ".zip") == -1) {
			perror("string formatting err");
			exit(EXIT_FAILURE);
		}
		if ((of = fopen(fname, "wb")) == NULL) {
			perror("fopen err");
			exit(EXIT_FAILURE);
		}
		if (curl_easy_setopt(c_handle, CURLOPT_TRANSFERTEXT, 0) != CURLE_OK) {
			perror("curl setop err");
			exit(EXIT_FAILURE);
		}
		if (curl_easy_setopt(c_handle, CURLOPT_WRITEDATA, of) != CURLE_OK) {
			perror("curl setop err");
			exit(EXIT_FAILURE);
		}
		if (curl_easy_setopt(c_handle, CURLOPT_ERRORBUFFER, buf) != CURLE_OK) {
			perror("curl setop err");
			exit(EXIT_FAILURE);
		}	
		if (curl_easy_setopt(c_handle, CURLOPT_URL, *(args + i)) != CURLE_OK) {
			perror("curl setop err");
       	    		exit(EXIT_FAILURE);
		}
		if ((errcode = curl_easy_perform(c_handle)) != CURLE_OK) {
			printf("%s\n", buf);
			exit(EXIT_FAILURE);
		}
		if (fclose(of) == -1) {
			perror("fclose err");
			exit(EXIT_FAILURE);
		}
	}
	free(args);
	curl_easy_cleanup(c_handle);
	curl_global_cleanup();
	return 0;

}
