concac :: [[a]] -> [a]
concac xss = [x | xs <- xss, x <- xs]

factors :: Int -> [Int]
factors n = [x | x <- [1..n], n `mod` x == 0]

prime :: Int -> Bool
prime n = factors n == [1, n]

primes :: Int -> [Int]
primes n = [x | x <- [2..n], prime x]

pairs :: [a] -> [(a, a)]
pairs xs = zip xs (tail xs)

sorted :: Ord a => [a] -> Bool
sorted xs = and [x <= y | (x,y) <- pairs xs]

indexes :: Eq a => a -> [a] -> [Int]
indexes x xs = [i | (x', i) <- zip xs [0..], x == x']

count :: Char -> String -> Int
count x xs = length [x' | x' <- xs, x == x']

pyths :: Int -> [(Int, Int, Int)]
pyths n = [(x, y, z) | x <- [1..n], y <- [1..n], z <- [1..n], x^2 + y^2 == z^2]

perfects :: Int -> [Int]
perfects n = [x | x <- [1..n], sum (factors x) - x == x]

scalar_product :: [Int] -> [Int] -> Int
scalar_product xs ys = sum [x*y | (x, y) <- zip xs ys]