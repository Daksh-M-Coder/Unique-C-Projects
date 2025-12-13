# Weather Data Analyzer - Code Explanation

## Program Structure
The weather data analyzer is designed to process and analyze weather records from multiple cities. It uses a structure to organize weather data and provides functionality for file I/O, statistical analysis, and data visualization. The program follows a menu-driven approach for user interaction.

## Key Components

### Header Files
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
```
- `stdio.h`: For input/output operations and file handling
- `stdlib.h`: For program termination with `exit()`
- `string.h`: For string operations like `strcpy()`
- `float.h`: For floating-point constants like `FLT_MAX`

### Constants and Data Structures
```c
#define MAX_RECORDS 1000
#define CITY_NAME_LEN 50

typedef struct {
    char city[CITY_NAME_LEN];
    float temperature;
    float humidity;
    float pressure;
} WeatherRecord;
```
- `MAX_RECORDS`: Maximum number of weather records that can be stored
- `CITY_NAME_LEN`: Maximum length of city names
- `WeatherRecord`: Structure to hold weather data for a single city

### Global Variables
```c
WeatherRecord records[MAX_RECORDS];
int recordCount = 0;
```
- `records`: Array to store all weather records
- `recordCount`: Tracks the current number of records

### Function Prototypes
```c
void addSampleData();
void loadWeatherData(const char* filename);
void saveWeatherData(const char* filename);
void analyzeData();
void printStatistics();
void printRecords();
void printMenu();
```
Each function handles a specific aspect of weather data management or UI.

## Detailed Code Walkthrough

### Main Function
The main function orchestrates the entire program:
1. Displays welcome message
2. Loads sample data for immediate testing
3. Runs a loop showing menu and processing user choices
4. Handles all user interactions

### Sample Data Initialization
```c
void addSampleData() {
    strcpy(records[0].city, "New York");
    records[0].temperature = 22.5;
    records[0].humidity = 65.0;
    records[0].pressure = 1013.25;
    // ... more records
    recordCount = 5;
}
```
Initializes the program with sample weather data for demonstration purposes.

### File I/O Operations

#### Loading Data
```c
void loadWeatherData(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file '%s'\n", filename);
        return;
    }

    recordCount = 0;
    while (recordCount < MAX_RECORDS && 
           fscanf(file, "%s %f %f %f", 
                  records[recordCount].city,
                  &records[recordCount].temperature,
                  &records[recordCount].humidity,
                  &records[recordCount].pressure) == 4) {
        recordCount++;
    }

    fclose(file);
    printf("Loaded %d records from '%s'\n", recordCount, filename);
}
```
- Opens file in read mode
- Uses `fscanf` to parse space-separated values
- Continues until end of file or maximum records reached
- Updates record count and closes file

#### Saving Data
```c
void saveWeatherData(const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not create file '%s'\n", filename);
        return;
    }

    for (int i = 0; i < recordCount; i++) {
        fprintf(file, "%s %.2f %.2f %.2f\n",
                records[i].city,
                records[i].temperature,
                records[i].humidity,
                records[i].pressure);
    }

    fclose(file);
    printf("Saved %d records to '%s'\n", recordCount, filename);
}
```
- Opens file in write mode
- Writes each record in space-separated format
- Uses `fprintf` for formatted output
- Closes file and confirms operation

### Data Analysis Functions

#### Extreme Value Analysis
```c
void analyzeData() {
    // Find hottest and coldest cities
    int hottestIndex = 0, coldestIndex = 0;
    for (int i = 1; i < recordCount; i++) {
        if (records[i].temperature > records[hottestIndex].temperature) {
            hottestIndex = i;
        }
        if (records[i].temperature < records[coldestIndex].temperature) {
            coldestIndex = i;
        }
    }
    
    // Similar logic for humidity extremes
}
```
- Iterates through records to find extreme values
- Uses index tracking for efficient comparison
- Identifies cities with maximum and minimum values

#### Statistical Summary
```c
void printStatistics() {
    // Calculate averages and track min/max values
    float tempSum = 0, humiditySum = 0, pressureSum = 0;
    float tempMin = FLT_MAX, tempMax = -FLT_MAX;
    // ... similar for humidity and pressure
    
    for (int i = 0; i < recordCount; i++) {
        // Accumulate sums for averages
        tempSum += records[i].temperature;
        
        // Track min/max values
        if (records[i].temperature < tempMin) tempMin = records[i].temperature;
        if (records[i].temperature > tempMax) tempMax = records[i].temperature;
        // ... similar for humidity and pressure
    }
    
    // Display results
    printf("Average Temperature: %.2f°C (Min: %.2f°C, Max: %.2f°C)\n", 
           tempSum/recordCount, tempMin, tempMax);
    // ... similar for humidity and pressure
}
```
- Calculates sum, average, minimum, and maximum for each parameter
- Uses `FLT_MAX` and `-FLT_MAX` for initial min/max values
- Formats output for readability

### Data Display Functions

#### Formatted Record Display
```c
void printRecords() {
    printf("\n===== Weather Records =====\n");
    printf("%-15s %-12s %-10s %-10s\n", "City", "Temperature", "Humidity", "Pressure");
    printf("------------------------------------------------------\n");
    
    for (int i = 0; i < recordCount; i++) {
        printf("%-15s %-10.2f°C %-9.2f%% %-10.2f hPa\n",
               records[i].city,
               records[i].temperature,
               records[i].humidity,
               records[i].pressure);
    }
}
```
- Uses formatted output for tabular display
- Aligns columns with width specifiers
- Includes units for clarity

## Input/Output Handling
Special attention is paid to input/output handling:
- `scanf("%s", filename)`: Reads filename without spaces
- `fscanf(file, "%s %f %f %f", ...)`: Parses structured data
- `fprintf(file, "%s %.2f %.2f %.2f\n", ...)`: Writes formatted data
- Space before format specifier in `scanf(" %c", ...)` consumes leftover newlines

## Program Flow
1. Program starts and loads sample data
2. Main loop displays menu and processes user choices
3. Each operation is executed through dedicated functions
4. User can continue operations or exit
5. All data operations provide feedback

## Learning Points
1. **File I/O Operations**: Reading from and writing to text files
2. **Structured Data**: Using structs to organize related information
3. **Statistical Analysis**: Calculating averages, minima, and maxima
4. **String Handling**: Managing city names with character arrays
5. **Formatted I/O**: Creating readable output with printf format specifiers
6. **Error Handling**: Checking file operations and data availability
7. **Menu-Driven Interface**: Building interactive console applications
8. **Floating-Point Operations**: Working with real-number data

## Limitations and Possible Improvements
1. **File Format Constraints**: Requires specific space-separated format
2. **City Name Limitations**: No spaces allowed in city names in files
3. **Fixed Array Size**: Could be improved with dynamic memory allocation
4. **Limited Analysis**: Could include more statistical measures
5. **Data Validation**: No validation of input data ranges
6. **Sorting Capability**: Could sort records by different criteria
7. **Search Functionality**: Could search for specific cities or conditions