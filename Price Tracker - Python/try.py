def divide(num):
    try:
        return num/0
    except ZeroDivisionError:
        print("Can't do that opps")

if(divide(10)):
    print(divide(10))