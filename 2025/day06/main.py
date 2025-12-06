import sys
import re
import numpy as np


def solve_a(lines_in: list[str]):
    lines = [line.split() for line in lines_in]
    nums = np.array(lines[:-1], np.int64).T
    operators = np.array(lines[-1])

    sums = nums[operators == "+"].sum(1)
    prods = nums[operators == "*"].prod(1)

    return np.int64(sums.sum() + prods.sum())


def get_collens(operators_line: str):
    spaces = re.split(r"[+*]", operators_line)
    lens = [len(col) for col in spaces][1:]
    lens[-1] += 1
    return lens


def split_row(row, cs):
    i = 0
    res = []
    for c in cs:
        res.append(row[i : (i + c)])
        i += c + 1
    return res


def solve_b(lines_in: list[str]):
    cs = np.array(get_collens(lines_in[-1]))
    lines = np.array([split_row(line, cs) for line in lines_in[:-1]])
    operators, (r, c) = np.array(lines_in[-1].split()), lines.shape

    max_len = cs.max()
    lines = np.strings.rjust(lines, max_len)
    nums_separated = lines.view("U1").reshape((r, c, -1)).swapaxes(0, 1).swapaxes(1, 2)
    for i, group in enumerate(nums_separated):
        for row in group:
            res = "".join(row)
            if res == len(res) * " ":
                row[2] = 0 if operators[i] == "+" else 1
    nums = np.array(
        [["".join(row) for row in cols] for cols in nums_separated], dtype=np.int64
    )

    sums = nums[operators == "+"].sum(1)
    prods = nums[operators == "*"].prod(1)

    return np.int64(sums.sum() + prods.sum())


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python main.py <filename>")
        exit(1)

    filename = sys.argv[1]
    lines = []
    with open(filename, "r") as f:
        lines = [line.strip("\n") for line in f.readlines()]

    print(solve_b(lines))
