import sys


def apply_ins(state: int, ins: str) -> tuple[int, int]:
    """
    :return new_state: is the new state
    :return zero_count: how many times zero is crossed during the search
    """
    num = int(ins[1:])

    starts_at_zero = state == 0
    zero_count = num // 100
    num = num % 100

    if ins[0] == "L":
        state -= num
    else:
        state += num

    if not starts_at_zero:
        if state <= 0:
            zero_count += 1
        elif state >= 100:
            zero_count += 1

    return state % 100, zero_count


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python main.py <filename>")
        exit(1)

    filename = sys.argv[1]
    lines = []
    with open(filename, "r") as f:
        lines = f.readlines()

    state = 50
    zero_count = 0
    for line in lines:
        insctruciton = line.strip()
        new_state, ins_zero_count = apply_ins(state, insctruciton)
        print(state, new_state, insctruciton, ins_zero_count)
        state = new_state
        zero_count += ins_zero_count

    print("Final number of zeros is: ", zero_count)
