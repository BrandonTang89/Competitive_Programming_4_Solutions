-- Kattis - apples
-- Easy once you realise we can just split each column by # then sort then concat back
import Data.List (sort, transpose)
main :: IO()
main = interact(unlines . transpose . map solve . transpose . tail . lines)

solve :: String -> String
solve [] = []
solve xs = (sort . takeWhile(/='#')) xs ++ if null rs then [] else ('#':(solve . tail) rs)
            where rs = (dropWhile(/='#')) xs