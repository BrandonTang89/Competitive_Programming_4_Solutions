-- Kattis - reversebinary
-- Simple. Convert to binary, reverse, convert back to decimal.
main :: IO()
main = interact(show . solve . read . head . lines)

solve :: Int -> Int
solve = foldr f 0 . reverse . toBinary
        where f x y = 2*y + x
    
toBinary :: Int -> [Int]
toBinary 0 = []
toBinary x = (x `mod` 2) : toBinary (x `div` 2)