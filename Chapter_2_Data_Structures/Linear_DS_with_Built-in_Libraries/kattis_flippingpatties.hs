-- Kattis - flippingpatties
-- Taking an L due to the lack of an array, but still works.
-- Time: O(n log n)
import Data.List
main :: IO()
main = interact (show . solve . map (map read . words) . tail . lines)

solve :: [[Int]] -> Int
solve = runs . sort . foldl (\xs [d, t] -> t:(t-d):(t-2*d):xs) []

runs :: [Int] -> Int
runs xs = let (_, _, z) = foldl f (-1, 0, 1) xs
              f (prev, c, longest) x = if (x == prev) then (prev, c+1, max (c+1) longest) else (x, 1, longest)
          in ((z+1) `div` 2)