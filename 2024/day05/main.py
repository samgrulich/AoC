import sys

def is_page_valid(page: list, rules: dict):
    if len(page) == 1:
        return True
    for i, x in enumerate(page):
        x = int(x)
        for y in rules.get(x, []):
            y = str(y)
            if y in page[:i]:
                return False
    return True

def reorder_page(page: list[str], rules: dict[int, list[int]]):
    incomingCounts: dict[int, int] = {}

    # generate graph
    for x in page:
        x = int(x)
        incomingCounts[x] = 0

    # count incoming edges
    for x in page:
        x = int(x)
        for y in rules.get(x, []):
            if str(y) in page:
                incomingCounts[y] = incomingCounts.get(y, 0) + 1

    # topological sort
    result: list[int] = []
    while len(incomingCounts) != 0:
        for k, v in incomingCounts.items():
            if v == 0:
                result.append(k)
                for x in rules.get(k, []):
                    if str(x) in page:
                        incomingCounts[x] -= 1
                del incomingCounts[k]
                break

    return result



def main(filename: str):
    with open(filename, 'r') as f:
        file = f.read()
    rulesIn, pagesIn = file.split('\n\n')

    rules: dict[int, list[int]] = {}
    for rule in rulesIn.split('\n'):
        x, y = rule.split('|')
        x, y = int(x.strip()), int(y.strip())
        if (rules.get(x) == None):
            rules[x] = []
        rules[x].append(y)

    print("rules: ", rules)
    invalidPages = []
    for pageIn in pagesIn.split('\n'):
        page = pageIn.split(',')
        if not is_page_valid(page, rules):
            invalidPages.append(page)

    # reorder
    validPages: list[list[int]] = []
    for page in invalidPages:
        reordered = reorder_page(page, rules)
        validPages.append(reordered)
        print("original: ", page, "; reordered: ", reordered)

    medianSum = 0
    for page in validPages:
        medianSum += int(page[len(page) // 2])
    print(medianSum)


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: python main.py <input_file>")
        exit(1)
    main(sys.argv[1])
