# Algorithm:

## Main:

1. Start
2. Create structure for storing productions
3. Read file and store as productions (fscanf(fp,"%s",dest))
4. Read input into input variable
5. Initialise stack (single element - $) and append input (add $)
6. While:
   1. Print header
   2. Print stack content
   3. Print input content
   4. Check accept state (stack contains start symbol, input contains $):
      1. If true, print "Accept"
      2. Break while
   5. Set reduced to false
   6. Iterate through productions:
      1. If reduce(i):
         1. Print "reduced by" prod[i]
         2. Set reduced to true
         3. Break
   7. Set shifted to false
   8. If !reduced:
      1. Shifted = shift()
      2. Print "shift"
   9. If !shifted and !reduced:
      1. Print "parse error"
7. Stop

## Shift:

1. Start
2. If \*ip=='$' return false (end of string)
3. Stack[++top]=input[0]
4. Input = (\*ip++)
5. Return true
6. Stop

## Reduce:

1. Start
2. Compare length of current rhs and top (strlen and top+1):
   1. If not equal, return false
3. Copy stack to temp string
4. Strcmp:
   1. If not same, return false
5. Top-=strlen
6. Stack[++top]=lhs
7. Return true
