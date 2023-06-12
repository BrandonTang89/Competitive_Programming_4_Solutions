-- Kattis - prva
-- Standard kind of question, chill
import Data.List (sort, transpose)
main :: IO()
main = interact(head . sort . filter (\x -> length x > 1) . solve . tail . lines)

solve :: [String] -> [String]
solve xs = concatMap (splitOn '#') (xs ++ transpose xs)

splitOn :: (Eq a) => a -> [a] -> [[a]]
splitOn _ [] = []
splitOn c xs = ys : splitOn c (dropWhile (== c) zs) where (ys, zs) = span (/= c) xs