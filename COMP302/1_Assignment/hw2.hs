#!/usr/bin/env runghc

import Data.List

main = print (average [1,2,3])

average :: (Real b, Fractional a) => [b] -> a
average xs = realToFrac (sum xs) / genericLength xs

--test to see what generic length is made of
genericlength [] = 0
genericlength (x:xs) = 1 + genericlength xs

bmi weight height
    | bmical > 20 = "you are bit overweight"
    | bmical == 20 = "you are beautiful"
    | bmical < 20 = "you skinny bastard"
    where bmical = weight/height * height

