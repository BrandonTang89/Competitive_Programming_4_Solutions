-- Kattis - chartingprogress
-- Generic sorting problem, its easiest to solve by sorting a zip of each column with an index to sort by 
-- that is computed by seeing how many '.'s are in the column before the first '*' in the column.
import Data.List
main :: IO()
main = interact (unlines . concat . intersperse [" "] . map (transpose . solve . transpose) . merge . lines)

merge :: [String] -> [[String]]
merge [] = []
merge xs = cur : merge (if null rest then [] else tail rest) where (cur, rest) = span (/= "") xs

solve :: [String] -> [String]
solve xs = (map snd . reverse . sort) (zip (map (length . takeWhile (== '.')) xs ) xs)