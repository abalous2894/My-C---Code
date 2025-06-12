#include <iostream>
#include <cellularapi_oem.h>/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

const string API_KEY = "my_api_key_here" // Add API key.
const string API_KEY = "https://v6.exchangerate-api.com/v6/" + API_KEY + "/latest/";

// API callback function for API response
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

// Function to fetch exchange rates
json fetchExchnageRates(const string& baseCurrency) {
    CURL* curl;
    CURLcode res;
    string response;

    curl = curl_easy_init();
    if (curl) {
        string url = API_URL + baseCurrency;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);
        curl_easy_cleanup;
    }

    return json::parse(response);
}

//Convert function
void convertCurrency(const json& rates, const string& from, const string& to, double amount) {
    if (rates["conversion_rates"].contains(to)) {
        double rate = rates["conversion_rates"][to];
        double converted = amount * rate;
        cout << amount << " " << from << " = " << converted << " " << to << endl;
    } else {
        cout << "Invalid target currency code!" << endl;
    }
}

int main() {
    string baseCurrency, targetCurrency;
    double amount;

    cout << "Enter base currency (ex: US Dollar): ";
    cin >> baseCurrency;
    cout << "Enter target currency (ex: EURO): ";
    cin >> targetCurrency;
    cout << "Enter amount: ";
    cin >> amount;

    json rates = fetchExchnageRates(baseCurrency);
    if (rates.contains("conversion_rates")) {
        convertCurrency(rates, baseCurrency, targetCurrency, amount);
    } else {
        cout << "Failed to retrieve exchange rates. Check API key or network." << endl;
    }

    return 0;
}