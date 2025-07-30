import os
import numpy as np
import csv
import pandas as pd
import math
import matplotlib.pyplot as plt
import seaborn as sns

def read_sequential_times(serial_filename, val):
    df = pd.read_csv(serial_filename)
    #df.loc[df['Size'] == vak, 'Median Total Time (s)'].iloc[0]
    t1 = df[df['Size']==val]['Median Total Time (s)'].values[0]
    return t1

# Function to extract numerical data from a text file
def extract_data(file_path, val):
    total_time = []
    total_cpu_time = []
    size = 0
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.split()
            if len(parts) == 4:  # Ensure the line has the expected structure
                try:
                    size = parts[0]
                    if int(size)==int(val):
                        total_time.append(float(parts[2]))
                        total_cpu_time.append(float(parts[3]))
                except ValueError:
                    continue  # Skip lines with invalid numerical data


    return total_time, total_cpu_time

# Function to calculate mean and median
def calculate_statistics(data):
    mean = np.mean(data)
    median = np.median(data)
    return mean, median

def process_folder_to_csv(folder_path, serial_filename):
    
    for file_name in os.listdir(folder_path):
        if file_name.endswith('.txt'):
            csv_file = "runtime/report_" + file_name[:-4] + ".csv"
            csv_data = []
            header = ["Size", "Speedup", "Mean Total Time (s)", "Median Total Time (s)", "Mean Total CPU Time (ms)", "Median Total CPU Time (ms)"]
            csv_data.append(header)
            file_path = os.path.join(folder_path, file_name)
            test_vals = {2500,5000,7500,10000,12500, 15000, 17500, 20000}
            for val in test_vals:
                total_time, total_cpu_time = extract_data(file_path, val)

                if total_time and total_cpu_time:  # Ensure data is not empty
                    mean_total_time, median_total_time = calculate_statistics(total_time)
                    mean_total_cpu_time, median_total_cpu_time = calculate_statistics(total_cpu_time)
                    t1 = read_sequential_times(serial_filename, val)
                    
                    speedup = float(t1) / median_total_time

                    csv_data.append([
                        f"{val}",
                        f"{speedup:.6f}",
                        f"{mean_total_time:.6f}",
                        f"{median_total_time:.6f}",
                        f"{mean_total_cpu_time:.6f}",
                        f"{median_total_cpu_time:.6f}"
                    ])

                    # Write data to CSV
                    with open(csv_file, 'w', newline='') as csvfile:
                        writer = csv.writer(csvfile)
                        writer.writerows(csv_data)

            df = pd.read_csv(csv_file)
            sorted_df = df.sort_values(by="Size")
            sorted_df.to_csv(csv_file, index=False)

def generateReports():
    threads = ['1','2','4','8','16']
    algorithms = ['auction/', 'hungarian/']
    for algo in algorithms:
        for thread in threads:
            folder_path = algo + thread
            serial_filename = algo[:3] + "_serial_times.csv"
            process_folder_to_csv(folder_path, serial_filename)

generateReports()
