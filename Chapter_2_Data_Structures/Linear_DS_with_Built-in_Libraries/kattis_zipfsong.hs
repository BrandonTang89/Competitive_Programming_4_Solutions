-- Kattis - zipfsong
-- Unpack the problem to notice that we are sorting by f*i where i is the 1-indexed index of the song.
-- Avoiding divisions allows avoiding floating point errors, using Big-Integers allows avoiding overflow errors.
-- Notice that since we reverse the list at the end of the sort, we should sort by decreasing i as the second
-- priority.
-- Time: O(n log n), Space: O(n)
import Data.List (sort)
main :: IO()
main = interact(unlines . parse . map words . lines)
    
parse :: [[String]] -> [String]
parse ([_, m']:xs) = (take (read m') . solve . map toTuple) xs
                    where toTuple [x, y] = (read x :: Integer, y)
                          toTuple _ = error "Invalid input"
parse _ = error "Invalid input"

solve :: [(Integer, String)] -> [String]
solve ys = (map third . reverse . sort) (zipWith (\(f, s) i -> (f*i, -i, s)) ys [1..])
                where third (_, _, x) = x