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

def calcWeakScaling(algo):
    cores = [1,2,4,8,16]
    problem_sizes = [5000,7071,10000,14142,20000]
    base_filename = 'runtime/report_' + algo + "_"
    versions = ["par_omp_", "th_"]
    for version in versions:
        t1 = 0
        csv_file = "scaling/weak_scaling_" + algo + "_" + version + ".csv"
        csv_data = []
        header = ["Problem Size", "Cores", "Time (s)", "Scaling efficiency"]
        csv_data.append(header)

        for i in range(len(cores)):
            core = cores[i]
            problem_size = problem_sizes[i]
            filename = base_filename + version + str(core) + "_scal.csv"
            print(filename)
            df = pd.read_csv(filename)
            time = df[df['Size']==problem_size]['Median Total Time (s)'].values[0]
            if core == 1:
                t1=time
            scaling_efficiency = t1 / time
            csv_data.append([
                f"{problem_size}",
                f"{core}",
                f"{time:.2f}",
                f"{scaling_efficiency:.2f}",
            ])

            # Write data to CSV
            with open(csv_file, 'w', newline='') as csvfile:
                writer = csv.writer(csvfile)
                writer.writerows(csv_data)


def calcStrongScaling(algo):
    cores = [1,2,4,8,16]
    problem_sizes = [10000,14142,20000]
    base_filename = 'runtime/report_' + algo + "_"
    versions = ["par_omp_", "th_"]
    for version in versions:
        for problem_size in problem_sizes:
            t1 = 0
            csv_file = "scaling/strong_scaling_" + algo + "_" + version + "_" + str(problem_size) + ".csv"
            csv_data = []
            header = ["Problem Size", "Cores", "Time (s)", "Scaling efficiency"]
            csv_data.append(header)

            for core in cores:
                filename = base_filename + version + str(core) + "_scal.csv"
                print(filename)
                df = pd.read_csv(filename)
                print(problem_size)
                time = df[df['Size']==problem_size]['Median Total Time (s)'].values[0]
                if core == 1:
                    t1=time
                scaling_efficiency = t1 / (core*time)
                csv_data.append([
                    f"{problem_size}",
                    f"{core}",
                    f"{time:.2f}",
                    f"{scaling_efficiency:.2f}",
                ])

                # Write data to CSV
                with open(csv_file, 'w', newline='') as csvfile:
                    writer = csv.writer(csvfile)
                    writer.writerows(csv_data)

def calcJitter(data):
    jmin = np.min(data)
    jmax = np.max(data)
    jitter = jmax-jmin
    return jitter

def showJitter(path, version):
    # Example Data
    thread_counts = ['1', '2', '4', '8', '16']              # Thread counts
    problem_sizes = ['5000', '7500', '10000', '12500']  # Problem sizes

    jitter_values = []
    for problem_size in problem_sizes:
        thread_count_jitter_vals = []
        for thread_count in thread_counts:
            if thread_count == '1':
                filename = path + thread_count + "/" + path[:3] + "_ser_50.txt"
            else:
                filename = path + thread_count + "/" + path[:3] + "_" + version + "50_" + thread_count + ".txt"
            total_time, total_cpu_time = extract_data(filename, problem_size)
            jitter = calcJitter(total_time)
            thread_count_jitter_vals.append(jitter)
        jitter_values.append(thread_count_jitter_vals)

    # Create the heatmap
    plt.figure(figsize=(10, 10))

    sns.set(font_scale=2)
    ax = sns.heatmap(jitter_values, annot=True, fmt=".2f", cmap="Reds", xticklabels=thread_counts, yticklabels=problem_sizes)

    # Add labels and title
    title = "Jitter [s] (" + path[:-1] + " " + version[:-1] + ")"
    plt.title(title, fontsize=25)
    plt.xlabel("Thread Count", fontsize=20)
    plt.ylabel("Problem Size", fontsize=20)
    plt.xticks(fontsize=15)
    plt.yticks(fontsize=15)

    # Show the plot
    plt.tight_layout()
    plt.show()


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
            test_vals = {5000,7071,10000,14142,20000}
            #test_vals = {2500,5000,7500,10000,12500, 15000, 17500, 20000}
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
        calcWeakScaling(algo[:3])
        calcStrongScaling(algo[:3])


#process_folder_to_csv("auction/1", "asdf")
generateReports()
#showJitter("hungarian/","threadpool_")
#showJitter("hungarian/","par_omp_")
#showJitter("auction/","threadpool_")
#showJitter("auction/","par_omp_")
