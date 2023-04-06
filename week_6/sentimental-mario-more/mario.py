import cs50

while True:
    height = cs50.get_int("Height: ")
    if height > 0 and height < 9:
        break
for i in range(1, height+1, 1):

    # prints first columns spaces
    for k in range(height-i):
        print(" ", end="")

    # prints first columns #
    for l in range(i):
        print("#", end="")

    # prints middle spaces
    print("  ", end="")

    # prints second columns
    for j in range(i):
        print("#", end="")
    print()
