-- Kattis - nastyhacks
-- A relatively simple for loop followed by 3 cases for each test case.
-- Time: O(n), Space: O(1)
import Control.Monad
solve :: Int -> Int -> Int -> String
solve r e c
    | r < e - c = "advertise"
    | r == e - c = "does not matter"
    | r > e -c = "do not advertise"

main :: IO()
main = do
    x <- getLine
    let n = read x :: Int
    replicateM_ n (do
        l <- getLine
        let [r, e, c] = map read (words l) :: [Int]
        putStrLn (solve r e c))