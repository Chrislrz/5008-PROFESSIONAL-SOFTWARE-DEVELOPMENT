// If I take the data of the web page to the local (such as the txt file saved as a local), and then the local access query this txt document, so as to complete the job. However, I assume that the document of this web page is very large, so maybe copying the web page to the local is not an effective method. So this time I want to access the query data by directly visiting the web page.

//If the code here is too tedious, you can directly look at the 1a (2) solution, which uses the download to the local processing method.

#include <iostream>
#include <string>
#include <curl/curl.h> // This line introduces the libcurl library header file. libcurl is a library for client URL transfer that supports many protocols, such as HTTP and HTTPS. In the program, it is used to get web content from the web.
#include <sstream> // Include this header

// The callback function WriteCallback, which is used as a write callback function in the libcurl library. When libcurl receives data from a network request, it calls this function to process the received data. What this function does is append the received data to an std::string object, which in this case is used to store the contents of the entire web page.

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}// All parameters are necessary because libcurl expects the function to have a specific list of arguments.

int main() {

    // Initialize CURL for fetching the webpage
    CURL *curl = curl_easy_init();
    std::string readBuffer;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://adventofcode.com/2023/day/1/input");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);// This line sets up a callback function, WriteCallback, which will be called when libcurl receives data. This function appends the received data to the readBuffer
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        // Set cookie
        // Because the official website of adventofcode requires my password and account to access, I link to my account and open the document 1a, where I can find the header option under the network label to view my cookies, so as to access the data of this assignment.
        curl_easy_setopt(curl, CURLOPT_COOKIE, "session=53616c7465645f5f37a538ec9321da88931d650471dd3bddcc4eb378c15523014f3fbcbca4327c441d73557b1b0ad38f961e45c2ebba3e192f2137af5c581bf4; _gat=1; _ga_MHSNPJKWC7=GS1.2.1710114280.2.1.1710116387.0.0.0");
        curl_easy_perform(curl);
    }

    // Process the content line by line
    std::istringstream iss(readBuffer);
    std::string line;
    int totalSum = 0;

    while (std::getline(iss, line)) {
        // Find the first number from the beginning and the end
        int firstNum = -1, lastNum = -1;
        for (char ch : line) {
            if (isdigit(ch)) {
                if (firstNum == -1) {
                    firstNum = ch - '0';
                }
                lastNum = ch - '0';
            }
        }

        // Combine the numbers and add to the total sum
        if (firstNum != -1 && lastNum != -1) {
            int combinedNum = firstNum * 10 + lastNum;
            totalSum += combinedNum;
        }
    }

    // Output the result
    std::cout << "Total Sum: " << totalSum << std::endl;

    // Check whether the web document data is obtained.
    // std::cout << "Webpage content:\n" << readBuffer << std::endl;


    // g++ -std=c++11 1a.cpp -o 1a -lcurl && ./1a

    // g++ -std=c++11 1a.cpp -o 1a -lcurl && ./1a : This command is used to compile C++ program. g++ is the C++ compiler in the GNU compiler collection. 1a.cpp is the source code file. -o 1a specifies the name of the output executable file 1a. -lcurl is a link option that tells the compiler to include the libcurl library when linking because libcurl is used in your program to send network requests. 

    // So please use this command when running the program.

    return 0;
}
