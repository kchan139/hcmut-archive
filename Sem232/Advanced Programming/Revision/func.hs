myabs :: Int -> Int
myabs n = if n >= 0 then n else -n

mysignum :: Int -> Int
mysignum n =    if n < 0 then -1 else
                    if n == 0 then 0 else 1

mysignum2 n | n < 0     = -1
            | n > 0     = 1
            | otherwise = 0

(&&&) :: Bool -> Bool -> Bool
True  &&& x = x
False &&& _ = False

(|||) :: Bool -> Bool -> Bool
True  ||| _ = True
False ||| x = x

myhead :: [a] -> a
myhead (x:_) = x

mytail :: [a] -> [a]
mytail [] = []
mytail (_:xs) = xs

mylast :: [a] -> a
mylast [x] = x
mylast (_:xs) = mylast xs

--
-- THIS IS NOT HOW PATTERN MATCHING
-- WORKS IN HASKELL
-- myinit :: [a] -> [a]
-- myinit (xs:_) = xs
--

myadd :: Int -> (Int -> Int)
myadd = \x -> (\y -> x + y)

myodds :: Int -> [Int]
myodds n = map (\x -> 2*x + 1) [0..n-1]

safetail :: [a] -> [a]
safetail xs = if null xs then [] else tail xs

safetail2 :: [a] -> [a]
safetail2 xs | null xs   = []
             | otherwise = tail xs
