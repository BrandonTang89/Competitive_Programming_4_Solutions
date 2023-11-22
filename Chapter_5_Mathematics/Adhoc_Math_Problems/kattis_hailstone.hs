-- Kattis - hailstone
-- It quite straightforward with haskell

main :: IO()
main = interact (show . solve . read)

solve :: Int -> Int
solve n = (sum . h) n

h :: Int -> [Int]
h 1 = [1]
h n
    | even n = n : h (n `div` 2)
    | odd n = n : h (3 * n + 1)