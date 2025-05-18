import System.IO

type Board = [Int]
type Player = Int

main :: IO ()
main = do
    hSetBuffering stdout NoBuffering
    game [5,4,3,2,1] 1

game :: Board -> Player -> IO ()
game board player = do
    printBoard board
    if sum board == 0
        then putStrLn ("Player " ++ show (switch player) ++ " wins!!!")
        else do
            putStrLn ("Player " ++ show player ++ " is playing...")
            row <- prompt "Row? "
            stars <- prompt "How many stars? "
            if validMove board row stars
                then game (updateBoard board row stars) (switch player)
                else do
                    putStrLn "Invalid move!"
                    game board player

prompt :: String -> IO Int
prompt s = do
    putStr s
    readLn

validMove :: Board -> Int -> Int -> Bool
validMove board row stars = row >= 1 && row <= length board && stars >= 1 && stars <= board !! (row - 1)

updateBoard :: Board -> Int -> Int -> Board
updateBoard board row stars = take (row - 1) board ++ [board !! (row - 1) - stars] ++ drop row board

printBoard :: Board -> IO ()
printBoard = mapM_ (putStrLn . flip replicate '*')

switch :: Player -> Player
switch 1 = 2
switch 2 = 1