#include "HttpGetClient.cpp"

int main() {
    std::cout << "Enter URL" << std::endl;
    std::string url;
    std::cin >> url;

    HttpGetClient client(url);
    std::cout << client.printData();
    client.writeDataToFile("document.txt");

    return 0;
}