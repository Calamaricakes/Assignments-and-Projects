myElem :: Eq a => a -> [a] -> Bool
myElem item []  = False
myElem item (x:xs)
    | item == x = True
    | otherwise = myElem item xs
