#GCD Euclidean
def gcd(a, b): 
    if a == 0 : 
        return b 
    return gcd(b%a, a) 
a = 10
b = 15
print("gcd(", a , "," , b, ") = ", gcd(a, b)) 


#Extended Euclidean
def gcdExtended(a, b): 
    if a == 0: 
        return b, 0, 1      
    gcd, x1, y1 = gcdExtended(b % a, a) 
    x = y1 - (b // a) * x1 
    y = x1 
    return gcd, x, y 

a, b = 231, 71
g, x, y = gcdExtended(a, b) 
print("Extended GCD(", a , "," , b, ") = ", g)
print("Coefficients x and y:", x, y)
