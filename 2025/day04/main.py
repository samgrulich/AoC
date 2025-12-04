import sys
import numpy as np
from scipy.signal import convolve2d


def conv2d(A: np.ndarray, kenrel: np.ndarray):
    h, w = A.shape
    A = np.zeros((h, w)) + (chars == "@")
    return convolve2d(A, kernel, mode="same", boundary="fill")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python main.py <filename>")
        exit(1)

    filename = sys.argv[1]
    lines = np.array([], dtype=str)
    with open(filename, "r") as f:
        lines = np.array([line.strip() for line in f.readlines()], str)

    chars = lines.view("U1").reshape(len(lines), -1)
    kernel = np.ones((3, 3))
    kernel[1, 1] = 0

    counts = conv2d(chars, kernel)
    indices = np.logical_and((counts < 4), (chars == "@"))
    chars[indices] = "x"
    for row in ["".join(row) for row in chars]:
        print(row)
    print(indices.sum())
