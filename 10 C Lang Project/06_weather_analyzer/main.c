#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX_RECORDS 1000
#define CITY_NAME_LEN 50

// Structure to represent weather data
typedef struct {
    char city[CITY_NAME_LEN];
    float temperature;
    float humidity;
    float pressure;
} WeatherRecord;

// Global array to store weather records
WeatherRecord records[MAX_RECORDS];
int recordCount = 0;

// Function prototypes
void addSampleData();
void loadWeatherData(const char* filename);
void saveWeatherData(const char* filename);
void analyzeData();
void printStatistics();
void printRecords();
void printMenu();

int main() {
    int choice;
    char filename[100];
    char continueOperation;

    printf("Welcome to the Weather Data Analyzer!\n");
    
    // Add some sample data for demonstration
    addSampleData();

    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Load data from file
                printf("Enter filename: ");
                scanf("%s", filename);
                loadWeatherData(filename);
                break;

            case 2: // Save data to file
                printf("Enter filename: ");
                scanf("%s", filename);
                saveWeatherData(filename);
                break;

            case 3: // Analyze data
                analyzeData();
                break;

            case 4: // Print statistics
                printStatistics();
                break;

            case 5: // Print all records
                printRecords();
                break;

            case 6: // Exit
                printf("Thank you for using the Weather Data Analyzer!\n");
                exit(0);

            default:
                printf("Invalid choice! Please select a valid option.\n");
        }

        printf("\nDo you want to perform another operation? (y/n): ");
        scanf(" %c", &continueOperation);
        printf("\n");

    } while (continueOperation == 'y' || continueOperation == 'Y');

    return 0;
}

// Function to add sample data
void addSampleData() {
    strcpy(records[0].city, "New York");
    records[0].temperature = 22.5;
    records[0].humidity = 65.0;
    records[0].pressure = 1013.25;
    
    strcpy(records[1].city, "Los Angeles");
    records[1].temperature = 28.0;
    records[1].humidity = 55.0;
    records[1].pressure = 1010.0;
    
    strcpy(records[2].city, "Chicago");
    records[2].temperature = 18.0;
    records[2].humidity = 70.0;
    records[2].pressure = 1015.5;
    
    strcpy(records[3].city, "Houston");
    records[3].temperature = 30.5;
    records[3].humidity = 75.0;
    records[3].pressure = 1008.75;
    
    strcpy(records[4].city, "Phoenix");
    records[4].temperature = 38.0;
    records[4].humidity = 25.0;
    records[4].pressure = 1005.0;
    
    recordCount = 5;
}

// Function to load weather data from a file
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

// Function to save weather data to a file
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

// Function to analyze weather data
void analyzeData() {
    if (recordCount == 0) {
        printf("No data available for analysis!\n");
        return;
    }

    printf("\n===== Weather Data Analysis =====\n");
    
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
    
    printf("Hottest city: %s (%.2f°C)\n", 
           records[hottestIndex].city, 
           records[hottestIndex].temperature);
    printf("Coldest city: %s (%.2f°C)\n", 
           records[coldestIndex].city, 
           records[coldestIndex].temperature);
    
    // Find highest and lowest humidity
    int humidIndex = 0, dryIndex = 0;
    for (int i = 1; i < recordCount; i++) {
        if (records[i].humidity > records[humidIndex].humidity) {
            humidIndex = i;
        }
        if (records[i].humidity < records[dryIndex].humidity) {
            dryIndex = i;
        }
    }
    
    printf("Most humid city: %s (%.2f%%)\n", 
           records[humidIndex].city, 
           records[humidIndex].humidity);
    printf("Least humid city: %s (%.2f%%)\n", 
           records[dryIndex].city, 
           records[dryIndex].humidity);
}

// Function to print statistical summary
void printStatistics() {
    if (recordCount == 0) {
        printf("No data available for statistics!\n");
        return;
    }

    printf("\n===== Weather Statistics =====\n");
    
    // Calculate averages
    float tempSum = 0, humiditySum = 0, pressureSum = 0;
    float tempMin = FLT_MAX, tempMax = -FLT_MAX;
    float humidityMin = FLT_MAX, humidityMax = -FLT_MAX;
    float pressureMin = FLT_MAX, pressureMax = -FLT_MAX;
    
    for (int i = 0; i < recordCount; i++) {
        // Sum for averages
        tempSum += records[i].temperature;
        humiditySum += records[i].humidity;
        pressureSum += records[i].pressure;
        
        // Track min/max for temperature
        if (records[i].temperature < tempMin) tempMin = records[i].temperature;
        if (records[i].temperature > tempMax) tempMax = records[i].temperature;
        
        // Track min/max for humidity
        if (records[i].humidity < humidityMin) humidityMin = records[i].humidity;
        if (records[i].humidity > humidityMax) humidityMax = records[i].humidity;
        
        // Track min/max for pressure
        if (records[i].pressure < pressureMin) pressureMin = records[i].pressure;
        if (records[i].pressure > pressureMax) pressureMax = records[i].pressure;
    }
    
    printf("Total records: %d\n", recordCount);
    printf("Average Temperature: %.2f°C (Min: %.2f°C, Max: %.2f°C)\n", 
           tempSum/recordCount, tempMin, tempMax);
    printf("Average Humidity: %.2f%% (Min: %.2f%%, Max: %.2f%%)\n", 
           humiditySum/recordCount, humidityMin, humidityMax);
    printf("Average Pressure: %.2f hPa (Min: %.2f hPa, Max: %.2f hPa)\n", 
           pressureSum/recordCount, pressureMin, pressureMax);
}

// Function to print all records
void printRecords() {
    if (recordCount == 0) {
        printf("No records found!\n");
        return;
    }

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

// Function to print the menu
void printMenu() {
    printf("\n===== Weather Data Analyzer =====\n");
    printf("1. Load data from file\n");
    printf("2. Save data to file\n");
    printf("3. Analyze data\n");
    printf("4. Print statistics\n");
    printf("5. Print all records\n");
    printf("6. Exit\n");
    printf("================================\n");
}