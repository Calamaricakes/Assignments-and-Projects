xor :: Bool -> Bool -> Bool
xor b1 b2
    | b1 == True && b2 == False = True
    | b1 == False && b2 == True = False
    | otherwise                 = False
