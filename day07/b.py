import sys

operators = ["+", "*"]
vals: list[int] = []

def combine(target: int, a: int, i: int) -> bool:
    if i == len(vals):
        return a == target
    b = vals[i]
    for op in operators:
        c = eval(f"{a} {op} {b}")
        if combine(target, c, i+1):
            return True
    if combine(target, int(f"{a}{b}"), i+1):
        return True
    return False

def main(filename: str): 
    with open(filename, "r") as f:
        lines = f.readlines()

    sum = 0
    for line in lines:
        global vals
        res, valsIn = line.split(":")
        vals = [int(val) for val in valsIn.strip().split(" ")]
        res = int(res)
        if combine(res, vals[0], 1):
            sum += res 

    print(sum)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python main.py <input_file>")
        exit(1)
    main(sys.argv[1])
