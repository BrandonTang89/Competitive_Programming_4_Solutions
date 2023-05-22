-- Kattis - closingtheloop
-- Chill question. Just split the lengths by colour then sort the lengths in decreasing order then repeatedly take the largest from both.
-- Time: O(n log n)
import Data.List
main :: IO()
main = interact (parse 1 . tail . lines)

parse :: Int -> [String] -> String
parse _ [] = ""
parse i (_:x:xs) = "Case #" ++ (show i) ++ ": " ++ (show (solve [] [] (words x))) ++ "\n" ++ (parse (i+1) xs)
parse _ _ = error "invalid input"

solve :: [Int] -> [Int] -> [String] -> Int
solve xs ys [] = let zs = zipWith (+) ((reverse . sort) xs) ((reverse . sort) ys)
                 in sum zs - 2*(length zs)
solve xs ys (w:ws) = let col = last w
                         len = read (init w) :: Int
                     in if (col == 'R') then solve (len:xs) ys ws else solve xs (len:ys) ws