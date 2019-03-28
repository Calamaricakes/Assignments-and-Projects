factorial :: Integer -> Integer
factorial 0 = 0
factorial 1 = 1
factorial num = num * factorial (num-1)
