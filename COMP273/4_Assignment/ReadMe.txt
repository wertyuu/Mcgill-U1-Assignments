/**********************\
|    Jonathan Fokkan   |
|      260447938       |
|     Assignment 4     |
|       24.11.11       |
\**********************/

Cache: N-Way LRU 4/64/4/1024
-----------------------------------------------------
V   N       access  hit     miss    rate(%)    instcount
-----------------------------------------------------
1   8       1088    1038    50      95          9094    
2   8       2048    1997    51      98          13894

1   16      8448    6394    2054    76          68990
2   16      16384   15313   1071    93          108670

1   32      66560   31280   35279   47          537838
2   32      131072  121567  9505    93          860398

Cache: N-Way LRU 2/64/4/1024
-----------------------------------------------------
V   N       access  hit     miss    rate(%)    instcount
-----------------------------------------------------
1   8       1088    1038    50      95          9094
2   8       2048    1998    50      98          13894

1   16      8448    6660    1788    79          68990
2   16      16384   15514   870     95          108670

1   32      66560   31289   35271   47          537838
2   32      131072  121551  9521    93          860398

Cache: Direct LRU 1/64/4/1024
-----------------------------------------------------
V   N       access  hit     miss    rate(%)    instcount
-----------------------------------------------------
1   8       1088    928     160     85          9094
2   8       2048    1454    594     71          13894

1   16      8448    7151    1297    85          68990
2   16      16384   14916   1468    91          108670

1   32      66560   30882   35678   46          537838
2   32      131072  111166  19906   85          860398

1 Multiplication
----------------
1.
    The norm of a matrix is the natural extension of the notion of vector norm to matrices. 
    Therefore the norm of the difference of the computed result from the actual result. If 
    this norm is non-zero, this means that the computed result is no close enough to the
    actual result. If the norm is close to zero, this means the computed result is a close
    approximation of the actual result.

    The frobenius norm is not exactly zero for a correct answer because of loss of precision 
    during the multiplication or the answer put inside of C* is not precise enough.

2.
    n^2 + (2n)*(n^2) = 2n^3 + n^2

2 Cache Optimized Multiplication
--------------------------------
1.
    Assuming a N-Way LRU 4/64/4/1024 cache,

    For N=8,
        Difference in Instcount from MADD1 to MADD2 = 13894-9094 = 4800
        MADD2 has 1 more cache miss even though it has 3% less cache miss rate.
        MADD2 will never be faster than MADD1 for N = 8, no matter what Miss Penalty.

    For N = 16,
        Difference from MADD1 to MADD2 in instcount = 108670 - 68990 = 39680
        MADD1 - MADD2 (miss) = 2054 - 1071 = 983
        (/ 39680 983) = 40 (Approx.)
        MADD2 will be faster if the miss penalty is greater than time to execute 41 instructions.

    For N = 32,
        Difference from MADD1 to MADD2 in instcount = 860398 - 537838 = 322560
        MADD1 - MADD2 (miss) = 35279 - 9505 = 25774
        (/ 322560 25774) = 12.5
        MADD2 will be faster if the miss penalty is greater than the time to execute 13 instructions.

2.
    The 2-way set associative cache is best for my implementation for N=16. This is because when going through

3.
    The smallest cache that will still allow a win for MADD2 over MADD1 
    is a 4-Way set associative cache of 32bytes (N-Way set associative 4/4/2/32).
    MADD2 will still have (- 6641 4609) = 2032 less misses for N = 16 and 
    therefore a miss penalty of less than 19.5 instructions will allow MADD2 to win over MADD1.

3 Optimization
--------------
1.
From MADD1 to MADD3
    I calculated the address of a, b and c outside of the loop in which they would be updated and 
    updated them with less instructions when the need arised.
    I replaced BGE with BEQ. This provided a smaller increase in performance.
    I removed the j at the end of the inner most loop and but a bne to go back into the loop.

    For the final optimization, I did partial loop unrolling. Since no information was given 
    about what size of matrices the MADD* functions are expected to be able to do, I decided 
    to special case the MADD4 procedure to solve matrices of size multiple 8. This is necessary for 
    the partial loop unrolling, therefore choosing multiples of 8 will give the greatest optimization
    for the matrices supplied.

2.
        MADD1 to MADD3
        ------------------------------------------------------------
        V   N               instcount                   % decrease
        ------------------------------------------------------------
        1   8               9094    
        3   8               6511(smart addresses)           28.4
        3   8               5854(BGE->BEQ)                  10.0
        3   8               5278(j->BNE)                    9.8
        3   8               4830(partial loop unrolling)    8.4

        1   16              68990
        3   16              46287(smart addresses)          32.9
        3   16              41646(BGE->BEQ)                 10.0
        3   16              37294(j->BNE)                   10.4
        3   16              33710(partial loop unrolling)   9.6

        1   32              537838
        3   32              348559(smart addresses)         35.1
        3   32              313678(BGE->BEQ)                10.0
        3   32              279886(j->BNE)                  10.7
        3   32              251214(partial loop unrolling)  10.2

        MADD2 to MADD4
        ---------------------------------------------------------------
        V   N               instcount                      % decrease
        ---------------------------------------------------------------
        2   8               13894                           
        4   8               7174(smart addresses)           48.3  
        4   8               6526(BEQ)                       9.0
        4   8               5949(j->BNE)                    9.0
        4   8               5493(partial loop unrolling)    7.7
                                                              
        2   16              108670                            
        4   16              51070(smart addresses)          53.0
        4   16              46446(BEQ)                      9.0
        4   16              42077(j->BNE)                   9.4
        4   16              38493(Partial loop unrolling)   8.5
                                                              
        2   32              860398                            
        4   32              384238(smart addresses)         55.3
        4   32              349390(BEQ)                     9.1
        4   32              315565(j->BNE)                  10.0
        4   32              386893(partial loop unrolling)  9.0

        The change producing the most significant reduction in instruction count is uncontestably
        the smart updating of addresses. This is because it removed about 4 instruction per iteration
        per address calculated. Over thousands of iterations this reduced the instruction count by 
        as much as 55.3% for 32x32 matrices in MADD4.

3.
    The cache aware implementations will win even for a smaller miss penalty, 
    since the disparity in instruction count will be smaller between the non-cache aware ones and the cache ones.
