# SPDX-License-Identifier: Apache-2.0

import matplotlib.pyplot as plt

# Load data from the file
sizes = []
counts = []

total_allocations = 0  # To store the total number of allocations

with open('alloc_histogram.txt', 'r') as f:
    for line in f:
        size, count = map(int, line.split())
        sizes.append(size)
        counts.append(count)
        total_allocations += count  # Sum up the total number of allocations

# Plot the histogram
plt.bar(sizes, counts, width=10)
plt.xlabel('Allocation Size (bytes)')
plt.ylabel('Number of Allocations')

# Set the plot title with total allocation count
plt.title(f'Memory Allocation Size Histogram\nTotal Allocations: {total_allocations:,}')

# Show the plot
plt.show()

