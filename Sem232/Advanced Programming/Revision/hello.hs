double x = x + x

quadruple x = double (double x)

factorial x = product [1..x]

average xs = sum xs `div` length xs

square x = x * x

append xs ys = xs ++ ys

mylast1 xs = xs !! (length xs - 1)

mylast2 xs = head (reverse xs)

myinit1 xs = reverse (tail (reverse xs))

myinit2 xs = take (length xs - 1) xs

second xs = head (tail xs)

swap (x, y) = (y, x)

pair x y = (x, y)

palindrome xs = reverse xs == xs

twice f x = f (f x) 

mean xs = sum xs / fromIntegral (length xs)

variance xs = let avg = mean xs
              in sum (map (\x -> (x - avg) ^ 2) xs) / fromIntegral (length xs)

