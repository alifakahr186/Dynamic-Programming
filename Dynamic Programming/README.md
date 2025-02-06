In Problems Files we write two .cpp files one is Implementation & other is Implementation2.
    In Implementation.cpp we cover all cases recursion, Memoization, Tabulation
    In Implementation2.cpp we cover space optimization with all cover 

How we came to know that now we can solve this problem using space optimization also?
    If the current state in the DP table only depends on a small number of previous states
    (e.g., the previous row or column)


By analyzing base case of recursion we write memoization and Tabulation base case. We know that if recursion
base case return 0 than we do not need to write it in base case of tabulation function. We write other base case.
If need than modifying base case.

How we come to know that this is 2D array or we solve Memo & Tabu using 2D array. We look at function 
paramenter and that paramenter tell us is we now using either 2D or 3D in memoization and tabulation.
We look which paramenter in function is effected either one or two. Than according to that.

*If there is previous row and column, then we can space optimize*
