# Why python when you can use C? Cuz it was here before I could write files.
"""Generates file to sort."""

from random import randint

mlines = 2
lines = 1_000_000
n = 1_000_000
mn = -n


def main():
    amm = 0
    with open("sort_me.txt", "w") as file:
        # amm = randint(10, 1000)
        # amm = 37_100_000
        # amm = 10_000_000
        # amm = randint(2, lines)
        amm = randint(mlines, lines)
        tot = amm
        while amm:
            file.write(f"{randint(mn, n)}\n")
            amm -= 1

        print(
            "  - [INFO]: Generated file 'sort_me.txt' with"
            f" {tot} numbers in range [{mn}; {n}]."
        )

    with open("numburs.txt", "w") as file:
        file.write(str(tot))


if __name__ == "__main__":
    main()
