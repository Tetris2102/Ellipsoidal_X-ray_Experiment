import numpy as np
import matplotlib.pyplot as plt

# Load data
data = np.loadtxt("/Users/tarasosaulenko/X-RAY EXPERIMENT/data/data_raw/400 keV/flat/gamma_momenta.csv", delimiter=',', skiprows=1)
px, py, pz = data[:,2], data[:,3], data[:,4]

# Calculate average vector
avg_px, avg_py, avg_pz = np.mean(px), np.mean(py), np.mean(pz)

# Calculate divergence measures
vectors = np.column_stack((px, py, pz))
avg_vector = np.array([avg_px, avg_py, avg_pz])

plt.scatter(px, py)

# Add labels and a title
plt.xlabel("X-axis")
plt.ylabel("Y-axis")
plt.title("Customizable Scatter Plot")

# Display the plot
plt.show()