List = list(range(1,21))
result = []
for i in range(2,len(List)+1):
    prevLen = len(List)
    List = list(filter(lambda x : x % i != 0, List))
    [result.append(i) if prevLen != len(List) else None]
print(result)