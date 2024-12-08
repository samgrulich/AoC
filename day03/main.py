import sys

def main(): 
    filename = sys.argv[1]
    s = ""
    with open(filename, 'r') as f:
        s = f.read()
    activeZoneCandidates = s.split("do()");
    print("zone candidates: ", activeZoneCandidates)
    zones = []
    for activeZoneCandidate in activeZoneCandidates:
        zone = activeZoneCandidate.split("don't()")[0];
        zones.append(zone)

    sum = 0;
    for zone in zones:
        candidates = zone.split("mul") 
        print("candidates: ", candidates)
        for candidate in candidates:
            if not candidate.startswith("("):
                continue
            print(candidate, end=" ")
            if candidate.find(")") == -1:
                continue
            temp = candidate.split(")")
            candidate = temp[0][1:]
            print(candidate)
            nums = candidate.split(',')
            if len(nums) != 2:
                continue
            if not nums[0].isnumeric() or not nums[1].isnumeric():
                continue
            sum += int(nums[0]) * int(nums[1]);
    print(sum)
        


if __name__ == "__main__":
    if (len(sys.argv) < 2):
        print("Usage: python main.py <filename>")
        exit(1)
    main()

        
