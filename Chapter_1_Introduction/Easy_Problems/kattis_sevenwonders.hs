-- Kattis - sevenwonders
-- I love these easy questions

solve :: String -> Int
solve s = let arr = [length (filter (\x -> x == c) s) | c <- ['T', 'C', 'G']]
          in
          (sum (map (\x -> x * x) arr)) + (minimum arr) * 7
main :: IO()
main = interact (show . solve)