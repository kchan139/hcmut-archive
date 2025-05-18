factorial :: Int -> Int
factorial 0 = 1
factorial n = n * factorial (n - 1)

size :: [a] -> Int
size []     = 0
size (_:xs) = 1 + size xs

myreverse :: [a] -> [a]
myreverse []     = []
myreverse (x:xs) = myreverse xs +++ [x]

myzip :: [a] -> [b] -> [(a, b)]
myzip [] _          = []
myzip _ []          = []
myzip (x:xs) (y:ys) = (x, y) : myzip xs ys

mydrop :: Int -> [a] -> [a]
mydrop 0 xs     = xs
mydrop _ []     = []
mydrop n (_:xs) = mydrop (n-1) xs

(+++) :: [a] -> [a] -> [a]
[] +++ ys     = ys
(x:xs) +++ ys = x : (xs +++ ys)

qsort :: Ord a => [a] -> [a]
qsort []     = []
qsort (x:xs) = qsort smallers ++ [x] ++ qsort largers
    where smallers = [s | s <- xs, s <= x]
          largers  = [l | l <- xs, l >  x]

myand :: [Bool] -> Bool
myand []     = True
myand (x:xs) = x && myand xs

concac :: [[a]] -> [a]
concac []       = []
concac (xs:xss) = xs ++ concac xss

myreplicate :: Int -> a -> [a]
myreplicate 0 _ = []
myreplicate n x = [x] ++ myreplicate (n-1) x

(!!!) :: [a] -> Int -> a
(x:_) !!! 1  = x
(_:xs) !!! n = xs !!! (n - 1)

myelem :: Eq a => [a] -> a -> Bool
myelem [] _     = False
myelem (x:xs) n = x == n || myelem xs n

merge :: Ord a => [a] -> [a] -> [a]
merge xs [] = xs
merge [] ys = ys
merge (x:xs) (y:ys) | x <= y    = x : merge xs (y:ys)
                    | otherwise = y : merge ys (x:xs)

msort :: Ord a => [a] -> [a]
msort []  = []
msort [x] = [x]
msort xs  = merge (msort left) (msort right)
    where left  = take (length xs `div` 2) xs
          right = drop (length xs `div` 2) xs