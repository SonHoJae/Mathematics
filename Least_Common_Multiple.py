from functools import reduce
List = list(range(1,21))
print(List)
commonMutiples = []
while sum(List) != len(List):
    minValue = min([x for x in List if x != 1 and x != 0])
    common = list(filter(lambda x: x % minValue == 0, List))
    common = list(map(lambda x: x // minValue,common))
    uncommon = list(filter(lambda x: x % minValue != 0, List))
    List = common + uncommon
    commonMutiples.append(minValue)
print(reduce(lambda x,y: x*y ,commonMutiples))