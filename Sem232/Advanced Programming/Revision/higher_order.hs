mysum xs = foldl (+) 0 xs
myproduct xs = foldl (*) 1 xs

mylength xs = foldr (\_ n -> n + 1) 0 xs

-- (++ ys) = foldr (:) ys
reverse = foldr (\x xs -> xs ++ [x]) []

takeWhile :: (a -> Bool) -> [a] -> [a]
takeWhile p [] = []
takeWhile p (x:xs) | p x = x : takeWhile p xs | otherwise = []
dropWhile :: (a -> Bool) -> [a] -> [a]
dropWhile p [] = []
dropWhile p (x:xs) | p x = x

map' :: (a -> b) -> [a] -> [b]
map' f = foldr (\x acc -> f x : acc) []
filter' :: (a -> Bool) -> [a] -> [a]
filter' p = foldr (\x acc -> if p x then x : acc else acc) []

map f (filter p xs)

