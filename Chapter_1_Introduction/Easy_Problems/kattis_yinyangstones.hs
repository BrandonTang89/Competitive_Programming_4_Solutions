-- Kattis - yinyangstones
-- Check if equal number of black and white stones
main :: IO()
main = interact (show . solve . head . lines)

solve :: String -> Int
solve c = if (sum (map (\x -> (if (x == 'W') then 1 else -1)) c)) == 0 then 1 else 0