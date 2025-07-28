import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Load data
data = np.loadtxt("/Users/tarasosaulenko/Documents/GitHub/Ellipsoidal_X-ray_Experiment/data/data_raw/500 keV/flat/gamma_momenta.csv", delimiter=',', skiprows=1)
px, py, pz = data[:,2], data[:,3], data[:,4]

# Calculate average vector
avg_px, avg_py, avg_pz = np.mean(px), np.mean(py), np.mean(pz)

# Calculate divergence measures
vectors = np.column_stack((px, py, pz))
avg_vector = np.array([avg_px, avg_py, avg_pz])

# Normalize all vectors for angular calculations
norms = np.linalg.norm(vectors, axis=1)
normalized_vectors = vectors / norms[:, np.newaxis]
normalized_avg = avg_vector / np.linalg.norm(avg_vector)

# Calculate angles between each vector and average
dot_products = np.dot(normalized_vectors, normalized_avg)
angles = np.arccos(np.clip(dot_products, -1.0, 1.0))  # in radians
angular_divergence = np.mean(angles)

# Calculate magnitude variation
magnitude_std = np.std(norms)

print(f"Angular divergence: {np.degrees(angular_divergence)} degrees")

# # Create 3D plot
# fig = plt.figure(figsize=(12, 9))
# ax = fig.add_subplot(111, projection='3d')

# # Plot original vectors with half transparency
# ax.quiver(np.zeros_like(px), np.zeros_like(py), np.zeros_like(pz), 
#           px, py, pz, 
#           length=0.1, normalize=True, 
#           alpha=0.5, arrow_length_ratio=0.1, color='blue')

# # Plot average vector (red and thicker)
# ax.quiver(0, 0, 0, 
#           avg_px, avg_py, avg_pz, 
#           length=0.1, normalize=True, 
#           color='red', linewidth=2, arrow_length_ratio=0.1)

# # Set labels and title with divergence info
# ax.set_xlabel('X')
# ax.set_ylabel('Y')
# ax.set_zlabel('Z')
# ax.set_title(f'Momentum Directions of Emitted Particles\n'
#              f'Angular Divergence: {np.degrees(angular_divergence):.2f}°  '
#              f'Magnitude Variation: {magnitude_std:.2e}')

# # Equal aspect ratio
# ax.set_box_aspect([1,1,1])

# # Add legend
# from matplotlib.lines import Line2D
# legend_elements = [Line2D([0], [0], color='blue', alpha=0.5, lw=2, label='Individual Vectors'),
#                    Line2D([0], [0], color='red', lw=2, label='Average Vector')]
# ax.legend(handles=legend_elements)

# plt.tight_layout()
# plt.show()
