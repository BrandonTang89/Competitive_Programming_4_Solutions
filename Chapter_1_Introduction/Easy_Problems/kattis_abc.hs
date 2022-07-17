-- Kattis - abc
-- Pretty strightforward, sort 3 numbers then output according to the order given.
-- Time: O(1), Space: O(1)
import Data.List
import Data.Char
main :: IO()
main  = do
    line <- getLine
    let abc = words (line) :: [String]

    let f = read (abc!!0) :: Int
    let s = read (abc!!1) :: Int
    let t = read (abc!!2) :: Int

    let nums = sort [f,s,t] :: [Int]

    order <- getLine
    putStr $ show (nums!!( (ord (order!!0) - ord 'A') :: Int))
    putStr " "
    putStr $ show (nums!!( (ord (order!!1) - ord 'A') :: Int))
    putStr " "
    putStrLn $ show (nums!!( (ord (order!!2) - ord 'A') :: Int))