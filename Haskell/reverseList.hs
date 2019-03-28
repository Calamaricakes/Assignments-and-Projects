reverseList :: [a] -> [a]
reverseList [] = []
reverseList [a] = [a]
reverseList (x:xs)
    | last x ++ reverseList init x
