mergel:: [Int] -> [Int] -> [Int]
mergel [] [] = []
mergel list [] = list
mergel [] list = list
mergel (x:xs) (y:ys)
    | x < y    = [x] ++ (mergel xs (y:ys))
    | otherwise= [y] ++ (mergel (x:xs) ys)
