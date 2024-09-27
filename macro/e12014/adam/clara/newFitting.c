#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // for std::max_element
#include <utility>   // for std::pair
#include <limits>    // for std::numeric_limits

// Include ROOT headers for histogram manipulation and fitting
#include "TH1F.h"
#include "TF1.h"
#include "TMath.h"

// Include AtCSVReader
#include "AtCSVReader.h"

std::vector<std::vector<float>> csvData; //global so everything can access it

double fitf(double* x, double* par);
double fitf2(double* x, double* par);

double findSig(double time) {
  double tdrift = (time-73.6)*0.32;
  if (tdrift < 0) {
    tdrift = 0;
  }
  double sigcm = std::sqrt(2*0.0055*tdrift);
  double sigms = sigcm/0.815; //0.815 cm/ms is drift velocity
  double sigtb = sigms/0.32; //conversion of ms to tb
  return sigtb;
}

std::pair<double, double> findMax(const std::vector<std::vector<float>>& csvData, int columnIndex) {
    // Ensure the data is not empty and the column index is valid
    if (csvData.empty() || columnIndex >= csvData[0].size()) {
        std::cerr << "Invalid data or column index!" << std::endl;
        return {-1.0, -1.0}; // Return an error code
    }

    float maxValue = -std::numeric_limits<float>::infinity();
    //cout << maxValue;
    int maxIndex = -1;

    for (const auto& vec: csvData)
    {
        auto maxIt = std::max_element(vec.begin(), vec.end());
        maxValue = *maxIt;
        maxIndex = std::distance(vec.begin(), maxIt);

    }

    double mValue = static_cast<double>(maxValue); // Convert maxValue to double
    double mIndex = static_cast<double>(maxIndex); // Convert index to double
    return {mValue, mIndex};
}

// Define a function to read data from a CSV file and return a vector of vectors containing the data
// Updated CSV Parser using AtCSVReader
std::vector<std::vector<float>> readCSV(const std::string& fileName) {
    // Create an AtCSVReader object
    std::ifstream file("5bad.csv");
    std::string line;
    std::getline(file, line);
    //AtCSVReader<float> csvReader(file);

    // Check if the file was loaded successfully
    // use standard C++ to check if file was loaded successfully

    std::vector<std::vector<float>> data;
    

    // Loop through the rows of the CSV
    for(auto& row : CSVRange<float>(file)) {
        data.resize(row.size()-1); // Assuming 5 columns in the CSV file
        for(int i = 1; i < row.size(); ++i) {
            data.at(i-1).push_back(row[i]) ;
        }
    }

    return data;
}

// Updated newFitting function to take a filename parameter
void newFitting() { //const std::string& fileName
    // Read data from the CSV file
    int column = 0;
    csvData = readCSV("5bad.csv");

    // Check if the data has been loaded correctly
    if (csvData.empty() || csvData[0].empty()) {
        std::cerr << "Error: No data found in the CSV file or file is improperly formatted." << std::endl;
        return;
    }

    int numBins = csvData[0].size();
    TCanvas* canvas = new TCanvas("canvas", "Fit Results", 800, 600);
    TH1F* hTest = new TH1F("hTest", "Test Histogram", numBins, 0, numBins); // Adjust the range and bins based on data size

    // Set the bin contents from the CSV data
    for (int i = 0; i < numBins; i++) {
        int binContent = csvData[column][i]; // last column of data
        hTest->SetBinContent(i + 1, binContent); // Bin indices start at 1 in ROOT histograms
    }
    // Create a TF1 object to define the fit function
    TF1* fitFunction = new TF1("fitFunction", fitf, 0, numBins, 3); // Range from 0 to number of bins, with 5 parameters
    // Set initial parameter values for the fit
    auto result = findMax(csvData, column); // finds the max value and index of the max value
    double sigma = findSig(result.second);
    fitFunction->SetParameters(result.first, result.second, sigma); // Example: a = 1, b = numBins/2, c = 10, m = 0, d = 0
    TF1* fitFunction2 = new TF1("fitFunction2", fitf2, 0, numBins, 5); // Range from 0 to number of bins, with 5 parameters
    

    auto fitResult = hTest->Fit(fitFunction, "RQS"); // "R" means use the range specified by the TF1 object
    double par2 = fitResult->Parameter(2);
    fitResult->Chi2();

    int begin = static_cast<int>(result.second - par2*3);
    int end = static_cast<int>(result.second + par2*3);

    fitFunction2->SetParameters(result.first, result.second, par2, 0, 0);
    hTest->Fit(fitFunction2, "RQS","",begin,end);
    hTest->Draw();
    fitFunction->Draw("SAME"); // Draw the fitted function on top of the histogram
    fitFunction2->SetLineColor(kBlack);
    fitFunction2->SetRange(begin,end);
    fitFunction2->Draw("SAME");
    canvas->Update();

    // Draw the histogram and the fitted function
    
}

// Define a function using the new algorithm: f(x) = a * exp(-1/2 * ((x-b)/c)^2) + m * x + d
double fitf(double* x, double* par) {
     // Using the first column (index 0)
    double a = par[0];//result.first; //max value
    //std::cout << a;
    double b = par[1];//result.second; //max index
    double c = par[2];//findSig(b); //sigma!
    //double m = par[3];
    //double d = par[4];

    double arg = (x[0] - b) / c;
    double gaussian = a * TMath::Exp(-0.5 * arg * arg);


    //double linear = m * x[0] + d;

    return gaussian; //+ linear;
}

double fitf2(double* x, double* par) {
     // Using the first column (index 0)
    double a = par[0];//result.first; //max value
    //std::cout << a;
    double b = par[1];//result.second; //max index
    double c = par[2];//findSig(b); //sigma!
    double m = par[3];
    double d = par[4];

    double arg = (x[0] - b) / c;
    double gaussian = a * TMath::Exp(-0.5 * arg * arg);


    double linear = m * x[0] + d;

    return gaussian + linear;
}

int main() {
    // Call the newFitting function with the filename as a parameter
    newFitting();

    return 0;
}