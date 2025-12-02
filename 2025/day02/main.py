import sys
import numpy as np


def get_doubles_in_range(min_s: str, max_s: str) -> list[int]:
    doubles = []
    min, max = int(min_s), int(max_s)
    for num in range(min, max + 1):
        num_s = str(num)
        num_l = len(num_s)
        if num_l % 2 != 0:
            continue
        if num_s[: num_l // 2] == num_s[num_l // 2 :]:
            doubles.append(num)
    return doubles


def get_patterns_in_range(min_s: str, max_s: str) -> list[int]:
    patterns = []
    min, max = int(min_s), int(max_s)
    for num in range(min, max + 1):
        num_s = str(num)
        num_l = len(num_s)
        for i in range(1, num_l // 2 + 1):
            if num_l % i != 0:
                continue
            parts = np.fromiter(
                (num_s[j * i : (j + 1) * i] for j in range(num_l // i)), np.int32
            )
            # print(num_s, i, parts, (parts == parts[0]))
            if (parts == parts[0]).all() and not num in patterns:
                patterns.append(num)
    return patterns


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python main.py <filename>")
        exit(1)

    filename = sys.argv[1]
    content = ""
    with open(filename, "r") as f:
        content = f.read().strip()

    ranges = content.split(",")
    ranges = [[num for num in r.split("-")] for r in ranges]

    doubles = np.array([], dtype=np.int64)
    for r in ranges:
        range_doubles = get_patterns_in_range(r[0], r[1])
        doubles = np.append(doubles, range_doubles)
        # print(f"{r[0]}-{r[1]}, {range_doubles}")

    sum = doubles.astype(np.int64).sum()
    print(f"result is {sum}")
