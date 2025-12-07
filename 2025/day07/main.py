import sys
import numpy as np


def solve_a(map: np.ndarray):
    start = np.where(lines[0] == "S")[0][0]
    stack = np.array([[1, start]])
    m, n = map.shape
    splits = 0
    while len(stack) != 0:
        coords = stack[0]
        stack = np.delete(stack, 0, axis=0)

        y, x = coords[0], coords[1]
        if y >= m or x >= n:
            continue
        item = map[y, x]
        if item == ".":
            map[y, x] = "|"
            stack = np.append(stack, [[y + 1, x]], axis=0)
        elif item == "^":
            splits += 1
            stack = np.append(stack, [[y, x + 1], [y, x - 1]], axis=0)
    return splits


def get_int(map: np.ndarray, y: np.int64, x: np.int64):
    if map[y, x] == "." or map[y, x] == "S":
        return 0
    else:
        return int(map[y, x])


def solve_b(map: np.ndarray, x: np.int64, y: np.int64):
    # m, n = map.shape
    # if y >= m or x >= n:
    #     return 1
    # while map[y, x] == ".":
    #     y += 1
    #     if y >= m or x >= n:
    #         return 1
    # if map[y, x] == "^":
    #     return solve_b(map, x - 1, y) + solve_b(map, x + 1, y)
    m, n = map.shape
    start = np.where(lines[0] == "S")[0][0]
    stack = np.array([[1, start]])
    map = ((map == "^") * -1).astype(np.int64)
    map[0, start] = 1
    visited = np.zeros((m, n), dtype=bool)
    while len(stack) != 0:
        i = stack[:, 0].argmin()
        coords = stack[i]
        stack = np.delete(stack, i, axis=0)

        y, x = coords[0], coords[1]
        if y >= m or x >= n:
            continue
        if visited[y, x]:
            continue
        visited[y, x] = True
        item = map[y, x]
        if item == 0:
            map[y, x] = map[y - 1, x]
            stack = np.append(stack, [[y + 1, x]], axis=0)
        elif item == -1:
            num = get_int(map, y - 1, x)
            map[y, x + 1] = get_int(map, y, x + 1) + num
            map[y, x - 1] = get_int(map, y, x - 1) + num
            stack = np.append(stack, [[y, x + 1], [y, x - 1]], axis=0)
        else:
            stack = np.append(stack, [[y + 1, x]], axis=0)
    return map[:, -1].sum()


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python main.py <filename>")
        exit(1)

    filename = sys.argv[1]
    lines = []
    with open(filename, "r") as f:
        lines = [line.strip() for line in f.readlines()]

    n = len(lines)
    lines = np.array(lines).view("U1").reshape((n, -1))

    start = np.where(lines[0] == "S")[0][0]
    splits = solve_b(lines, start, np.int64(1))
    print(lines)
    print("Total splits: ", splits)
