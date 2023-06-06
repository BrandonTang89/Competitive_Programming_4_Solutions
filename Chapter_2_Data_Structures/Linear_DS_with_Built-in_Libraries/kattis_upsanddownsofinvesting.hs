-- Kattis - upsanddownsofinvesting
-- Searching for a pattern of (n-1) ups then (n-1) downs in a list of changes. Could be achieved in linear time, but this is haskell.
-- Clearly the peaks and the valleys are the same, just invert the data.
-- There is a debugging issue where the s stock prices may occur on more than 1 line so we need to concat the tail of the lines together.
-- Time: O(s(n+m))
main :: IO()
main = interact(parse . map (map read . words) . lines)

parse :: [[Int]] -> String
parse ([s, n, m]:xss) = show (solve (n-1) (getChanges (concat xss))) ++ " " ++ show (solve (m-1) (getChanges(map (\x -> -x) (concat xss))))
parse _ = "error"

getChanges :: [Int] -> [Bool]
getChanges xs = map (> 0) (zipWith (-) (tail xs) xs) -- whether the list is increasing or not

kIncreaseskDecreases :: Int -> [Bool]
kIncreaseskDecreases k = (replicate k True) ++ (replicate k False)

solve :: Int -> [Bool] -> Int
solve k xs = solve' k (kIncreaseskDecreases k) xs

solve' :: Int -> [Bool] -> [Bool] -> Int
solve' k ps [] = 0
solve' k ps xs = if isPrefix ps xs then 1 + solve' k ps (drop (2*k) xs) else solve' k ps (tail xs)

isPrefix :: Eq a => [a] -> [a] -> Bool
isPrefix xs ys = xs == (take (length xs) ys)