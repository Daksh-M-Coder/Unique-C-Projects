# Weather Data Analyzer

## Description
A comprehensive weather data analysis tool that loads, processes, and analyzes weather records from multiple cities. The program calculates statistical summaries, identifies extreme values, and provides insights into weather patterns across different locations.

## Features
- Load weather data from text files
- Save weather data to text files
- Analyze data to find extreme values (hottest, coldest, most humid, least humid cities)
- Calculate and display statistical summaries (averages, minimums, maximums)
- Display formatted weather records
- Sample data included for immediate testing

## Data Structure
The program uses a structure to represent weather data:
```c
typedef struct {
    char city[CITY_NAME_LEN];
    float temperature;
    float humidity;
    float pressure;
} WeatherRecord;
```

## File Format
Weather data files should be in the following format (space-separated):
```
CityName Temperature Humidity Pressure
```

Example:
```
New_York 22.5 65.0 1013.25
Los_Angeles 28.0 55.0 1010.0
Chicago 18.0 70.0 1015.5
```

Note: City names with spaces should use underscores.

## Standard Library Functions Used
- `stdio.h` - For input/output operations and file handling (`printf`, `scanf`, `fopen`, `fclose`, `fscanf`, `fprintf`)
- `stdlib.h` - For program termination (`exit`)
- `string.h` - For string operations (`strcpy`)
- `float.h` - For floating-point constants (`FLT_MAX`)

## How to Compile and Run

### Compilation
```bash
gcc -o weather_analyzer main.c
```

### Execution
```bash
./weather_analyzer
```

On Windows:
```bash
weather_analyzer.exe
```

## How to Use
1. Run the program (sample data is automatically loaded)
2. Select an operation from the menu:
   - Load data from file: Read weather data from a text file
   - Save data to file: Save current data to a text file
   - Analyze data: Find extreme values in the dataset
   - Print statistics: Display statistical summaries
   - Print all records: Show all weather records in a formatted table
   - Exit: Quit the program
3. Choose to continue or exit after each operation

## Sample Output
```
Welcome to the Weather Data Analyzer!

===== Weather Data Analyzer =====
1. Load data from file
2. Save data to file
3. Analyze data
4. Print statistics
5. Print all records
6. Exit
================================
Enter your choice: 5

===== Weather Records =====
City            Temperature  Humidity   Pressure
------------------------------------------------------
New York        22.50°C      65.00%     1013.25 hPa
Los Angeles     28.00°C      55.00%     1010.00 hPa
Chicago         18.00°C      70.00%     1015.50 hPa
Houston         30.50°C      75.00%     1008.75 hPa
Phoenix         38.00°C      25.00%     1005.00 hPa
```

## Statistical Analysis
The program provides the following statistical insights:
- Total number of records
- Average, minimum, and maximum temperature
- Average, minimum, and maximum humidity
- Average, minimum, and maximum pressure
- Identification of cities with extreme values

## Educational Value
This implementation demonstrates:
1. File I/O operations with structured data
2. Statistical analysis of numerical datasets
3. Data structure management and manipulation
4. String and numerical data processing
5. Formatted output for better readability
6. Menu-driven interface design