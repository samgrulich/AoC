import sys
import numpy as np


def solve_a(ranges: np.ndarray, ids: np.ndarray):
    last_index = 0
    fresh = 0
    for num in ids:
        lb, ub = ranges[last_index]
        while num > ub:
            last_index += 1
            if last_index >= len(ranges):
                break
            lb, ub = ranges[last_index]
        if last_index >= len(ranges):
            break
        if num >= lb:
            # print(num, lb, ub)
            fresh += 1
    return fresh


def solve_b(ranges: np.ndarray):
    sum = np.int64(0)
    prev_ub = np.int64(0)
    for lb, ub in ranges:
        lb = max(prev_ub + 1, lb)
        if lb <= ub:
            sum += ub - lb + 1
            prev_ub = ub
        else:
            print(lb, ub)
    return sum


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python main.py <filename>")
        exit(1)

    filename = sys.argv[1]
    file_content = ""
    with open(filename, "r") as f:
        file_content = f.read()

    ranges_str, ids_str = file_content.split("\n\n")
    ranges = np.array(
        [line.split("-") for line in ranges_str.split("\n")], dtype=np.int64
    )
    ids = np.array(ids_str.split(), dtype=np.int64)

    ranges = np.sort(ranges, axis=0)
    ids = np.sort(ids)

    print("result: ", solve_b(ranges))
