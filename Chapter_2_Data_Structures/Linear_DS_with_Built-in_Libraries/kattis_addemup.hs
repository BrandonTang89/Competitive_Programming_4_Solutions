-- Kattis - addemup
-- First kinda longish haskell solution. Slightly scary how I can't just spam print statements
-- Though to be fair, there isn't that state to print I suppose, just need to check each function
-- individually. The solution is mostly straightforward, flip all the flippable numbers, sort, 
-- then use the 2 pointer method to find if there are any 2 numbers that sum to the target.
-- Time: O(n log n)
import Data.List (sort)

main :: IO()
main = interact(solve . map (map read . words) . lines)

solve :: [[Int]] -> String
solve [[n, t], xs] = solve' t (extend xs [0..])
solve _ = error "Invalid input"

extend :: [Int] -> [Int] -> [(Int, Int)]
extend [] _ = []
extend (x:xs) (i:is) = if flipable x then (x, i):(flipped x, i):(extend xs is) else (x, i):(extend xs is)
extend _ _ = error "Invalid input"

flipable :: Int -> Bool
flipable xs = all charflipable (show xs)

charflipable :: Char -> Bool
charflipable x = (x == '0') || (x == '1') || (x == '8') || (x == '2') || (x == '5') || (x == '6') || (x == '9')

flipped :: Int -> Int
flipped x = read ((map charFlipper . reverse . show) x) :: Int

charFlipper :: Char -> Char
charFlipper '0' = '0'
charFlipper '1' = '1'
charFlipper '8' = '8'
charFlipper '2' = '2'
charFlipper '5' = '5'
charFlipper '6' = '9'
charFlipper '9' = '6'
charFlipper _ = error "Invalid input"

solve' :: Int -> [(Int, Int)] -> String -- n, target, list
solve' t xs = search (length xs) t ys (reverse ys) where ys = sort xs

search :: Int -> Int -> [(Int, Int)] -> [(Int, Int)] -> String
search 0 _ _ _ = "NO"
search n t ((x, i):xs) ((y, j):ys)
    | x + y == t && i /= j = "YES"
    | x + y > t = search (n-1) t ((x, i):xs) ys
    | x + y < t = search (n-1) t xs ((y, j):ys)
    | otherwise = if (n-2 /= 0 && (fst . head) xs == x) then "YES" else search (n-2) t xs ys
search _ _ _ _ = error "Invalid input"