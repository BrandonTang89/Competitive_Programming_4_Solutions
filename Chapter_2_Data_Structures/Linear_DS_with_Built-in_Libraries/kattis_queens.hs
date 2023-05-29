-- Kattis - queens
-- Not too bad, just check if any 2 queens are in the same row, column, or diagonal. 
-- Time: O(n log n)
import Data.List
main :: IO()
main = interact (solve . map (map read . words). tail . lines)

solve :: [[Int]] -> String
solve xs = if any id [if r1 == r2 || c1 == c2 || abs (r1 - r2) == abs (c1 - c2) then True else False | [r1, c1] <- xs, [r2, c2] <- xs, (r1, c1) /= (r2, c2)] 
            || containsDuplicates xs then "INCORRECT" else "CORRECT"

containsDuplicates :: [[Int]] -> Bool
containsDuplicates xs = let zs = zip ys (tail ys)
                            ys = sort xs
                        in any id [if x == y then True else False | (x, y) <- zs]