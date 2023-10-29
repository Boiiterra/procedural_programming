# Why Python? - Why not?!
"""Checks if file is sorted correctly."""

import sys


def main():
    mx = 0
    with open("./numburs.txt", "r") as file:
        mx = int(file.readline())

    a = []
    with open("./sort_me.txt", "r") as file:
        for i in range(mx):
            a.append(int(file.readline()))
    a = sorted(a)

    r = 0
    with open("./sorted.txt", "r") as file:
        for i in range(mx):
            n = int(file.readline())

            if int(n) == a[i]:
                r += 1

    if r == mx:
        print("  - [INFO]: File is sorted correctly!")
    else:
        print(f"  - [INFO]: Only {r} numbers are sorted correctly out of {mx}!")


def obscure():
    mx = 10000000
    a = []
    i = "  - [INFO]:"
    with open("./ten_mln_to_sort.txt", "r") as file:
        for _ in range(mx):
            a.append(int(file.readline()))
    a = sorted(a)

    r = 0
    with open("./ten_mln_sorted.txt", "r") as file:
        for j in range(mx):
            n = int(file.readline())

            if int(n) == a[j]:
                r += 1

    if r == mx:
        print(f"{i} File with ten million numbers is sorted correctly!")
    else:
        print(f"{i} Only {r} numbers are sorted correctly out of ten million!")


if __name__ == "__main__":
    doing = True

    if len(sys.argv) > 1:
        if sys.argv[1] == "10m":
            print("  - [INFO]: Checking ten million lines files!!!")
            obscure()
            doing = False
        if doing:
            print(
                "- [INFO]: If you want to check ten million lines"
                "files use: python see.py 10m"
            )
    if doing:
        main()
