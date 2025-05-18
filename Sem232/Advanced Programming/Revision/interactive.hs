act :: IO (Char, Char)
act = do x <- getChar
         getChar
         y <- getChar
         return (x, y)

getline :: IO String
getline = do 
    x <- getChar
    if x == '\n' then 
        return []
    else 
        do 
        xs <- getline
        return (x:xs)