import sys

KW = "MAS"

sum = 0

def is_in_range(lines: list[str], i: int, j: int):
    return 0 <= i and i < len(lines) and  0 <= j and j < len(lines[i]);

def search_in_dir(lines: list[str], i: int, j: int, dx: int, dy: int):
    i-=dx; j-=dy;
    for kc in KW:
        if (not is_in_range(lines, i, j) or kc != lines[i][j]):
            return False
        i+=dx; j+=dy;
    return True

def main():
    # load input 
    filename = sys.argv[1]
    lines: list[str] = []
    with open(filename, 'r') as f:
        lines = f.readlines()

    print(end=' ')
    for (i, line) in enumerate(lines):
        for (j, c) in enumerate(line):
            print(c, end=' ')
            if (c == 'A'):
                founda = search_in_dir(lines, i, j,  1,  1);
                foundb = search_in_dir(lines, i, j, -1,  1);
                foundc = search_in_dir(lines, i, j,  1, -1);
                foundd = search_in_dir(lines, i, j, -1, -1);
                print(founda, foundb, foundc, foundd)
                if ((founda and (foundb or foundc)) or (foundd and (foundb or foundc))):
                    print("found")
                    global sum
                    sum += 1


if __name__ == '__main__':
    if (len(sys.argv) != 2):
        print("Usage: python main.py <input_file>")
        exit(1)
    main()
    print(sum)
