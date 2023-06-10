-- Kattis - dirtydriving
-- Basically a foldl with a max function. Perhaps we could just split it into a map + maximum as well?
import Data.List
main :: IO()
main = interact (show . solve . map (map read . words) . lines)

solve :: [[Int]] -> Int
solve ([n, p]:xs:[]) = foldl f p (zip (tail sxs) [2..])
                        where sxs = sort xs
                              f curMax (x, i) = max curMax (p*i - x + head sxs)
solve _ = error "Unhandled case"