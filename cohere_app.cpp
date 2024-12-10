#include <iostream>
#include <string>
#include <curl/curl.h>
#include "json.hpp"  // Include the nlohmann/json library for JSON parsing

using json = nlohmann::json;  // Using alias for json from nlohmann library

// Callback function to handle API response data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;  // Calculate the total size of the received data
    output->append((char*)contents, totalSize);  // Append the response data to the output string
    return totalSize;  // Return the total size to curl
}

// Function to call the Cohere API and generate a response based on user input
std::string callCohereAPI(const std::string& userInput, const std::string& apiKey) {
    const std::string apiUrl = "https://api.cohere.ai/v1/generate";  // API endpoint for Cohere API
    CURL* curl;  // Declare a CURL object for making HTTP requests
    CURLcode res;  // Declare a variable to hold the result of the CURL request
    std::string readBuffer;  // String to store the response from the API

    // Initialize the global CURL environment
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();  // Initialize the CURL session

    if (curl) {
        struct curl_slist* headers = nullptr;  // Declare a variable to store HTTP headers
        // Add Authorization header (API Key) and Content-Type header for JSON
        headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // Prepare the JSON payload to send in the POST request
        json payload = {
            {"model", "command-xlarge-nightly"},  // Specify the model to use
            {"prompt", userInput},  // The user's input as the prompt for the model
            {"max_tokens", 100}  // Limit the maximum number of tokens for the response
        };

        std::string postData = payload.dump();  // Convert JSON payload to a string

        // Set up CURL options for the HTTP request
        curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());  // Set the API URL
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());  // Attach the POST data (JSON)
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);  // Set the headers
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);  // Set the write callback function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);  // Set the buffer to store the response
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);  // Disable SSL certificate verification (for testing)
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);  // Disable host verification (for testing)

        // Perform the CURL request
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "cURL Error: " << curl_easy_strerror(res) << std::endl;  // Print any CURL errors
        }

        // Clean up CURL and headers after the request
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    curl_global_cleanup();  // Clean up the global CURL environment
    return readBuffer;  // Return the response data as a string
}

// Main program to interact with the user and communicate with the Cohere API
int main() {
    std::string apiKey = "A3gw4U2Ojg0P7aOgGdSeB1ODK9PwADeul8meJFom";  // Replace with your Cohere API key

    while (true) {
        std::string userInput;  // Variable to store the user's input
        std::cout << "\nYou: ";  // Prompt the user for input
        std::getline(std::cin, userInput);  // Read the user's input

        if (userInput == "exit") {  // Exit condition if user types "exit"
            std::cout << "Exiting... Goodbye!" << std::endl;
            break;  // Break out of the loop and terminate the program
        }

        std::cout << "Processing..." << std::endl;  // Notify the user that the input is being processed

        // Call the Cohere API to get a response based on the user's input
        std::string response = callCohereAPI(userInput, apiKey);

        // Parse the JSON response from the API
        try {
            json jsonResponse = json::parse(response);  // Parse the JSON response string

            // Check if the "generations" field exists and contains valid data
            if (jsonResponse.contains("generations") && !jsonResponse["generations"].empty()) {
                std::string aiResponse = jsonResponse["generations"][0]["text"];  // Extract the AI's response text
                std::cout << "\nAI: " << aiResponse << std::endl;  // Print the AI's response
            } else {
                std::cout << "\nAI: No response generated or there was an issue." << std::endl;  // Handle empty or invalid response
            }
        } catch (const std::exception& e) {
            std::cerr << "Error parsing response: " << e.what() << std::endl;  // Print an error if JSON parsing fails
        }
    }

    return 0;  // Exit the program
}
