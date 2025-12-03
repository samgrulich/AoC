import sys
import numpy as np

MAX_N = 12


def slice_mat(A: np.ndarray, ids: np.ndarray, offset: int):
    off = -offset if offset != 0 else None
    return [row[i + 1 : off] for row, i in zip(A, ids)]


def slice_ids(A, ids: list):
    return [row[i] for row, i in zip(A, ids)]


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

    prev_ids = -np.ones(n, np.int32)
    results = np.array([])
    for offset in range(MAX_N - 1, -1, -1):
        # print(numbers, prev_ids, offset)
        mats = slice_mat(numbers, prev_ids, offset)
        print(prev_ids)
        ids = [np.argmax(arr) for arr in mats]
        res = slice_ids(mats, ids)
        print(np.array(ids))
        print("mats: ", mats)
        prev_ids = prev_ids + np.array(ids) + 1
        # print(res)
        results = np.append(results, res)

    tens = np.pow(10, np.arange(MAX_N - 1, -1, -1))
    results = results.reshape(-1, n).T

    print((tens * results).astype(np.int64).sum(1))
    print((tens * results).astype(np.float64).sum(1).sum())
