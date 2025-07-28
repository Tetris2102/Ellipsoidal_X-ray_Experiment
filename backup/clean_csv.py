# Cleans a .csv file from unuseful momenta lines with px, py and pz of 0, 0, 0.5
# i.e. lines like 0,3994,0,0,0.5

import csv

def filter_csv(input_file, output_file):
    with open(input_file, 'r') as infile, open(output_file, 'w', newline='') as outfile:
        reader = csv.reader(infile)
        writer = csv.writer(outfile)
        
        for row in reader:
            # Skip lines that don't have 5 columns (optional)
            if len(row) != 5:
                continue
            
            # Check if the last three values are 0, 0, 0.5 (as strings)
            if row[2] == '0' and row[3] == '0' and row[4] == '0.5':
                continue  # Skip this line
            
            writer.writerow(row)

# Usage
input_csv = "gamma_momenta_flat.csv"  # Your input file
output_csv = "filtered_gamma_momenta_flat.csv"  # Output file after filtering

filter_csv(input_csv, output_csv)
print(f"Filtered CSV saved to {output_csv}")