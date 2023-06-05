#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>

// Function to fetch data from a file
std::vector<double> fetchData(const std::string& filename) {
    std::vector<double> values;
    std::ifstream file(filename);
    double num;
    while (file >> num) {
        values.push_back(num);
    }
    return values;
}

// Function to calculate the histogram of the given values
std::vector<int> calculateHistogram(const std::vector<double>& values, int numBins, int numThreads) {
    std::vector<int> histogram(numBins, 0);

    // Parallelize the histogram calculation across multiple threads
    #pragma omp parallel for num_threads(numThreads)
    for (int i = 0; i < values.size(); ++i) {
        int binIndex = static_cast<int>((values[i] / 5.0) * numBins);

        // Update the histogram bin atomically to avoid race conditions
        #pragma omp atomic
        ++histogram[binIndex];
    }

    return histogram;
}

int main(int argc, char** argv) {
    std::string inputFile = "input.txt";

    // Check if the number of threads is provided as a command-line argument
    if (argc < 2) {
        std::cout << "Usage: ./histogram <num_threads>\n";
        return 1;
    }

    // Extract the number of threads from the command-line argument
    int threadCount = std::stoi(argv[1]);

    // Fetch the data from the input file
    std::vector<double> data = fetchData(inputFile);

    // Measure the execution time
    double startTime = omp_get_wtime();

    // Generate the histogram using the specified number of threads
    std::vector<int> histogram = calculateHistogram(data, 5, threadCount);

    double endTime = omp_get_wtime();
    double executionTime = endTime - startTime;

    // Print the histogram with bin ranges and frequencies
    for (int i = 0; i < histogram.size(); ++i) {
        double binStart = i * (5.0 / histogram.size());
        double binEnd = (i + 1) * (5.0 / histogram.size());
        std::cout << "[" << binStart << " - " << binEnd << "]: ";
        std::cout << histogram[i] << " ";
        std::cout << "\n";
    }

    // Print the execution time of the histogram generation process
    std::cout << "\nProcessing Time: " << executionTime << " seconds\n";

    return 0;
}
