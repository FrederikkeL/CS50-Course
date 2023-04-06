import cs50
import math

creditCardNumber = cs50.get_int("creditCardNumber card no.:")
creditNumberCopy = creditCardNumber
creditno = []

while creditNumberCopy > 0:
    creditno.append(creditNumberCopy % 10)
    creditNumberCopy = math.trunc(creditNumberCopy / 10)
    
lenght = len(creditno)
totalSum = 0

while creditCardNumber > 0:
    lastDigit = creditCardNumber % 10                      
    rest = math.trunc(creditCardNumber / 10)   
    everyOther = rest % 10         
    creditCardNumber = math.trunc(creditCardNumber / 100) 

    product = everyOther * 2                
    productLastDigit = product % 10                   
    productFirstDigit = math.trunc(product / 10)    

    totalSum = totalSum + productLastDigit + productFirstDigit + lastDigit

controlNumber = totalSum % 10
if controlNumber == 0:
    if creditno[lenght-1] == 4 and (lenght == 13 or lenght == 16):
        print("VISA")  # checks if visa (starts with 4) then print visa
    elif (creditno[lenght-1] == 5 and creditno[lenght-2] < 6 and creditno[lenght-2] > 0) and lenght == 16:
        # checks if mastercard (starts with 5) then print mastercard/n
        print("MASTERCARD")
    elif (creditno[lenght-1] == 3 and creditno[lenght-2] == 7 or creditno[lenght-2] == 4) and lenght == 15:
        print("AMEX")  # controlNumber if american express (starts with 3) then print amex/n
    else:
        # prints invalid if not one of the recognized types
        print("INVALID")
else:
    print("INVALID")
