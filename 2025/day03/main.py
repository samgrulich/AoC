import sys
import numpy as np


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python main.py <filename>")
        exit(1)

    filename = sys.argv[1]
    lines = np.array([], dtype=str)
    with open(filename, "r") as f:
        lines = np.array([line.strip() for line in f.readlines()], str)

    n = len(lines)
    numbers = lines.view("U1").reshape(n, -1).astype(np.int32)

    i = np.argmax(numbers[:, :-1], axis=1)
    results = np.array([])
    for k, arr in enumerate(numbers):
        l = i[k]
        first = numbers[k, l]
        second = np.max(np.array(arr[l + 1 :]))
        result = int(str(first) + str(second))
        results = np.append(results, result)

    print(results, results.sum())
