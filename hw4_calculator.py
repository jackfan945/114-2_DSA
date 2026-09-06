import math

def calc(t):
    print(f"t = {t}, time = {round((1000 + 64 * t) * math.log(1024, 2 * t), 2)}")

for i in range(2, 20):
    calc(i)
