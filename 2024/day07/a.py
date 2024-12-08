import sys

operators = ["+", "*"]

def combine(target: int, a: int, vals: list[int]) -> bool:
    if len(vals) == 0:
        return a == target
    b = vals[0]
    for op in operators:
        c = eval(f"{a} {op} {b}")
        if combine(target, c, vals[1:]):
            return True
    return False

def main(filename: str): 
    with open(filename, "r") as f:
        lines = f.readlines()

    sum = 0
    for line in lines:
        res, vals = line.split(":")
        vals = [int(val) for val in vals.strip().split(" ")]
        res = int(res)
        if combine(res, vals[0], vals[1:]):
            sum += res 

    print(sum)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python main.py <input_file>")
        exit(1)
    main(sys.argv[1])
