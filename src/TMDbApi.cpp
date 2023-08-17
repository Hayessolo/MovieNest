#include <iostream>
#include <curl/curl.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total_size = size * nmemb;
    static_cast<std::string *>(userp)->append(static_cast<char *>(contents), total_size);
    return total_size;
}

int main() {
    CURL *curl;
    CURLcode res;
    std::string response;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set API URL
        const char *url = "https://api.themoviedb.org/3/movie/550?api_key="0a8742106d5a1604338b5ba7a774dd62Y"";

        // Set libcurl options
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    // Cleanup libcurl
    curl_global_cleanup();

    // Print the API response
    std::cout << "API Response:" << std::endl;
    std::cout << response << std::endl;

    return 0;
}
