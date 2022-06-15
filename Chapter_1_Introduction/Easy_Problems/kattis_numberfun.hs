-- Kattis - numberfun
-- Simple if else cases
-- Time: O(1), Space: O(1)
import           Control.Monad

solve :: Int -> Int -> Int -> String -- a / b = c -> a = b*c or b = a*c
solve a b c =
  if (a + b == c) ||
     (a - b == c) ||
     (b - a == c) || (a * b == c) || (b * c == a) || (b == a * c)
    then "Possible"
    else "Impossible"

main :: IO () -- define type IO()
main = do
  x <- getLine -- x is a string
  let n = read x :: Int -- convert x to double
  replicateM_
    n -- For loop
    (do l <- getLine
        let [a, b, c] = map read (words l) :: [Int] -- split by spaces
        putStrLn (solve a b c) -- printing strings
     )
