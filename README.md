# ymacro
map/reduce macro lib for C. works with lists up to 32 items in length.

```
#define INCR(x) (x+1)
#define MUL(a,b) a*b

Y_REDUCE(MUL, Y_MAP(INCR, (1,2,3,4,5,6,7))))
```

expands to
```
(1+1)*(2+1)*(3+1)*(4+1)*(5+1)*(6+1)*(7+1)
```
