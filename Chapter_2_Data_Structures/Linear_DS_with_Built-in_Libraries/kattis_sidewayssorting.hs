import Data.Char
main :: IO()
main = interact(parse . lines)

parse :: [String] -> String
parse xs = let [r, c] = map read ((words . head) xs)
               nxt = take r (tail xs)
               remaining = drop r (tail xs)
           in 
           if r == 0 then "" else unlines (solve nxt) ++ "\n" ++ parse remaining

solve :: [[Char]] -> [[Char]]
solve = transpose . qsort . transpose

qsort :: [String] -> [String]
qsort [] = []
qsort [a] = [a]
qsort (x:xs) = qsort (filter (\y -> map toLower y < map toLower x) xs) ++ [x] ++ qsort (filter (\y -> map toLower y >=  map toLower x) xs)

transpose :: [[Char]] -> [[Char]]
transpose = foldr (zipWith (:)) (repeat [])