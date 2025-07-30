import os
import numpy as np
import csv
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

def read_sequential_times(serial_filename, val):
    df = pd.read_csv(serial_filename)
    #df.loc[df['Size'] == vak, 'Median Total Time (s)'].iloc[0]
    t1 = df[df['Size']==val]['Median Total Time (s)'].values[0]
    return t1

def calcJitter(data):
    jmin = np.min(data)
    jmax = np.max(data)
    percentile50 = np.percentile(data, 50)
    percentile25 = np.percentile(data, 25)
    percentile75 = np.percentile(data, 75)
    jitter = jmax-jmin
    return jitter,percentile50,percentile25,percentile75

def showJitter(algo, path):
    # Example Data
    thread_counts = ['1', '2', '4', '8']              # Thread counts
    problem_sizes = ['1000','1500','2000','2500', '3000']  # Problem sizes
    base_filename = path

    jitter_values = []
    for problem_size in problem_sizes:
        thread_count_jitter_vals = []
        for thread_count in thread_counts:
            if thread_count == '1':
                filename = base_filename + thread_count + "/" + algo + "_emmtrix_ser" + "_" + problem_size + ".txt"
            else:
                filename = base_filename + thread_count + "/" + algo + "_emmtrix_" + thread_count + "_" + problem_size + ".txt"
            print(filename)
            if algo == 'auc' and int(problem_size) > 1500 and thread_count == '8':
                jitter = 0
            else:
                size, count, tries, total_time, total_cpu_time = extract_data(filename)
                jitter, percentile50, percentile25, percentile75 = calcJitter(total_time)
            thread_count_jitter_vals.append(jitter)
        jitter_values.append(thread_count_jitter_vals)

    # Create the heatmap
    plt.figure(figsize=(10, 10))

    sns.set(font_scale=2)
    ax = sns.heatmap(jitter_values, annot=True, fmt=".2f", cmap="Reds", xticklabels=thread_counts, yticklabels=problem_sizes)

    # Add labels and title
    title = "Jitter [s] (" + path[:-1] + " Emmtrix)"
    plt.title( "Jitter [s] (Hungarian ePS)", fontsize=25)
    plt.xlabel("Thread Count", fontsize=20)
    plt.ylabel("Problem Size", fontsize=20)
    plt.xticks(fontsize=15)
    plt.yticks(fontsize=15)

    # Show the plot
    plt.tight_layout()
    plt.show()

# Function to extract numerical data from a text file
def extract_data(file_path):
    total_time = []
    total_cpu_time = []
    size = 0
    count = 50
    tries = 0
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.split()
            #print(parts)
            if len(parts) >= 1:
                if parts[0] == 'total:':
                    tries = int(parts[1])
            if len(parts) == 4 and parts[0] != "Auction":  # Ensure the line has the expected structure
                try:
                    #print(parts)
                    size = parts[0]
                    total_time.append(float(parts[2]))
                    total_cpu_time.append(float(parts[3]))
                except ValueError:
                    continue  # Skip lines with invalid numerical data


    return size, count, tries, total_time, total_cpu_time

# Function to calculate mean and median
def calculate_statistics(data):
    mean = np.mean(data)
    median = np.median(data)
    return mean, median

def calcRatio(tries,count):
    return count/tries

def process_folder_to_csv(folder_path, csv_file, serial_file):
    csv_data = []
    header = ["Size", "Tries", "Entries", "Ratio", "Speedup", "Mean Total Time (s)", "Median Total Time (s)", "Mean Total CPU Time (ms)", "Median Total CPU Time (ms)"]
    csv_data.append(header)

    for file_name in os.listdir(folder_path):
        if file_name.endswith('.txt'):
            file_path = os.path.join(folder_path, file_name)
            size, count, tries, total_time, total_cpu_time = extract_data(file_path)

            if total_time and total_cpu_time:  # Ensure data is not empty
                mean_total_time, median_total_time = calculate_statistics(total_time)
                mean_total_cpu_time, median_total_cpu_time = calculate_statistics(total_cpu_time)
                print(size)
                t1 = read_sequential_times(serial_file, int(size))

                speedup = float(t1) / median_total_time

                ratio = calcRatio(tries, count)

                csv_data.append([
                    f"{size}",
                    f"{tries}",
                    f"{count}",
                    f"{ratio:.6f}",
                    f"{speedup}",
                    f"{mean_total_time:.6f}",
                    f"{median_total_time:.6f}",
                    f"{mean_total_cpu_time:.6f}",
                    f"{median_total_cpu_time:.6f}"
                ])

    # Write data to CSV
    with open(csv_file, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerows(csv_data)



def generateReports():
    threads = ['1','2','4','8']
    algorithms = ['auction', 'hungarian/']
    for algo in algorithms:
        for thread in threads:
            report_file = "runtime/report_" + algo[:3] + "_" + thread + ".csv"
            folder_path = algo + "/" + thread
            serial_filename = algo[:3] + "_serial_times.csv"
            #serial_filename = ""
            process_folder_to_csv(folder_path, report_file, serial_filename)
            df = pd.read_csv(report_file)
            sorted_df = df.sort_values(by="Size")
            sorted_df.to_csv(report_file, index=False)


generateReports()
#showJitter('hun','hungarian/')
#showJitter('auc','auction/')