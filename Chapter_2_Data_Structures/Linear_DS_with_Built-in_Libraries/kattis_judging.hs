-- Kattis - judging
-- Mostly classic, kinda similar to finding the intersection of 2 sets
-- Time: O(n log n)
import Data.List (sort)
main :: IO()
main = interact(show . solve . tail . lines)

solve :: [String] -> Int
solve xs = solve' (sort ys) (sort zs) where (ys, zs) = splitAt (length xs `div` 2) xs

solve' :: [String] -> [String] -> Int
solve' [] _ = 0
solve' _ [] = 0
solve' (x:xs) (y:ys)
    | x == y = 1 + solve' xs ys
    | x < y = solve' xs (y:ys)
    | otherwise = solve' (x:xs) ys