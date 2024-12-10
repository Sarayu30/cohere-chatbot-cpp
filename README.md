Thank you for the clarification! Here's the updated README with the correct file name `cohere_app.cpp`:

```markdown
# Cohere API Integration Chatbot (C++)

This project demonstrates how to integrate with the Cohere API in C++ to create a simple chatbot. The chatbot takes user input, sends it to the Cohere API, and displays the generated response. The program uses `libcurl` for making HTTP requests and `nlohmann::json` for parsing the JSON response from the API.

## Features
- Interact with the Cohere API to generate text-based responses.
- Handle user input and display the AI-generated responses.
- JSON response parsing and error handling.

## Prerequisites

Before running the project, you need to install the following dependencies:

1. **C++ Compiler**: Ensure you have a C++ compiler installed (e.g., GCC, Clang, or MSVC).
2. **CURL Library**: The program uses `libcurl` for making HTTP requests. You need to install it on your system.
3. **nlohmann::json**: A header-only C++ library for JSON parsing.

### Installing Dependencies

#### 1. Install `libcurl`
   - On **Linux** (Debian-based systems like Ubuntu):
     ```bash
     sudo apt-get update
     sudo apt-get install libcurl4-openssl-dev
     ```
   - On **macOS**:
     ```bash
     brew install curl
     ```
   - On **Windows**:
     - Download the precompiled `libcurl` binaries from [curl.se](https://curl.se/download.html).
     - Follow the installation instructions on the website.

#### 2. Install `nlohmann::json`
   - Since `nlohmann::json` is a header-only library, you can download the single header file or install it via a package manager:
     - On **Linux** (Debian-based systems):
       ```bash
       sudo apt-get install nlohmann-json3-dev
       ```
     - On **macOS**:
       ```bash
       brew install nlohmann-json
       ```
     - Alternatively, you can download the header file directly from the [nlohmann::json GitHub repository](https://github.com/nlohmann/json).

## Configuration

1. **Cohere API Key**:  
   You'll need an API key from Cohere to use their service. You can obtain it from the [Cohere API documentation](https://cohere.ai/). Replace the placeholder in the code with your own API key.

   ```cpp
   std::string apiKey = "YOUR_COHERE_API_KEY";  // Replace with your API key
   ```

## Building and Running the Program

1. **Clone or Download the Repository**:  
   Clone or download the source code to your local machine.

   ```bash
   git clone https://github.com/your-username/cohere-chatbot-cpp.git
   cd cohere-chatbot-cpp
   ```

2. **Compile the Program**:  
   If you are using a C++ compiler like `g++`, you can compile the program using the following command:

   ```bash
   g++ -std=c++11 -o cohere_app cohere_app.cpp -lcurl
   ```

   This will generate an executable named `cohere_app`.

3. **Run the Program**:  
   Once compiled, run the program using:

   ```bash
   ./cohere_app
   ```

   - The program will prompt you to enter your input.
   - Type your message, and the program will return a generated response from the Cohere API.
   - Type `exit` to quit the program.

## Example Usage

```
You: Hello, how are you?
AI: I'm doing great! How about you?
```

### Troubleshooting

- **cURL Error**: If you encounter a `cURL` error, ensure that `libcurl` is correctly installed and accessible in your environment.
- **JSON Parsing Error**: If there’s an error parsing the API response, check the format of the JSON returned by the API. Make sure the `generations` field is present in the response.

## Acknowledgements

- [Cohere API](https://cohere.ai/) for providing the API for text generation.
- [libcurl](https://curl.se/libcurl/) for handling HTTP requests.
- [nlohmann::json](https://github.com/nlohmann/json) for JSON parsing in C++.
```
 
