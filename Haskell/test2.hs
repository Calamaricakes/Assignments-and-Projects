-- define your function here
-- don't forget the type signature
bigsearch :: (Int -> Bool) -> [Int] -> [Int]
bigsearch func [] = []
bigsearch func (y:ys)
    | func y     = [y] ++ bigsearch func ys
    | otherwise  = []  ++ bigsearch func ys

-- the following helper functions are provided to help you
-- test your function

evn :: Int -> Bool
evn x = x `mod` 2 == 0

big :: Int -> Bool
big x = x > 100
